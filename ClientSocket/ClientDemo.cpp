#include "ClientSocket.h"

int main(int argc, char const *argv[])
{
    // Pass UDP for Datagram socket, TCP for Stream socket
    ClientSocket cs("TCP");

    // cs.connectTo("192.168.1.102", 5000);
    cs.connectTo("127.0.0.1", 3434);
    cs.send("nope");
    cs.receive();
    return 0;
}
