#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <arpa/inet.h>
#include <errno.h>

#define LISTENQ 1000
#define MAXLINE 1000
#define SERV_PORT 9999

void echo(int fd);

int main(int argc, char *argv[])
{
    int listenfd, connfd;
    socklen_t clilen;
    struct sockaddr_in cliaddr, servaddr;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(listenfd < 0)
    {
        printf("socket create error\n");
        return -1;
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    if(bind(listenfd, (const struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
    {
        printf("bind error\n");
        return -1;
    }

    if(listen(listenfd, LISTENQ) < 0)
    {
        printf("listen error\n");
        return -1;
    }

    for( ; ; )
    {
        clilen = sizeof(cliaddr);
        connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &clilen);

        if(connfd < 0)
        {
            printf("accept error\n");
            return -1;
        }

        echo(connfd);

        close(connfd);
    }

    return 0;
}

void echo(int fd)
{
    ssize_t n;
    char buf[MAXLINE];

    again:
    while((n = read(fd, buf, MAXLINE)) > 0)
    {
        write(fd, buf, n);
    }

    if(n < 0 && errno == EINTR)
        goto again;

    else if(n < 0)
        printf("read error\n");
}
