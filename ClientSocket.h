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
    }

    void connectTo(char *ipAddress, int portNumber)
    {
    }

    int send(char *message)
    {
    }

    char *receive()
    {
    }
}