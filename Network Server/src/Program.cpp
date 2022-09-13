#include "Server.h"
#include <iostream>

using namespace Network;

static NetworkSystem network;
static Server server(10, 8088, "0.0.0.0");

int main()
{
    if (network.Initialize() == true)
    {
        server.Start(); //Create and Bind the listen socket
        
        while (server.running == true)
        {
            server.Update();

            std::string text;
            Message message(MessageType::Chat);
            std::cin >> text;
            message.Write(text);

            server.SendToAll(SendMode::Tcp, message);
        }
    }
    network.ShutDown();
}