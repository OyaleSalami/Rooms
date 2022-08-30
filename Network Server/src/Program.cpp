#include "Server.h"
#include <iostream>

using namespace Network;

int main()
{
    NetworkSystem network;
    Server server(10, 8088);

    if (network.Initialize() == true)
    {
        Debug::Log("Network Initialized");

        server.Start();

        while (server.running == true)
        {
            server.Update();
            Sleep(1);
        }
    }
    else
    {
        Debug::Log("Network Not Initialized");
    }
    network.ShutDown();
}