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
        server.Update();

        while (server.running == true)
        {
            std::string text = "";
            std::cin >> text;

            Message message(MessageType::Chat);
            message.Write(text);

            server.SendToAll(SendMode::Tcp, message);

            std::cin.get();
            Sleep(1);
        }
    }
    else
    {
        Debug::Log("Network Not Initialized");
    }
    network.ShutDown();
}