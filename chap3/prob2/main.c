#include <stdio.h>
#include <string.h>
#include "copy.h"
char str[MAXLINE][MAXLINE];
char longest[MAXLINE];

int main() {
 
    int i, j;
    int count = 0;
    
    while(count<5){
        scanf(" %s", str[count]);
        count++;
    }

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4 - i; j++) {
            if (strlen(str[j]) < strlen(str[j + 1])) {
                copy(str[j], longest);
                copy(str[j+1], str[j]);
                copy(longest, str[j+1]);
                
            }
        }
    }
    for (i = 0; i < 5; i++) {
        printf("%s\n", str[i]);
    }

    return 0;
}
