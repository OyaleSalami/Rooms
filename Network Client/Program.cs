using System;
using Rooms;

class Program
{
    static Client gameClient = new Client();
    static void Main(string[] args)
    {
        gameClient.Connect(new Endpoint(8088, "127.0.0.1"));

        Console.Read();
        Console.WriteLine("Hello World");
        
        while (true)
        {
            Console.Read();
            Message message = new Message();
            message.Add("Data received good:: ");

            gameClient.Send(IMessage.Mode.Tcp, message);
            Console.WriteLine("Sent");
        }
    }
}

