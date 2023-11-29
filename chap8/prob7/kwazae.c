#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[], char *environ[]) {
    int i;

    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-e") == 0) {
            if (++i < argc) { 
                char *env_val = getenv(argv[i]);
                if (env_val)
                    printf("%s=%s\n", argv[i], env_val);
            } else {
                for (char **env = environ; *env; ++env)
                    printf("%s\n", *env);
            }
        } else if (strcmp(argv[i], "-u") == 0) {
            printf("My Realistic User ID: %d(ppos2eun)\nMy valid User ID: %d(ppos2eun)\n", getuid(), geteuid());
        } else if (strcmp(argv[i], "-g") == 0) {
            printf("My Realistic Group ID: %d(ppos2eun)\nMy Valid Group ID: %d(ppos2eun)\n", getgid(), getegid());
        } else if (strcmp(argv[i], "-i") == 0) {
            printf("my process number: [%d]\n", getpid());
        } else if (strcmp(argv[i], "-p") == 0) {
            printf("my parent's process number: [%d]\n", getppid());
        }
    }

    return 0;
}

