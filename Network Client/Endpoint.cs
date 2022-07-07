namespace NetworkClient
{
    class Endpoint
    {
        public int port;
        public string address;

        /// <summary>Resets the endpoint</summary>
        public void Reset()
        {
            port = 0;
            address = null;
        }

    }
}
