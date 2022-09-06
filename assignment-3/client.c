#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define MAXLINE 1024

int main()
{
    int sock_fd;
    struct sockaddr_in servaddr;
    char buffer[MAXLINE];
    bzero(&servaddr, sizeof servaddr);
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(22000);
    connect(sock_fd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    while (1)
    {
        bzero(buffer, MAXLINE);
        printf("Client: ");
        fgets(buffer, MAXLINE, stdin);
        send(sock_fd, buffer, MAXLINE, 0);
        if (strcasecmp(buffer, "exit\n") == 0)
        {
            break;
        }
        bzero(buffer, MAXLINE);
        recv(sock_fd, buffer, MAXLINE, 0);
        printf("Server: %s", buffer);
    }
    close(sock_fd);
}
