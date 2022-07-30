using System;
using System.Net.Sockets;

namespace Rooms.Transport
{
    /// <summary>Abstraction for a TCP Client-Socket</summary>
    public class TCP
    {
        private TcpClient socket;
        private Endpoint endpoint;

        private byte[] buffer;
        private NetworkStream stream;

        ///<summary>Bind the socket to a remote endpoint</summary>
        ///<param name="ep">Endpoint of the remote host</param>
        public TCP(Endpoint ep)
        {
            if (ep.address == null)
            {
                throw new ArgumentException("Endpoint: Address");
            }

            endpoint = ep;
            socket = new TcpClient();
            buffer = new byte[socket.ReceiveBufferSize];
        }
        
        public void Connect()
        {
            //Tries to connect to the server
            //Calls the HandleConnectCallback method if it succeeds
            socket.BeginConnect(endpoint.address, endpoint.port, HandleConnectionCallback, socket);
        }

        private void HandleConnectionCallback(IAsyncResult connection)
        {
            //End connection attempt
            socket.EndConnect(connection);

            //Exit if the socket did not connect
            if (socket.Connected == false)
            {
                return;
            }

            //Get the network stream for sending and receiving data
            stream = socket.GetStream();

            //Starts receiving data asynchronously from the server
            stream.BeginRead(buffer, 0, socket.ReceiveBufferSize, HandleDataCallback, null);
        }

        int dataLog = 0;
        /// <summary>Handle the incoming data from the remote client</summary>
        private void HandleDataCallback(IAsyncResult connection)
        {
            //Gets the number of bytes read
            int bytesRead = stream.EndRead(connection);

            //If no data was received 5 times consecutively, disconnect
            if (dataLog >= 4)
            {
                Disconnect();
                return;
            }

            //If no data was received
            if (bytesRead <= 0)
            {
                dataLog++;

                //Tries receiving data asynchronously from the server again
                stream.BeginRead(buffer, 0, socket.ReceiveBufferSize, HandleDataCallback, null);
                return;
            }

            dataLog = 0;
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
