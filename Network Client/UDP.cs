using System;
using System.Net.Sockets;

namespace NetworkClient
{
    class UDP
    {
        public UdpClient socket;
        private Endpoint endpoint;
        private NetworkStream stream;
        private byte[] buffer;

        public void Bind(Endpoint ep)
        {
            if (ep.address == null)
            {
                throw new ArgumentNullException("Endpoint: Address");
            }

            endpoint = ep;
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
