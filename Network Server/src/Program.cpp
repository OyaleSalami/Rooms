#include "Server.h"
#include <iostream>

using namespace Network;
using namespace std::literals::chrono_literals;


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
            server.clients[_id].tcp = accept(server.ListenSocket.handle, (sockaddr*)&addr, &len);

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

void Receive()
{
    int i = server.GetNext();
    Message message = {};

    while (server.running == true)
    {
        if (server.clients[i - 1].tcp.Recv(message) == NetResult::Success)
        {
            std::string text;
            message.Read(text);

            std::cout << "Client: ";
            std::cout << text << std::cin.get();
        }
        else
        {
            int error = WSAGetLastError();
            std::cout << "ERRRRROROROROR: " << error << std::cin.get();
        }
        std::this_thread::sleep_for(1s);
    }
}

int main()
{
    if (network.Initialize() == true)
    {
        server.Start(); //Create and bind socket

        std::thread update(ListenAndAccept); //Async listen and accept
        
        std::cin.get();
        std::thread receive(Receive);

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