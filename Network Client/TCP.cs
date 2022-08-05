using System;
using System.Net.Sockets;

namespace Rooms.Transport
{
    /// <summary>Abstraction for a TCP Client-Socket</summary>
    public class TCP
    {
        /// <summary>Represents the connection state of the TCP Client</summary>
        public bool isConnected = false;
        private TcpClient socket;
        private Endpoint endpoint;

        private byte[] buffer;
        private NetworkStream stream;

        ///<summary>Bind the socket to a remote endpoint</summary>
        ///<param name="ep">Endpoint of the remote host</param>
        public TCP(Endpoint ep)
        {
            if (ep.IsValid() == false)
            {
                throw new ArgumentException("Endpoint is not valid");
            }

            endpoint = ep;
            socket = new TcpClient();
            buffer = new byte[socket.ReceiveBufferSize];
        }
        
        /// <summary>Attempt to connect to the bound endpoint</summary>
        public void Connect()
        {
            //Tries to connect to the server
            //Calls the HandleConnectCallback method if it succeeds
            socket.BeginConnect(endpoint.address, endpoint.port, HandleConnectionCallback, socket);
        }

        /// <summary>Called if the connection attempt was successful</summary>
        /// <param name="connection"></param>
        private void HandleConnectionCallback(IAsyncResult connection)
        {
            //End connection attempt
            socket.EndConnect(connection);

            //Exit if the socket did not connect
            if (socket.Connected == false)
            {
                isConnected = false;
                return;
            }

            isConnected = true; //Set the connection state of the TCP client

            //Get the network stream for sending and receiving data
            stream = socket.GetStream();

            //Starts receiving data asynchronously from the server
            stream.BeginRead(buffer, 0, socket.ReceiveBufferSize, HandleDataCallback, null);
        }

        int dataLog = 0;
        /// <summary>Handle the incoming data from the remote client</summary>
        private void HandleDataCallback(IAsyncResult connection)
        {
            try
            {
                //Get the number of bytes read from the stream
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

                    //Tries receiving data asynchronously from the remote host again
                    stream.BeginRead(buffer, 0, socket.ReceiveBufferSize, HandleDataCallback, null);
                    return;
                }

                //If data was received from the remote host
                dataLog = 0;
                byte[] data = new byte[bytesRead];
                Array.Copy(buffer, data, bytesRead);

                HandleData(data);
                buffer = null;

                //Starts receiving data asynchronously from the remote host again
                stream.BeginRead(buffer, 0, socket.ReceiveBufferSize, HandleDataCallback, null);
            }
            catch
            {
                Disconnect();
            }
        }

        private void HandleData(byte[] data)
        {
            Console.Write("Data Handled: ");
            Console.WriteLine(data);
        }

        /// <summary>Sends a message to the remote host it is bound to</summary>
        /// <param name="message">The message to send</param>
        public void Send(Message message)
        {
            if (socket != null)
            {
                try
                {
                    // Start sending data to the remote host
                    stream.BeginWrite(message.Unpack(), 0, message.Length(), null, null); 
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
            isConnected = false;
        }
    }
}
