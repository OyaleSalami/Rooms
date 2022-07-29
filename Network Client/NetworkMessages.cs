using System;
using System.Collections.Generic;
using System.Text;

namespace NetworkClient
{
    class Packet : IMessage
    {
        public Message message; // Message part is stored here, the rest of the class contains the header

        ///<summary>Declaring an empty Packet</summary>
        ///<param name="type">The indetifier for which type of message/packet it is</param>
        public Packet(Type type)
        {
            ResetReadHead();
            Add((int)type);
        }

        ///<summary>For recreating a Packet from a byte array</summary>
        ///<param name="data">the byte array</param>
        public Packet(byte[] data)
        {
            buffer.AddRange(data);
            ResetReadHead();
        }
    }

    class Message : IMessage
    {
        ///<summary>Declaring an empty message</summary>
        ///<param name="type">The indetifier for which type of message it is</param>
        public Message(Type type)
        {
            ResetReadHead();
            Add((int)type);
        }

        ///<summary>For recreating a message from a byte array</summary>
        ///<param name="data">the byte array</param>
        public Message(byte[] data)
        {
            buffer.AddRange(data);
            ResetReadHead();
        }
    }

    public abstract class IMessage
    {
        protected int readHead;   //To indicate the postion of the read head
        protected bool writeable = true; //To lock/unlock writing access
        protected List<byte> buffer; //The array where all the data is stored

        public enum Type
        {
            auth = 1,
            authFailed,
            chat,
            ping,
            spawnPlayer,
            custom
        }

        public enum Mode
        {
            Multicast = 1,
            Tcp,
            Udp,
            Reliable,
        }

        #region Auxilliary Functions
        ///<summary>Resets the read head back to the start of the message</summary>
        protected void ResetReadHead()
        {
            readHead = 0;
        }

        /// <returns>The message as an array</returns>
        public byte[] Unpack()
        {
            return buffer.ToArray();
        }

        /// <summary>Simple check to see whether or not the message contains valid 
        /// info</summary>
        public bool isValid()
        {
            if (buffer.Count > 4)
            {
                return true;
            }
            return false;
        }
        
        /// <returns>The number of bytes in the message</returns>
        public int Length()
        {
            return buffer.Count;
        }
        
        /// <summary>Clears the message and reset the read head</summary>
        public void Clear()
        {
            buffer.Clear();
            ResetReadHead();
        }
        
        /// <summary>Adds the length at the front of the message and locks writing access</summary>
        public void Seal()
        {
            buffer.InsertRange(0, BitConverter.GetBytes(buffer.Count));
            writeable = false;
        }

        #endregion

        #region Add Functions
        /// <summary>Adds a byte the message</summary>
        /// <param name="value">Byte to be added</param>
        /// <exception cref="Exception"> Writing is locked</exception>
        public void Add(byte value)
        {
            if(writeable == true)
            {
                buffer.Add(value);
            }
            else
            {
                throw new Exception("Error: Trying to write to a locked message");
            }
        }

        /// <summary>Adds a short the message</summary>
        /// <param name="value">Short to be added</param>
        /// <exception cref="Exception"> Writing is locked</exception>
        public void Add(short value)
        {
            if (writeable == true)
            {
                buffer.AddRange(BitConverter.GetBytes(value));
            }
            else
            {
                throw new Exception("Error: Trying to write to a locked message");
            }
        }

        /// <summary>Adds an int to the message</summary>
        /// <param name="value">Int to be added</param>
        /// <exception cref="Exception"> Writing is locked</exception>
        public void Add(int value)
        {
            if (writeable == true)
            {
                buffer.AddRange(BitConverter.GetBytes(value));
            }
            else
            {
                throw new Exception("Error: Trying to write to a locked message");
            }
        }

        /// <summary>Adds a long to the message</summary>
        /// <param name="value">Long to be added</param>
        /// <exception cref="Exception"> Writing is locked</exception>
        public void Add(long value)
        {
            if (writeable == true)
            {
                buffer.AddRange(BitConverter.GetBytes(value));
            }
            else
            {
                throw new Exception("Error: Trying to write to a locked message");
            }
        }

        /// <summary>Adds a float to the message</summary>
        /// <param name="value">Float to be added</param>
        /// <exception cref="Exception"> Writing is locked</exception>
        public void Add(float value)
        {
            if (writeable == true)
            {
                buffer.AddRange(BitConverter.GetBytes(value));
            }
            else
            {
                throw new Exception("Error: Trying to write to a locked message");
            }
        }

