using System.Collections.Generic;

namespace Network_Client
{
    class Message
    {
        public enum Type
        {
            authQuery = 1,
            authRequest,
            authFailed,
            welcome,
            welcomeReceived,
            chat,
            spawnPlayer,
            playerPosition,
            playerRotation
        }
        public enum Mode
        {
            Broadcast = 1,
            Tcp,
            Udp,
            Reliable,
        }

        private int readHead;
        private List<byte> buffer;

        #region Constructors
        public Message(Message.Type type)
        {
            Add((int)type);
            readHead = 0;
        }

        public Message(byte[] _data)
        {
            readHead = 0;
            buffer.AddRange(_data);
        }
        #endregion

        /// <returns>Returns the message as a Byte Array</returns>
        public byte[] Unpack()
        {
            return buffer.ToArray();
        }

        #region Write Functions
        public void Add(int _value)
        {

        }
        #endregion

        #region Read Functions
        public void Read(int _int)
        {

        }
        #endregion
    }
}
