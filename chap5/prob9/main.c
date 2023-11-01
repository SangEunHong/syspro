#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 100

void reverseAndPrint(FILE *file) {
    char lines[MAX_LINE_LENGTH][MAX_LINE_LENGTH];
    int count = 0;

    while (fgets(lines[count], MAX_LINE_LENGTH, file) != NULL) {
        count++;
    }

    for (int i = count - 1; i >= 0; i--) {
        printf("%s", lines[i]);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    reverseAndPrint(file);
    fclose(file);

    return EXIT_SUCCESS;
}
