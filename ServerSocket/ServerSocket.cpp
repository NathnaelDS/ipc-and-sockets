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
