namespace NetworkClient
{
    class Endpoint
    {
        public int port;
        public string address;

        public Endpoint(int _port, string _address)
        {
            port = _port;
            address = _address;
        }

        /// <summary>Resets the endpoint</summary>
        public void Reset()
        {
            port = 0;
            address = null;
        }

    }
}
