#include "../include/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>

int main(int argc, char* argv[])
{
	DIR *dir         = NULL;
	struct dirent *d = NULL;

	if (!check_args(argc, 2, "Usage: my_ls_linux.exe <directory>"))
    {
       return 1;
    }

    dir = opendir(argv[1]);
	
	if (dir == NULL)
	{
		perror("opendir");
		return errno;
	}

	while( (d = readdir(dir)) != NULL ) 
	{
		if (strcmp(d->d_name, ".") && strcmp(d->d_name, ".."))
		{
			printf("%s ", d->d_name);	
		}
	}
	printf("\n");

	closedir(dir);
}