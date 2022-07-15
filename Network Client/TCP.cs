using System;
using System.Net.Sockets;

namespace NetworkClient
{
    class TCP
    {
        public TcpClient socket;
        private NetworkStream stream;
        private byte[] buffer;

        /// <summary>Bind the socket to the server</summary>
        /// <param name="endpoint">Server's endpoint</param>
        public void Bind(Endpoint endpoint)
        {
            socket = new TcpClient();
            buffer = new byte[socket.ReceiveBufferSize];

            //Tries to connect to the server
            //Calls the ConnectCallback method if it succeeds
            socket.BeginConnect(endpoint.address, endpoint.port, HandleConnectionCallback, socket);
        }

        private void HandleConnectionCallback(IAsyncResult connection)
        {
            //End connection attempt
            socket.EndConnect(connection);

            if (socket.Connected == false)
            {
                return;
            }

            //Get the network stream for sending and receiving data
            stream = socket.GetStream();

            //Starts receiving data asynchronously from the server
            stream.BeginRead(buffer, 0, socket.ReceiveBufferSize, HandleDataCallback, null);
        }

        private void HandleDataCallback(IAsyncResult connection)
        {
            //Stops receiving data
            int bytesRead = stream.EndRead(connection);
            //If no data was received
            if (bytesRead <= 0)
            {
                return;
            }


            //Starts receiving data asynchronously from the server again
            stream.BeginRead(buffer, 0, socket.ReceiveBufferSize, HandleDataCallback, null);
        }


        /// <summary>Sends a message to the server it is bound to</summary>
        /// <param name="message">The message to send</param>
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

        ///<summary>Disconnects the socket from the server it was bound to</summary>
        public void Disconnect()
        {
            stream = null;
            socket.Close();
            socket = null;
        }
    }
}
