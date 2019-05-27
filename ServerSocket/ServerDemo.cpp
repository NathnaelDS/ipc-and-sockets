#include "ServerSocket.h"

int main(int argc, char const *argv[])
{

    // Initialize the server socket
    ServerSocket ss;

    // Provide port for our server socket.
    // If using TCP server, optionally add a second argument for number of connections allowed.
    ss.bindAndListen(3434);
    

    // Start the server
    ss.startServer();
    return 0;
}