#include <stdio.h>

int main(int argc, char* argv[])
{
	FILE *fp;
	int id, expired_date, stock;
	char name, category;
	fp = fopen(argv[5], "a");
	printf("%-4s %-8s %-7s %-4s %-3s\n", "id", "name", "category", "expired date", "stock");
	while (scanf("%d %s %s %d %d", &id, name, category, &expired_date, &stock)==6)
		fprintf(fp, "%d %s %s %d %d ", id, name, category, expired_date, stock);
	fclose(fp);
	return 0;
}
