using Rooms;
using System;

class Program
{
    public static Client gameClient = new Client();

    static void Main(string[] args)
    {
        gameClient.Connect(new Endpoint(8088, "127.0.0.1"));

        gameClient.AddHandler(IMessage.Type.chat, Handler.Chat);

        while (true)
        {
            string text = Console.ReadLine();
            Message message = new Message(IMessage.Type.chat);
            message.Add(text);
            message.Seal();

            gameClient.Send(IMessage.Mode.Tcp, message);
            Console.WriteLine("Sent");
        }
    }
}

