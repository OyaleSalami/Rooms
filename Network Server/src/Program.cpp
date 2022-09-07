#include "Server.h"
#include <iostream>

using namespace std::literals::chrono_literals;
using namespace Network;

static NetworkSystem network;
static Server server(10, 8088, "0.0.0.0");

void ListenAndAccept()
{
    while (server.listening == true)
    {
        //Listen on this socket with 100 backlogs...
        if (listen(server.ListenSocket.handle, 100) == 0)
        {
            sockaddr_in addr = {};
            int len = sizeof(sockaddr_in);

            int _id = server.GetNext();

            server.clients[_id].id = _id; //Set the id for the Client class
            server.clients[_id].isConnected = true;
            server.clients[_id].tcp = accept(server.ListenSocket.handle, (sockaddr*)&addr, &len);
            server.clients[_id].Update();

            Debug::Log("Accepted a client: ");
        }
        else
        {
            int error = WSAGetLastError();
            Debug::Error("Error while listening: " + std::to_string(error));
        }
        std::this_thread::sleep_for(1s);
    }
}

int main()
{
    if (network.Initialize() == true)
    {
        server.Start(); //Create and Bind socket

        std::thread update(ListenAndAccept); //Async listen and accept
        
        std::cin.get();

        while (true)
        {
            std::string text;
            Message message;
            std::cin >> text;

            message.Write(text);
            server.SendToAll(SendMode::Tcp, message);
        }
    }
    network.ShutDown();
}