#include "ServerSocket.h"

ServerSocket::ServerSocket()
{
    //create socket file descriptor and use ipv4 socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("Error getting a socket descriptor");
        exit(1);
    }
}

void ServerSocket::bindAndListen(int portNumber, int connectionLimit)
{
    maxConn = connectionLimit;
    
    //Set server address
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddress.sin_port = htons(portNumber);

    //Bind server to port
    if ((bind(sockfd, (struct sockaddr *)&serverAddress, sizeof(struct sockaddr_in))) < 0)
    {
        perror("Unable to bind server to port");
        exit(1);
    }
}

void ServerSocket::startServer()
{
    while (1)
    {
        char buffer[1024];
        if (recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&clientAddress, (socklen_t *)&addrlen) < 0)
        {
            perror("recvfrom error");
            exit(1);
        }
        else
        {
            //request successfully accepted
            pid = fork();
            if (pid == 0)
            {
                //Handl the request on the child process
                buf = (char *)malloc(1024);
                snprintf(buf, len, "%ld: %s\n", s_ack, buffer);
                n_bytes = sendto(sockfd, buf, 1024, 0, (struct sockaddr *)&clientAddress, sizeof(clientAddress));
                if (n_bytes < 0)
                {
                    perror("can not send data");
                    exit(1);
                }
                else
                {
                    s_ack++;
                }
            }
            else
            {
                wait(NULL);
            }
        }
    }
}