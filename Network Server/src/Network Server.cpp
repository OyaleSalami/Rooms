#include "Server.h"

#pragma comment (lib, "ws2_32.lib")
#include <Winsock2.h>
#include <Ws2tcpip.h>


int main()
{
    int iResult;
    WSADATA wsaData;
    Network::Server server(10);

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0)
    {
        printf("WSAStartup failed: %d\n", iResult);
        return 1;
    }

    server.Start();

    while (server.isRunning == true)
    {
        server.Update();
    }
}