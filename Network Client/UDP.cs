using System;
using System.Net;
using System.Net.Sockets;

namespace Rooms.Transport
{
    /// <summary>Abstraction for a UDP Client-Socket</summary>
    public class UDP
    {
        /// <summary>Represents the connection state of the UDP Client</summary>
        public bool isConnected = false;

        private UdpClient socket;
        private Endpoint endpoint;
        private NetworkStream stream;
        private byte[] buffer;

        /// <summary>Creates and Binds the UDP Client to a remote host</summary>
        /// <param name="ep">Enpoint of the remote host</param>
        public UDP(Endpoint ep)
        {
            if (ep.IsValid() == false)
            {
                throw new ArgumentNullException("Endpoint is not valid");
            }

            endpoint = ep;
            socket = new UdpClient();
        }

        /// <summary>Attempts to connect to the bound remote host</summary>
        public void Connect()
        {
            socket.Connect(new IPEndPoint(IPAddress.Parse(endpoint.address), endpoint.port));
        }

        /// <summary>Send a message to the bound remote host (Unreliable)</summary>
        /// <param name="message">Message to send</param>
        public void Send(Message message)
        {
            if (socket != null)
            {
                try
                {
                    //Starts sending the data to the remote host
                    socket.BeginSend(message.Unpack(), message.Length(), null, null);
                }
                catch (Exception e)
                {
                    //An error happened and the message couldnt be sent
                    throw new Exception("Unable to send messsage: " + e);
                }
            }
        }

        /// <summary>Send a message to the bound remote host (Reliable)</summary>
        /// <param name="message">Message to send</param>
        public void SendReliable(Message message)
        {
            //TODO: To be implemented
        }

        /// <summary>Disconnect the UDP Client from any remote host</summary>
        public void Disconnect()
        {
            stream.Close();
            socket.Close();
            stream = null;
            socket = null;
            endpoint.Reset();
        }
    }
}
