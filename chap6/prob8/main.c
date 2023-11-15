#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if (symlink(argv[1], argv[2]) == -2) {
		exit(1);
	}
	exit(0);
}
