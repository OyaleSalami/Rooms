using System;
using System.Net.Sockets;

namespace Rooms.Transport
{
    public class UDP
    {
        public UdpClient socket;
        private Endpoint endpoint;
        private NetworkStream stream;
        private byte[] buffer;

        public UDP(Endpoint ep)
        {
            if (ep.IsValid() == false)
            {
                throw new ArgumentNullException("Endpoint is not valid");
            }
            endpoint = ep;
        }
        public void Connect()
        {
            socket = new UdpClient();
        }

        public void Send(Message message)
        {
            if (socket != null)
            {
                try
                {

                }
                catch (Exception e)
                {
                    //An error happened and the message couldnt be sent
                    throw new Exception("Unable to send messsage: " + e);
                }
            }
        }

        public void SendReliable(Message message)
        {
            if (socket != null)
            {
                try
                {

                }
                catch (Exception e)
                {
                    //An error happened and the message couldnt be sent
                    throw new Exception("Unable to send message: " + e);
                }
            }
        }

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
