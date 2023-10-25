#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int i;

    for (i = 1; i < argc; i++) {
        FILE *fp;
        int c;
        int line_number = 1;  
        int should_number_lines = 0;  

        if (argv[i][0] == '-' && argv[i][1] == 'n' && argv[i][2] == '\0') {
            should_number_lines = 1;
            continue;
        }

        fp = fopen(argv[i], "r");
        if (!fp) {
            perror(argv[i]);
            exit(1);
        }

        if (should_number_lines) {
            printf("%6d\t", line_number);
            line_number++;
        }

        while ((c = fgetc(fp)) != EOF) {
            if (should_number_lines && c == '\n') {
                printf("%6d\t", line_number);
                line_number++;
            }

            if (putchar(c) == EOF) {
                perror("Error writing to stdout");
                exit(1);
            }
        }

        fclose(fp);
    }

    return 0;
}

