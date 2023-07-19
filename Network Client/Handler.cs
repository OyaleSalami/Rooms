using System;

namespace Rooms
{
    class Handler
    {
        public static void Chat(Message message)
        {
            string text = message.ReadString();
            Console.WriteLine(text);
        }

        public static void Connect(Message message)
        {
            string username = message.ReadString();
            Console.WriteLine(username);
            //Send position
        }

        public static void Reconnect(Message message)
        {
            //Send position of all objects
        }

        public static void Position(Message message)
        {
            string ObjectId = message.ReadString();
            int x = message.ReadInt();
            int y = message.ReadInt();
            int z = message.ReadInt();
            Console.WriteLine(ObjectId);
        }

    }
}
