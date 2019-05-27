#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>

class ServerSocket
{
  private:
    int sockfd, n_bytes, len, pid, maxConn;
    char *buffer;
    char *buf;
    long int s_ack = 1;
    struct sockaddr_in clientAddress, serverAddress;
    socklen_t addrlen = sizeof(struct sockaddr_in);

  public:
    ServerSocket();
    void bindAndListen(int portNumber, int connectionLimit=10);
    void startServer();
};
