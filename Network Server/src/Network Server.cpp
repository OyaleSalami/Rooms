#include <iostream>
#include "Debug.h"
#include "Server.h"

int main()
{
    Network::Server server;

    server.Start(9900);
    
    while(server.isRunning == true)
    {
        server.Update();
    }
}

