#include "Server.h"
#include <iostream>

using namespace Network;

int main()
{
    NetworkSystem network;
    Server server(10);

    if (network.Initialize() == true)
    {
        std::cout << "Network Initialized" << std::endl;
        server.Start();

        while (server.running == true)
        {
            server.Update();
            Sleep(1);
        }
    }
    else
    {
        std::cout << "Network Not Initialized" << std::endl;
    }
    network.ShutDown();
}