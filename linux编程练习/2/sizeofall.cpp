#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include <sys/stat.h>
#include <dirent.h>
#include <map>
#include <iostream>
using namespace std;

int sizeofall(char *filepath)
{
	struct stat statbuf;
	struct dirent *dirp;
	DIR *dp;
	char *ptr;
	int ret = 0;
    int temp;
	map<string, int> structure;
    map<string, int>::iterator it;

	if(lstat(filepath, &statbuf) < 0)
	{
		perror("lstat error : ");
		return -1;
	}
	if(0 == S_ISDIR(statbuf.st_mode))
	{
		perror("the file is not a directory");
		return -1;
	}

	ptr = filepath + strlen(filepath);
	*ptr++ = '/';
	if(NULL == (dp = opendir(filepath)))
	{
		perror("opendir error : ");
		return -1;
	}

	while((dirp = readdir(dp)) != NULL)
	{
		if(strcmp(dirp->d_name, ".") == 0 || strcmp(dirp->d_name, "..") == 0)
			continue;
		strcpy(ptr, dirp->d_name);
		if(lstat(filepath, &statbuf) < 0)
		{
			perror("lstat error : ");
			return -1;
		}
		if(S_ISDIR(statbuf.st_mode))
		{
			temp = sizeofall(filepath);
            strcpy(ptr, dirp->d_name);
		}
		else
		{
            temp = statbuf.st_size;
            ret += temp;
		}
        structure[filepath] = temp;
	}

    for(it = structure.begin(); it != structure.end(); ++it)
    {
        printf("%s : %d\n", it->first.c_str(), it->second);
    }
	return ret;
}

int main(int argc, char *argv[])
{
	if(2 != argc)
	{
		printf("parameter error, the format should be : filepath\n");
		exit(0);
	}

	char filepath[1000];
    int len;
    memset(filepath, 0, sizeof(filepath));
	strcpy(filepath, argv[1]);
    len = strlen(filepath);
    if('/' == filepath[len -1] && len > 1)
    {
        filepath[len - 1] = '\0';
    }
	sizeofall(filepath);

	return 0;
}
