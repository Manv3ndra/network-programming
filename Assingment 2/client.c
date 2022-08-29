#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    int sockfd;
    struct sockaddr_in servaddr;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof servaddr);
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(22000);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    while (1)
    {
        char sendline[100];
        char recvline[100];
        bzero(sendline, 100);
        bzero(recvline, 100);
        fgets(sendline, 100, stdin); /*stdin = 0 , for standard input */
        if (strcmp(sendline, "quit\n") == 0)
        {
            break;
        }
        send(sockfd, sendline, strlen(sendline), 0);
        recv(sockfd, recvline, 100, 0);
        printf("Message from Server: %s", recvline);
    }
    close(sockfd);
}
