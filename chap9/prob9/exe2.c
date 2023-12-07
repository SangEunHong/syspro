#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

#define MAXLINE 80
#define MAXARG 20

void background(char *cmd);
void execute(char *cmd);
void redirect(char *cmd);
void sequential(char *cmd);
char *args[MAXARG];

int main(void) {
    char cmd[MAXLINE];
    while (1) {
        printf("my shell");
        fgets(cmd, MAXLINE, stdin);
        cmd[strlen(cmd) - 1] = '\0';
        if (strstr(cmd, "&") != NULL)
            background(cmd);
        else if (strstr(cmd, ";") != NULL)
            sequential(cmd);
        else if (strstr(cmd, "<") != NULL || strstr(cmd, ">") != NULL)
            redirect(cmd);
        else
            execute(cmd);
    }
    return 0;
}

void parse(char *cmd) {
    char *token;
    token = strtok(cmd, " ");
    int i = 0;
    while(token != NULL){
        args[i] = token;
        token = strtok(NULL, " ");
        i++;
    }
    args[i] = NULL;
}

void execute(char *cmd) {
    parse(cmd);
    if (fork() == 0) {
        execvp(args[0], args);
        perror("execvp failed");
    } else {
        wait(NULL);
    }
}

void background(char *cmd) {
    char *token;
    token = strtok(cmd, "&");
    while(token != NULL){
        if (fork() == 0) {
            parse(token);
            execvp(args[0], args);
            perror("execvp failed");
        }
        token = strtok(NULL, "&");
    }
}

void sequential(char *cmd) {
    char *token;
    token = strtok(cmd, ";");
    while(token != NULL){
        execute(token);
        token = strtok(NULL, ";");
    }
}

void redirect(char *cmd) {
    char *inFile = NULL, *outFile = NULL;
    char *token = strtok(cmd, " ");
    int i = 0, in = 0, out = 0;
    while(token != NULL) {
        if (strcmp(token, "<") == 0) {
            in = 1;
        } else if (strcmp(token, ">") == 0) {
            out = 1;
        } else if (in) {
            inFile = token;
            in = 0;
        } else if (out) {
            outFile = token;
            out = 0;
        } else {
            args[i++] = token;
        }
        token = strtok(NULL, " ");
    }
    args[i] = NULL;
    if (fork() == 0) {
        if (inFile) {
            int fd0 = open(inFile, O_RDONLY, 0);
            dup2(fd0, STDIN_FILENO);
            close(fd0);
        }
        if (outFile) {
            int fd1 = open(outFile, O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
            dup2(fd1, STDOUT_FILENO);
            close(fd1);
        }
        execvp(args[0], args);
        perror("execvp failed");
    } else {
        wait(NULL);
    }
}

