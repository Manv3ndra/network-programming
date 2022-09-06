#include <stdio.h>
#include <stdlib.h>
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
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd == -1)
    {
        printf("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    bzero(&servaddr, sizeof servaddr);
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(22000);
    if (connect(sock_fd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        printf("Connection failed");
        exit(EXIT_FAILURE);
    }
    while (1)
    {
        bzero(buffer, MAXLINE);
        fgets(buffer, MAXLINE, stdin);
        if (send(sock_fd, buffer, strlen(MAXLINE), 0) < 0)
        {
            printf("Send failed");
            exit(EXIT_FAILURE);
        }
        if (strcasecmp(buffer, "quit\n") == 0)
        {
            break;
        }
        bzero(buffer, MAXLINE);
        if (recv(sock_fd, buffer, MAXLINE, 0) < 0)
        {
            printf("Receive failed");
            exit(EXIT_FAILURE);
        }
        printf("Message from Server: %s", buffer);
    }
    close(sock_fd);
}
