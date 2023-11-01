#include <stdio.h>
#include <string.h>

#define MAX_LINES 4
#define MAX_LENGTH 100

char savedText[MAX_LINES][MAX_LENGTH];

void readAndSaveText(FILE *file) {
    int line = 0, index = 0;
    char ch;

    while ((ch = fgetc(file)) != EOF && line < MAX_LINES) {
        if (ch == '\n') {
            savedText[line++][index] = '\0';  
            index = 0;
        } else {
            savedText[line][index++] = ch;
        }
    }
}

int main() {
    FILE *file = fopen("test.txt", "r");

    if (file == NULL) {
        return 1;
    }

    readAndSaveText(file);

    printf("File read success\n");
    printf("Total Line : %d\n", MAX_LINES);
    printf("You can choose 1 ~ %d Line\n", MAX_LINES);
    printf("Pls 'Enter' the line to select : ");

    char option[20];
    scanf("%s", option);

    int start, end;

    if (option[0] == '*') {
        for (int i = 0; i < MAX_LINES; i++) {
            printf("%s\n", savedText[i]);
        }
    } else if (sscanf(option, "%d-%d", &start, &end) == 2) {
        for (int i = start - 1; i < end && i < MAX_LINES; i++) {
            printf("%s\n", savedText[i]);
        }
    } else {
        char *token = strtok(option, ",-");
        while (token != NULL) {
            sscanf(token, "%d", &start);
            printf("%s\n", savedText[start - 1]);
            token = strtok(NULL, ",-");
        }
    }

    fclose(file);
    return 0;
}
