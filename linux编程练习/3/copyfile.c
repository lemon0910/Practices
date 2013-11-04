#include <unistd.h>
#include <string.h>
#include <fnumberl.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define MAXN 1024

int main(int argc, char *argv[])
{
	int i, j, k, n;
	int number = 0;
	int fd[2]; 
	int readfile;
	int outfile;
	pid_t pid[1000];
	char buf[MAXN + 5];
	char inputfilepath[100];
	char outputfilepath[100];

	if(4 != argc)
	{
		printf("parameter error, please the number of process, input file path and output file path \n");
		exit(0);
	}
	n = atoi(argv[1]);
	strcpy(inputfilepath, argv[2]);
	strcpy(outputfilepath, argv[3]);

	if(pipe(fd) < 0)
	{
		printf("pipe create error\n");
		exit(0);
	}
	if((readfile = open(inputfilepath, O_RDONLY)) < 0)
	{
		printf("inputfile open error");
		exit(0);
	}

	for(i = 0; i < n; ++i)
	{
		if((pid[i] = fork()) < 0)
		{
			printf("fork error");
			break;
		}
		else if(0 == pid)
		{
			close(fd[1]);
			close(readfile);
			if((outfile = open(outputfilepath, O_WRONLY)) < 0)
			{
				printf("open output file error");
				exit(0);
			}
			while(1)
			{
				number = read(fd[0], buf, MAXN + 4);

				if(number <= 0)
				{
					close(outfile);
					break;
				}
				else
				{
					int len = *((int*)buf);
					int n = pwrite(outfile, buf + 4, number -4, len);
				}
			}
			break;
		}
	}

	if(pid > 0)
	{
		close(fd[0]);
		while(1)
		{
			int num;
			num = read(readfile, buf + 4, MAXN);
			if(num > 0)
			{
				memcpy(buf, &number, 4);
                number += num;
				num = write(fd[1], buf, MAXN + 4);
			}
			if(num <= 0)
			{
				close(readfile);
				break;
			}
		}
		for(i = 0; i < n; ++i)
		{
			waitpid(pid[i], 0, 0);
		}
	}

	return 0;
}
