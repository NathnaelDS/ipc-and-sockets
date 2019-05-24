class ClientSocket {

    private:
        char* ip;
        int portNo;
        int transferMethod;

        char *msg;
        int sockfd, n_bytes;
        struct hostent *host;
        struct sockaddr_in serverAddress;
    
    
     
}