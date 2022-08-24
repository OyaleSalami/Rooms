#include <Winsock2.h>
#include <Ws2tcpip.h>
#include "Server.h"

using namespace Network;

int main()
{
    NetworkSystem network;

    network.Initialize();

    network.ShutDown();
}