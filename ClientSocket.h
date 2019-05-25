#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <sys/socket.h>

#define BUFSIZE 1024
class ClientSocket
{

  private:
    char *ip;
    int portNo;
    int transferMethod;

    char *msg;
    int sockfd, n_bytes;
    struct hostent *host;
    struct sockaddr_in serverAddress;

  public:
    ClientSocket(int method)
    {
        // Choose whether to use Stream or datagram
        transferMethod = method;

        // Set up a socket file descriptor. SOCK_DGRAM or SOCK_STREAM
        if (method == 1)
        {
            if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
            {
                perror("failed to get socket descriptor");
                exit(1);
            }
        }
        else if (method == 2)
        {
            if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
            {
                perror("failed to get socket descriptor");
                exit(1);
            }
        }
        else
        {
            perror("Usage: 1 for Datagram, 2 for Stream");
        }
    }

    // Connect to a server given an IP and Port number
    void connectTo(char *ipAddress, int portNumber)
    {
        ip = ipAddress;
        portNo = portNumber;

        printf("IP: %s and port: %d \n", ip, portNo);

        if (inet_pton(AF_INET, ipAddress, &serverAddress.sin_addr) < 1)
        {
            perror("pton failed");
        }

        // setting up server address
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_port = htons(portNo);

        printf("port: %d \n", serverAddress.sin_port);

        if (connect(sockfd, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
        {
            perror("Connect failed");
            exit(0);
        }
    }

    int send(char *message)
    {
        // send message to server
        n_bytes = sendto(sockfd, message, 1024, 0, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
        if (n_bytes < 0)
        {
            printf("Error: failed to connect to %s:%d\n", host->h_name, serverAddress.sin_port);
            close(sockfd);
            exit(1);
        }
        return 1;
    }

    char *receive()
    {
        // receive message from server
        char message[1024];
        // n_bytes = recv(sockfd, (char *)message, 64, MSG_WAITALL);
        // n_bytes = recvfrom(sockfd, message, 1024, MSG_WAITALL,
        //                    (struct sockaddr *)&serverAddress,
        //                    (socklen_t *)&serverAddress);
        read(sockfd, message, 1024);
        if (n_bytes < 0)
        {
            perror("failed to receive message");
            exit(1);
        }
        message[n_bytes - 1] = '\0';
        printf("%s\n", message);
        return message;
    }
};