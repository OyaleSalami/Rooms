using System.Collections.Generic;

namespace NetworkClient
{
    class Client
    {
        public int NetworkId;
        public Endpoint endpoint;
        public TCP tcp;
        public UDP udp;

        public delegate void MessageHandler(Message message);
        public Dictionary<Message.Type, MessageHandler> messageHandlers;

        /// <summary>First function to be called</summary>
        public void Init()
        {
            messageHandlers = new Dictionary<Message.Type, MessageHandler>();
        }

        public void Connect(Endpoint ep)
        {
            endpoint = ep;
            //TODO: connect the TCP and UDP parts 
        }

        public void Send(Message.Mode mode, Message message)
        {
            if (mode == Message.Mode.Tcp)
            {
                tcp.Send(message);
            }

            if (mode == Message.Mode.Udp)
            {
                udp.Send(message);
            }

            if (mode == Message.Mode.Reliable)
            {
                udp.SendReliable(message);
            }
        }

        public void Disconnect()
        {
            NetworkId = -1;
            tcp.Disconnect();
            udp.Disconnect();
            endpoint.Reset();
        }

        /// <summary>Add a function for handling a particular type of message</summary>
        /// <param name="type">The type of message</param>
        /// <param name="handler">THe function that will handle it</param>
        /// <returns>True if a handler for the function is added, False if one exists already</returns>
        public bool AddHandler(Message.Type type, MessageHandler handler)
        {
            if (messageHandlers.ContainsKey(type))
            {
                return false;
            }

            messageHandlers.Add(type, handler);
            return true;
        }

        /// <summary>Remove a function from handling a particular type of message</summary>
        /// <param name="type">The type of message</param>
        /// <returns>True if a handler for the function is removed, False if it doesn't exists</returns>
        public bool RemoveHandler(Message.Type type)
        {
            if (messageHandlers.ContainsKey(type))
            {
                messageHandlers.Remove(type);
                return true;
            }
            return false;
        }
    }
}
