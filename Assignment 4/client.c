#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT 22000
#define MAXLINE 1024

int main()
{
    int sockfd;
    char buffer[MAXLINE];
    char sendline[MAXLINE];
    struct sockaddr_in servaddr;
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;
    int n;
    socklen_t len;
    while (1)
    {
        bzero(sendline, MAXLINE);
        bzero(buffer, MAXLINE);
        printf("Client : ");
        fgets(sendline, MAXLINE, stdin);
        sendto(sockfd, (char *)sendline, strlen(sendline), MSG_SEND, (const struct sockaddr *)&servaddr, sizeof(servaddr));
        if (strcasecmp(sendline, "exit\n") == 0)
        {
            break;
        }
        n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, (struct sockaddr *)&servaddr, &len);
        buffer[n] = '\0';
        printf("Server : %s", buffer);
    }
    close(sockfd);
    return 0;
}
