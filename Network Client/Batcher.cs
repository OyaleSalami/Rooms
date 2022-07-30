using System.Collections.Generic;

namespace NetworkClient
{
    /// <summary>A unique batching class to batch a particular Mode of messages together</summary>
    class Batcher
    {
        private List<Message> queue;
        private Message.Mode mode;
        public Batcher(Message.Mode m)
        {
            this.mode = m;
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
