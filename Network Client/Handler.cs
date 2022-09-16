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
    }
}
