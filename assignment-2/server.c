#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#define MAXLINE 1024

int main()
{
    int listen_fd;
    struct sockaddr_in servaddr;
    char buffer[MAXLINE];
    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_fd == -1)
    {
        printf("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(22000);
    if (bind(listen_fd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        printf("Bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(listen_fd, 10) < 0)
    {
        printf("Listen failed");
        exit(EXIT_FAILURE);
    }
    int comm_fd = accept(listen_fd, (struct sockaddr *)NULL, NULL);
    while (1)
    {
        bzero(buffer, MAXLINE);
        if (recv(comm_fd, buffer, MAXLINE, 0) < 0)
        {
            printf("Receive failed");
            exit(EXIT_FAILURE);
        }
        printf("Message from Client: %s", buffer);
        if (strcasecmp(buffer, "exit\n") == 0)
        {
            break;
        }
        printf("Echoing back : %s", buffer);
        if (send(comm_fd, buffer, MAXLINE, 0) < 0)
        {
            printf("Send failed");
            exit(EXIT_FAILURE);
        }
    }
    close(comm_fd);
}