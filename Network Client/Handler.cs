namespace Rooms
{
    class Handler
    {
        public static void Auth(Message message)
        {
            string hash = message.ReadString();
        }
    }
}
