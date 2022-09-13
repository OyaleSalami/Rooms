#include "Server.h"
#include <iostream>
#include <thread>

using namespace Network;

static NetworkSystem network;
static Server server(10, 8088, "0.0.0.0");


void Chat()
{
    while (true)
    {
        std::string text;
        Message message(MessageType::Chat);
        std::cin >> text;
        message.Write(text);
        message.InsertLength();

        server.SendToAll(SendMode::Tcp, message);
    }
}

int main()
{
    if (network.Initialize() == true)
    {
        server.Start(); //Create and Bind the listen socket
        
        std::thread type(Chat);
        while (server.running == true)
        {
            server.Update();
        }
    }
    network.ShutDown();
}