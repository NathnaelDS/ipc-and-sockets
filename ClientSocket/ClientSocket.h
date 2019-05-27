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
    char *ip, *transferMethod, *msg;
    int portNo, sockfd, n_bytes;
    struct hostent *host;
    struct sockaddr_in serverAddress;

  public:
    ClientSocket(char *method);

    void connectTo(char *ipAddress, int portNumber);

    int send(char *message);

    char *receive();
};