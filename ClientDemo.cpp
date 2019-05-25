#include "ClientSocket.h"

int main(int argc, char const *argv[])
{
    // Pass 1 for Datagram socket, 2 for Stream socket

    ClientSocket cs(1);

    cs.connectTo("192.168.1.104", 6001);
    cs.send("chu");
    cs.receive();
    return 0;
}
