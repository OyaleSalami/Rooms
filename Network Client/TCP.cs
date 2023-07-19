using System;
using System.Net.Sockets;

namespace Rooms.Transport
{
    ///<summary>Refers to the transport mode by which a message is to be sent</summary>
    public enum Mode
    {
        /// <summary>A message to be broadcasted</summary>
        Multicast = 1,
        /// <summary>A message to be sent over TCP</summary>
        Tcp,
        /// <summary>A message to be sent over UDP(Unreliable)</summary>
        Udp,
        /// <summary>A message to be sent over UDP(Reliable)</summary>
        Reliable
    }


    /// <summary>Abstraction for a TCP Client-Socket</summary>
    public class TCP
    {
        /// <summary>Represents the connection state of the TCP Client</summary>
        public bool isConnected = false;
        private TcpClient socket;
        private Endpoint endpoint;

        private byte[] buffer;
        private NetworkStream stream;

        ///<summary>Instantiates the socket</summary>
        public TCP()
        {
            socket = new TcpClient();
            buffer = new byte[Message.MAX_MSG_SIZE];
        }

        /// <summary>Attempt to connect to the bound endpoint</summary>
        ///<param name="ep">Endpoint of the remote host</param>
        public void Connect(Endpoint ep)
        {
            endpoint = ep;
            //Tries to connect to the server
            //Calls (HandleConnectCallback) if a success
            socket.BeginConnect(endpoint.address, endpoint.port, HandleConnectionCallback, socket);
        }

        /// <summary>Called if the connection attempt was successful</summary>
        /// <param name="connection"></param>
        private void HandleConnectionCallback(IAsyncResult connection)
        {
            tries = 0;
            //End connection attempt
            try
            {
                socket.EndConnect(connection);
                Console.WriteLine("TCP Connection State: " + socket.Connected);

                //Set the connection state of the TCP client
                isConnected = true;

                //Get the network stream for sending and receiving data
                stream = socket.GetStream();

                //Starts receiving data asynchronously from the server
                stream.BeginRead(buffer, 0, Message.MAX_MSG_SIZE, HandleDataCallback, null);
            }
            catch (Exception ex)
            {
                Console.WriteLine("Unable to connect to remote host " + endpoint.address + ":" + endpoint.port);
                Console.WriteLine(ex.Message);
            }
        }

        /// <summary>Handle the incoming data from the remote client</summary>
        private void HandleDataCallback(IAsyncResult connection)
        {
            Console.WriteLine("Receiving data");
            try
            {
                //Get the number of bytes read from the stream
                int bytesRead = stream.EndRead(connection);

                if (bytesRead >= 0)
                {
                    //If data was received from the remote host
                    byte[] data = new byte[bytesRead];

                    Array.Copy(buffer, data, bytesRead);

                    buffer = new byte[Message.MAX_MSG_SIZE]; //Reset the buffer before handling data
                    HandleData(data); //Handles (data)
                }

                //Starts receiving data asynchronously from the remote host again
                stream.BeginRead(buffer, 0, Message.MAX_MSG_SIZE, HandleDataCallback, null);
            }
            catch (Exception ex)
            {
                Console.WriteLine("Error receiving data: " + ex);
                Reconnect(endpoint);
            }
        }

        private void HandleData(byte[] data)
        {
            Message message = new Message(data); //Represent the data as a packet

            int size = message.ReadInt(); //Get the size of message
            int type = message.ReadInt(); //Get the type of message

            Console.WriteLine("Size: " + size);
            Console.WriteLine("Type: " + type);

            if (Client.messageHandlers.ContainsKey(type))
            {
                Client.messageHandlers[type](message);
            }
            else
            {
                Console.WriteLine("There is no handler for this type of message: " + type);
            }
        }

        /// <summary>Sends a message to the remote host it is bound to</summary>
        /// <param name="message">The message to send</param>
        public void Send(Message message)
        {
            if (socket.Connected == true)
            {
                try
                {
                    stream.BeginWrite(message.Unpack(), 0, message.Length(), null, null);
                }
                catch (Exception e)
                {
                    //An error happened and the message couldnt be sent
                    throw new Exception("Not able to send messsage: " + e);
                }
            }
            else
            {
               throw new Exception("Socket Disconnected");
            }
        }

        ///<summary>Disconnects the socket from the server it was bound to</summary>
        public void Disconnect()
        {
            buffer = new byte[Message.MAX_MSG_SIZE];
            stream = null;
            socket.Close();
            socket = null;
            isConnected = false;
        }

        private int tries = 0;
        /// <summary>Try to reconnect back to the server</summary>
        /// <param name="ep">Endpoint to reconnect to</param>
        public void Reconnect(Endpoint ep)
        {
            if(tries <= 5)
            {
                Console.WriteLine("Reconnecting ... " + ep.address);
                endpoint = ep;
                //Tries to reconnect to the server
                //Calls (HandleConnectCallback) if a success
                socket.BeginConnect(endpoint.address, endpoint.port, HandleConnectionCallback, socket);
            }
            else
            {
                throw new Exception("Unable To Reconnect To: " + ep.address);
                //Disconnect();
            }
            tries++;
        }
    }
}