        /// <summary>Adds a double to the message</summary>
        /// <param name="value">Double to be added</param>
        /// <exception cref="Exception"> Writing is locked</exception>
        public void Add(double value)
        {
            if (writeable == true)
            {
                buffer.AddRange(BitConverter.GetBytes(value));
            }
            else
            {
                throw new Exception("Error: Trying to write to a locked message");
            }
        }

        /// <summary>Adds a boolean to the message</summary>
        /// <param name="value">Bool to be added</param>
        /// <exception cref="Exception"> Writing is locked</exception>
        public void Add(bool value)
        {
            if (writeable == true)
            {
                buffer.AddRange(BitConverter.GetBytes(value));
            }
            else
            {
                throw new Exception("Error: Trying to write to a locked message");
            }
        }

        /// <summary>Adds a string to the message</summary>
        /// <param name="value">String to be added</param>
        /// <exception cref="Exception"> Writing is locked</exception>
        public void Add(string value)
        {
            if (writeable == true)
            {
                //Add the length of the string
                Add(value.Length);
                //Then Add the string itself 
                buffer.AddRange(Encoding.ASCII.GetBytes(value));
            }
            else
            {
                throw new Exception("Error: Trying to write to a locked message");
            }
        }

        /// <summary>Adds a vector2 to the message</summary>
        /// <param name="value">Vector2 to be added</param>
        /// <exception cref="Exception"> Writing is locked</exception>
        public void Add(Vector2 value)
        {
            if (writeable == true)
            {
                Add(value.x);
                Add(value.y);
            }
            else
            {
                throw new Exception("Error: Trying to write to a locked message");
            }
        }

        /// <summary>Adds a vector3 to the message</summary>
        /// <param name="value">Vector3 to be added</param>
        /// <exception cref="Exception"> Writing is locked</exception>
        public void Add(Vector3 value)
        {
            if (writeable == true)
            {
                Add(value.x);
                Add(value.y);
                Add(value.z);
            }
            else
            {
                throw new Exception("Error: Trying to write to a locked message");
            }
        }

        /// <summary>Adds a quaternion to the message</summary>
        /// <param name="value">Quaternion to be added</param>
        /// <exception cref="Exception"> Writing is locked</exception>
        public void Add(Quaternion value)
        {
            if (writeable == true)
            {
                Add(value.x);
                Add(value.y);
                Add(value.z);
                Add(value.w);
            }
            else
            {
                throw new Exception("Error: Trying to write to a locked message");
            }
        }

        /// <summary>Adds a byte array to the message</summary>
        /// <param name="value">Byte array to be added</param>
        /// <exception cref="Exception"> Writing is locked</exception>
        public void Add(byte[] value)
        {
            if(writeable == true)
            {
                Add(value.Length);
                buffer.AddRange(value);
            }
            else
            {
                throw new Exception("Error: Trying to write to a locked message");
            }
        }
        #endregion

