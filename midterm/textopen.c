#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    int i;

    for(i = 1; i<3; i++){
        FILE *f;
        int c;

        f = fopen(argv[i], "r");
        while((c=fgetc(f)) != EOF){
            if(putchar(c) < 0) 
		    exit(1);
        }
        fclose(f);
    }
        exit(0);
}
