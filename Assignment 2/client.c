#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main()
{
    int sock_fd;
    struct sockaddr_in servaddr;
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof servaddr);
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(22000);
    connect(sock_fd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    while (1)
    {
        char sendline[100];
        char recvline[100];
        bzero(sendline, 100);
        bzero(recvline, 100);
        fgets(sendline, 100, stdin);
        send(sock_fd, sendline, strlen(sendline), 0);
        if (strcasecmp(sendline, "quit\n") == 0)
        {
            break;
        }
        recv(sock_fd, recvline, 100, 0);
        printf("Message from Server: %s", recvline);
    }
    close(sock_fd);
}
