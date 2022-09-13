using Rooms.Transport;
using System;
using System.Collections.Generic;

namespace Rooms
{
    /// <summary>Abstraction for a Client on a network</summary>
    public class Client
    {
        /// <summary>Identifies the Client on the network</summary>
        public int NetworkId;
        /// <summary>Endpoint that the Client is bound to</summary>
        public Endpoint endpoint;
        /// <summary>Bool to show if the Client is connected</summary>
        public bool isConnected = false;

        private TCP tcp; //Client's TCP Socket
        private UDP udp; //Client's UDP Socket

        /// <summary>A template for functions that handle messages</summary>
        /// <param name="message">Type of Message to be handled</param>
        public delegate void MessageHandler(Message message);
        /// <summary>A dictionary to store all function handlers matching them to a key(type)</summary>
        public Dictionary<int, MessageHandler> messageHandlers;

        ///<summary>Initializes the message handler dictionary</summary>
        private void Init()
        {
            messageHandlers = new Dictionary<int, MessageHandler>();
        }

        /// <summary>Attempt to connect the server to a client(TCP and UDP)</summary>
        /// <param name="ep">Endpoint of the remote host</param>
        public void Connect(Endpoint ep)
        {
            //Check if the endpoint is valid
            if (ep.IsValid() == false)
            {
                throw new Exception("Endpoint is not valid");
            }
            //Check if the client is already connected
            if (isConnected == true)
            {
                throw new Exception("Disconnect before trying to connect again!");
            }
            endpoint = ep;
            Init();
            tcp = new TCP(); //Create TCP Socket
            udp = new UDP(ep); //Create and Bind UDP socket to remote endpoint

            tcp.Connect(ep); //Attempts to connect the TCP socket
            udp.Connect(); //Attempts to connect the UDP socket
        }

        /// <summary>Sends a message to the remote host that the client is bound to</summary>
        /// <param name="mode">Transport used to send the message</param>
        /// <param name="message">Message to bo sent</param>
        public void Send(Message.Mode mode, Message message)
        {
            //message.Add(NetworkId); //Adds the client's ID to the message
            //message.Seal(); //Readies the message for sending

            if (mode == Message.Mode.Tcp)
            {
                tcp.Send(message); //Sends a message via TCP
            }
            else if (mode == Message.Mode.Udp)
            {
                udp.Send(message); //Sends a message via UDP(Unreliable)
            }
            else if (mode == Message.Mode.Reliable)
            {
                udp.SendReliable(message); //Sends a message via UDP(Reliable)
            }
            else
            {
                throw new Exception("Mode not recognized");
            }
        }

        ///<summary>Disconnect the client from the server</summary>
        public void Disconnect()
        {
            tcp.Disconnect();
            udp.Disconnect();
            endpoint.Reset();
            NetworkId = -1;
        }

        /// <summary>Add a function to handle a particular type of message</summary>
        /// <param name="type">The type of message</param>
        /// <param name="handler">The function that will handle it</param>
        /// <returns>True if a handler for the function is added, False if one exists already</returns>
        public bool AddHandler(Message.Type type, MessageHandler handler)
        {
            if (messageHandlers.ContainsKey((int)type))
            {
                return false;
            }

            messageHandlers.Add((int)type, handler);
            return true;
        }

        /// <summary>Remove a function from handling a particular type of message</summary>
        /// <param name="type">The type of message</param>
        /// <returns>True if a handler for the function is removed, False if it doesn't exists</returns>
        public bool RemoveHandler(Message.Type type)
        {
            if (messageHandlers.ContainsKey((int)type))
            {
                messageHandlers.Remove((int)type);
                return true;
            }
            return false;
        }
    }
}
