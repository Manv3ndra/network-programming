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
    struct sockaddr_in servaddr, cliaddr;
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);
    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    int n;
    socklen_t len;
    while (1)
    {
        bzero(buffer, MAXLINE);
        bzero(sendline, MAXLINE);
        len = sizeof(cliaddr);
        n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, (struct sockaddr *)&cliaddr, &len);
        buffer[n] = '\0';
        printf("Client : %s", buffer);
        if (strcasecmp(buffer, "exit\n") == 0)
        {
            break;
        }
        printf("Server : ");
        fgets(sendline, MAXLINE, stdin);
        sendto(sockfd, (char *)sendline, strlen(sendline), MSG_SEND, (const struct sockaddr *)&cliaddr, len);
    }
    close(sockfd);
    return 0;
}
