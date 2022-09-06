#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main()
{
    int sock_fd;
    char sendline[100];
    char recvline[100];
    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof servaddr);
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(22000);
    connect(sock_fd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    while (1)
    {
        bzero(sendline, 100);
        bzero(recvline, 100);
        printf("Client: ");
        fgets(sendline, 100, stdin);
        send(sock_fd, sendline, strlen(sendline), 0);
        if (strcasecmp(sendline, "exit\n") == 0)
        {
            break;
        }
        recv(sock_fd, recvline, 100, 0);
        printf("Server: %s", recvline);
    }
    close(sock_fd);
}
