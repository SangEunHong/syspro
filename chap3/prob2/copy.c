#include <stdio.h>

void copy(cahr from[], char to[]){
	int i;
	i = 0;
	while((to[i] = from[i])) != '\0')
		++i;
}
