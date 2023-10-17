#include <stdio.h>
#include "student"

int main(int argc, char* argv[]) {
	struct student rec;
	FILE *fp;
	if (argc != 2) {
		fprintf(stderr, "How to use: %s FileName\n", argv[0]);
		return 1;
	}
	fp = fopen(argv[1], "r");
	printf("%-9s %-7s %-4s\n", 'StudentID", "Name", "Score");
	while (fscanf(fp, "%d %s %d", &rec.id, rec.name, &rec.score
