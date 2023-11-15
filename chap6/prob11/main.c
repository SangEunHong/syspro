#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <grp.h>
#include <pwd.h>
#include <string.h>
#include <unistd.h>

char type(mode_t);
char *perm(mode_t);
void printStat(char*, char*, struct stat*, int, int, int);

int main(int argc, char **argv)
{
    DIR *dp;
    char *dir;
    struct stat st;
    struct dirent *d;
    char path[BUFSIZ+1];
    int size = 0;
    int links = 0;
    int owner = 0;

    // Parse options
    int opt;
    while ((opt = getopt(argc, argv, "sno")) != -1) {
        switch (opt) {
        case 's':
            size = 1;
            break;
        case 'n':
            links = 1;
            break;
        case 'o':
            owner = 1;
            break;
        default: /* '?' */
            fprintf(stderr, "Usage: %s [-s] [-n] [-o] [dir]\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    if (optind >= argc) {
        dir = ".";
    } else {
        dir = argv[optind];
    }

    if ((dp = opendir(dir)) == NULL)
        perror(dir);

    while ((d = readdir(dp)) != NULL) {
        sprintf(path, "%s/%s", dir, d->d_name);
        if (lstat(path, &st) < 0)
            perror(path);
        else
            printStat(path, d->d_name, &st, size, links, owner);
    }
    closedir(dp);
    exit(0);
}

void printStat(char *pathname, char *file, struct stat *st, int size, int links, int owner)
{
    printf("%5d ", (long)st->st_blocks);
    printf("%c%s ", type(st->st_mode), perm(st->st_mode));
    if (links) {
        printf("%3u ", (unsigned long)st->st_nlink);
    }
    if (owner) {
        printf("%s ", getpwuid(st->st_uid)->pw_name);
    }
    printf("%s ", getgrgid(st->st_gid)->gr_name);
    if (size) {
        printf("%9d ", (long)st->st_size);
    }
    printf("%.12s ", ctime(&st->st_mtime)+4);
    printf("%s\n", file);
}
char type(mode_t mode)
{
	if (S_ISREG(mode))
		return('-');
	if (S_ISDIR(mode))
		return('d');
	if (S_ISCHR(mode))
		return('c');
	if (S_ISBLK(mode))
		return('b');
	if (S_ISLNK(mode))
		return('l');
	if (S_ISFIFO(mode))
		return('p');
	if (S_ISSOCK(mode))
		return('s');
}
char* perm(mode_t mode)
{
	static char perms[10];
	strcpy(perms, "--------");

    	for (int i=0; i<3;i++){
		if (mode & (S_IRUSR >> i*3))
			perms[i*3] = 'r';
             	if (mode & (S_IWUSR >> i*3))
                    	perms[i*3 +1] = 'w';
            	if (mode & (S_IXUSR >> i*3))
                    	perms[i*3 + 2] = 'x';
    }
    return(perms);
}
