using System;

namespace Rooms
{
    class Handler
    {
        public static void Auth(Message message)
        {
            string hash = message.ReadString();
        }

        public static void Chat(Message message)
        {
            string text = message.ReadString();

            Console.WriteLine(text);
        }
    }
}
