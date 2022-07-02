using System.Collections.Generic;

namespace Network_Client
{
    class Batcher
    {
        private Dictionary<Message.Type, Message> messages;

        public Batcher()
        {
            messages = new Dictionary<Message.Type, Message>();
        }

        public void AddMessage(Message _message)
        {

        }

        public void Send(Client client)
        {

        }
    }
}
