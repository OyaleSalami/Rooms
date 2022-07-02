using System.Net.Sockets;

namespace Network_Client
{
    class UDP
    {
        public UdpClient socket;
        private Endpoint endpoint;
        private NetworkStream stream;
        private byte[] buffer;

        public void Bind(Endpoint _endpoint)
        {
            endpoint = _endpoint;
            socket = new UdpClient();
        }

        public void Send(Message _message)
        {
            if (socket == null)
            {

            }
        }

        public void SendReliable(Message _message)
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
