#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#define MAXLINE 1024

int main()
{
    int listen_fd;
    struct sockaddr_in servaddr;
    char buffer[MAXLINE];
    bzero(&servaddr, sizeof(servaddr));
    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(22000);
    bind(listen_fd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    listen(listen_fd, 10);
    int comm_fd = accept(listen_fd, (struct sockaddr *)NULL, NULL);
    while (1)
    {
        bzero(buffer, MAXLINE);
        recv(comm_fd, buffer, MAXLINE, 0);
        printf("Client: %s", buffer);
        if (strcasecmp(buffer, "exit\n") == 0)
        {
            break;
        }
        printf("Server: ");
        fgets(buffer, MAXLINE, stdin);
        send(comm_fd, buffer, MAXLINE, 0);
    }
    close(comm_fd);
}