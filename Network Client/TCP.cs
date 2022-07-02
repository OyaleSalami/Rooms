using System.Net.Sockets;

namespace Network_Client
{
    class TCP
    {
        public TcpClient socket;
        private NetworkStream stream;
        private byte[] buffer;

        /// <summary>Bind the socket to the server</summary>
        /// <param name="_endpoint">Server's endpoint</param>
        public void Bind(Endpoint _endpoint)
        {
            socket = new TcpClient();
            buffer = new byte[socket.ReceiveBufferSize];
        }

        /// <summary>Sends a message to the server it is bound to</summary>
        /// <param name="_message">The message to send</param>
        public void Send(Message _message)
        {
            if (socket != null)
            {

            }
        }

        ///<summary>Disconnects the socket from the server it was bound to</summary>
        public void Disconnect()
        {
            stream = null;
            socket.Close();
            socket = null;
        }
    }
}
