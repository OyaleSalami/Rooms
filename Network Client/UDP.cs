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
            endpoint = ep;
            socket = new UdpClient();
        }

        public void Send(Message message)
        {
            if (socket == null)
            {

            }
        }

        public void SendReliable(Message message)
        {
            if (socket == null)
            {

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
