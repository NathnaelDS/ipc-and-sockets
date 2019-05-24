class ClientSocket {

    private:
        char* ip;
        int portNo;
        int transferMethod;

        char *msg;
        int sockfd, n_bytes;
        struct hostent *host;
        struct sockaddr_in serverAddress;
    
    
    public:
        ClientSocket(int method) {
            // Choose whether to use Stream or datagram
            transferMethod = method;

            // Add an if function to differentiate between
            /* Code */



            // Set up a socket file descriptor
            if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
            {
                perror("failed to get socket descriptor");
                exit(1);
            }
        }

        // Connect to a server given an IP and Port number
        void connectTo(char* ipAddress, int portNumber){
            ip = ipAddress;
            portNo = portNumber;
            
            // Get the binary form of the IP Address
            if((host = gethostbyname(ip)) == NULL)
            {
                perror("failed to resolve host");
                exit(1);
            }

            // setting up server address
            serverAddress.sin_family = AF_INET;
            serverAddress.sin_port = htons(portNo);
            serverAddress.sin_addr.s_addr = inet_addr(
                        inet_ntoa(*((struct in_addr *)host->h_addr)));
        }

        
        int send(char *message){
            // send message to server
            msg = (char *) malloc(64);
            char *message = "Client says Hello!";
            snprintf(msg, 64, "%s", message);

            n_bytes = sendto(sockfd, msg, 64, 0, (struct sockaddr *) &serverAddress, sizeof(serverAddress));
            if (n_bytes < 0)
            {
                printf("Error: failed to connect to %s:%d\n", host, serverAddress.sin_port);
                close(sockfd);
                exit(1);
            }
            free(msg);
            return 1;
        }
        

        char* receive(){
            // receive message from server
            msg = (char *) malloc(1024);
            n_bytes = recvfrom(sockfd, msg, BUFSIZE, 0,
                    (struct sockaddr *) &serverAddress,
                    (socklen_t *) &serverAddress);
            if (n_bytes < 0)
            {
                perror("failed to receive message");
                exit(1);
            }
            char *message = msg;
            // ... get the message
            free(msg);
            return message;
        }   
}