        #region Read Functions
        public short ReadShort()
        {
            try
            {
                if (buffer.Count > readHead)
                {
                    short value = BitConverter.ToInt16(buffer.ToArray(), readHead);
                    readHead += sizeof(short);

                    return 0;
                }
                throw new Exception("Unable to Read Short: End of Packet Reached");
            }
            catch (Exception e)
            {
                throw new Exception("Unable to Read Short: " + e);
            }

        }
        public int ReadInt()
        {
            try
            {
                if (buffer.Count > readHead)
                {
                    int value = BitConverter.ToInt32(buffer.ToArray(), readHead);
                    readHead += sizeof(int);

                    return value;
                }
                throw new Exception("Unable to Read Int: End of Packet Reached");
            }
            catch (Exception e)
            {
                throw new Exception("Unable to Read Int: " + e);
            }
        }
        public long ReadLong()
        {
            try
            {
                if (buffer.Count > readHead)
                {
                    long value = BitConverter.ToInt64(buffer.ToArray(), readHead);
                    readHead += sizeof(long);

                    return value;
                }
                throw new Exception("Unable to Read Long: End of Packet Reached");
            }
            catch (Exception e)
            {
                throw new Exception("Unable to Read Long: " + e);
            }

        }
        public bool ReadBool()
        {
            try
            {
                if (buffer.Count > readHead)
                {
                    bool value = BitConverter.ToBoolean(buffer.ToArray(), readHead);
                    readHead += sizeof(bool);

                    return value;
                }
                throw new Exception("Unable to Read Bool: End Of Packet Reached");
            }
            catch (Exception e)
            {
                throw new Exception("Unable to Read Bool: " + e);
            }
        }
        public float ReadFloat()
        {
            try
            {
                if (buffer.Count > readHead)
                {
                    float value = BitConverter.ToSingle(buffer.ToArray(), readHead);
                    readHead += sizeof(float);

                    return value;
                }
                throw new Exception("Unable to Read Float: End of Packet Reached");
            }
            catch (Exception e)
            {
                throw new Exception("Unable to Read Float: " + e);
            }
        }
        public double ReadDouble()
        {
            try
            {
                if (buffer.Count > readHead)
                {
                    double value = BitConverter.ToDouble(buffer.ToArray(), readHead);
                    readHead += sizeof(double);

                    return value;
                }
                throw new Exception("Unable to Read Double: End of Packet Reached");
            }
            catch (Exception e)
            {
                throw new Exception("Unable to Read Double: " + e);
            }
        }
        public string ReadString()
        {
            try
            {
                if (buffer.Count > readHead)
                {
                    int stringLength = ReadInt();
                    string text = Encoding.ASCII.GetString(buffer.ToArray(), readHead, stringLength);

                    readHead += stringLength;
                    return text;
                }
                throw new Exception("Unable to Read String: End of Packet Reached");
            }
            catch (Exception e)
            {
                throw new Exception("Unable to Read String: " + e);
            }
        }

        #endregion

        #region Check Functions
        public short CheckShort()
        {
            try
            {
                if (buffer.Count > readHead)
                {
                    short value = BitConverter.ToInt16(buffer.ToArray(), readHead);
                    return value;
                }
                throw new Exception("Unable to Read Short: End of Packet Reached");
            }
            catch (Exception e)
            {
                throw new Exception("Unable to Read Short: " + e);
            }

        }
        public int CheckInt()
        {
            try
            {
                if (buffer.Count > readHead)
                {
                    int value = BitConverter.ToInt32(buffer.ToArray(), readHead);
                    return value;
                }
                throw new Exception("Unable to Read Int: End of Packet Reached");
            }
            catch (Exception e)
            {
                throw new Exception("Unable to Read Int: " + e);
            }
        }
        public long CheckLong()
        {
            try
            {
                if (buffer.Count > readHead)
                {
                    long value = BitConverter.ToInt64(buffer.ToArray(), readHead);
                    return value;
                }
                throw new Exception("Unable to Read Long: End of Packet Reached");
            }
            catch (Exception e)
            {
                throw new Exception("Unable to Read Long: " + e);
            }
        }
        public bool CheckBool()
        {
            try
            {
                if (buffer.Count > readHead)
                {
                    bool value = BitConverter.ToBoolean(buffer.ToArray(), readHead);
                    return value;
                }
                throw new Exception("Unable to Read Bool: End Of Packet Reached");
            }
            catch (Exception e)
            {
                throw new Exception("Unable to Read Bool: " + e);
            }
        }
        public float CheckFloat()
        {
            try
            {
                if (buffer.Count > readHead)
                {
                    float value = BitConverter.ToSingle(buffer.ToArray(), readHead);
                    return value;
                }
                throw new Exception("Unable to Read Float: End of Packet Reached");
            }
            catch (Exception e)
            {
                throw new Exception("Unable to Read Float: " + e);
            }
        }
        public double CheckDouble()
        {
            try
            {
                if (buffer.Count > readHead)
                {
                    double value = BitConverter.ToDouble(buffer.ToArray(), readHead);
                    return value;
                }
                throw new Exception("Unable to Read Double: End of Packet Reached");
            }
            catch (Exception e)
            {
                throw new Exception("Unable to Read Double: " + e);
            }
        }
        public string CheckString()
        {
            try
            {
                if (buffer.Count > readHead)
                {
                    int stringLength = ReadInt();
                    string text = Encoding.ASCII.GetString(buffer.ToArray(), readHead, stringLength);
                    return text;
                }
                throw new Exception("Unable to Read String: End of Packet Reached");
            }
            catch (Exception e)
            {
                throw new Exception("Unable to Read String: " + e);
            }
        }
        #endregion

        #region Encryption Functions
        //TODO: Encryption
        #endregion

    }
}
