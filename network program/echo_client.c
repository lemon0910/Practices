#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

#define MAXLINE 1000
#define SERV_PORT 9999

void client(FILE *fp, int sockfd);

int main(int argc, char *argv[]) 
{
    int sockfd;
    struct sockaddr_in servaddr;

    if(argc != 2)
    {
        printf("usage : tcpcli IPaddress\n");
        return -1;
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0)
    {
        printf("socket error\n");
        return -1;
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

    if(connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
    {
        printf("connect error\n");
        return -1;
    }

    client(stdin, sockfd);

    return 0;
}

void client(FILE *fp, int sockfd)
{
    char sendline[MAXLINE], recvline[MAXLINE];

    while(fgets(sendline, MAXLINE, fp) != NULL)
    {
        write(sockfd, sendline, strlen(sendline));
        int n = read(sockfd, recvline, MAXLINE);
        if(n > 0)
        {
            recvline[n] = '\0';
        }

        fputs(recvline, stdout);
    }
}
