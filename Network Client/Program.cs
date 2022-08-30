using System;
using Rooms;

class Program
{
    static Client gameClient = new Client();
    static void Main(string[] args)
    {
        gameClient.Connect(new Endpoint(8088, "127.0.0.1"));

        
        Console.WriteLine("Hello World");
        Console.Read();
    }
}

