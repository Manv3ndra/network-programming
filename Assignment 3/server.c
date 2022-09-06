#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main()
{
    int listen_fd;
    char sendline[100];
    char recvline[100];
    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(22000);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    bind(listen_fd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    listen(listen_fd, 10);
    int comm_fd = accept(listen_fd, (struct sockaddr *)NULL, NULL);
    while (1)
    {
        bzero(sendline, 100);
        bzero(recvline, 100);
        if (recv(comm_fd, recvline, 100, 0) == 0)
        {
            break;
        }
        printf("Client: %s", recvline);
        printf("Server: ");
        fgets(sendline, 100, stdin);
        send(comm_fd, sendline, strlen(sendline), 0);
    }
    close(comm_fd);
}