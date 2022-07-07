using System.Collections.Generic;

namespace NetworkClient
{
    class Batcher
    {
        private List<Message> queue;
        public Message.Mode mode { get; set; }
        public Batcher(Message.Mode m)
        {
            mode = m;
            queue = new List<Message>();
        }

        public void AddMessage(Message message)
        {
            queue.Add(message);
        }

        public void Send()
        {

        }
    }
}
