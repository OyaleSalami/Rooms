namespace Rooms
{
    /// <summary>Holds information about a remote host(address/port)</summary>
    public class Endpoint
    {
        /// <summary>Port of the remote host</summary>
        public int port;
        ///<summary>Address of the remote host</summary>
        public string address;

        /// <summary>Creates an Endpoint</summary>
        /// <param name="_port">Port of the remote host</param>
        /// <param name="_address">Address of the remote host</param>
        public Endpoint(int _port, string _address)
        {
            port = _port;
            address = _address;
        }

        /// <summary>Checks to see if an Endpoint is valid </summary>
        /// <returns>True if valid, false if otherwise </returns>
        public bool IsValid()
        {
            if(port == 0 || address == null)
            {
                return false;
            }
            return true;
        }

        /// <summary>Resets the endpoint so it doesn't point to any address</summary>
        public void Reset()
        {
            port = 0;
            address = null;
        }
    }
}
