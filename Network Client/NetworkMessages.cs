using System;
using System.Collections.Generic;
using System.Text;

namespace Rooms
{
    /// <summary>Represents a message to be sent over the network</summary>
    public class Message : IMessage
    {
        /// <summary>Maximum size of a message(bytes)</summary>
        public const int MAX_MSG_SIZE = 2048;

        ///<summary>Creating an empty message</summary>
        ///<param name="type">The type of message</param>
        public Message(Type type)
        {
            buffer = new List<byte>();
            ResetReadHead();
            Add((int)type);
        }

        ///<summary>For recreating a message from a byte array</summary>
        ///<param name="data">the byte array</param>
        public Message(byte[] data)
        {
            buffer = new List<byte>();
            buffer.AddRange(data);
            ResetReadHead();
        }

        ///<summary>The type of the message</summary>
        public enum Type : byte
        {
            ///<summary>Network test</summary>
            test = 0,

            ///<summary>Authentication request</summary>
            authRequest,

            ///<summary>Authentication response</summary>
            authCallback,

            ///<summary>Authentication failure</summary>
            authFailed,

            ///<summary>Ping request</summary>
            pingRequest,

            ///<summary>Ping response</summary>
            pingCallback,

            ///<summary>Chat message</summary>
            chat,

            ///<summary>Custom message</summary>
            custom
        }

    }

    /// <summary>Base class for all type of messages</summary>
    public abstract class IMessage
    {
        ///<summary>Read Head index</summary>
        protected int readHead;

        /// <summary>Write access</summary>
        protected bool writeable = true;

        ///<summary>The data buffer</summary>
        protected List<byte> buffer;

        

        #region Auxilliary Functions
        ///<summary>Resets the read head back to the start of the message</summary>
        protected void ResetReadHead()
        {
            readHead = 0;
        }

        ///<returns>The message as an array</returns>
        public byte[] Unpack()
        {
            return buffer.ToArray();
        }

        /// <summary>Check to see whether the message has valid info</summary>
        public bool IsValid()
        {
            if (buffer.Count >= 4)
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
        /// <summary>Adds a byte to the message</summary>
        /// <param name="value">Byte to be added</param>
        /// <exception cref="Exception"> Writing is locked</exception>
        public void Add(byte value)
        {
            if (writeable == true)
            {
                buffer.Add(value);
            }
            else
            {
                throw new Exception("Error: Trying to write to a locked message");
            }
        }

        /// <summary>Adds a short to the message</summary>
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

        /// <summary>Adds a byte array to the message</summary>
        /// <param name="value">Byte array to be added</param>
        /// <exception cref="Exception"> Writing is locked</exception>
        public void Add(byte[] value)
        {
            if (writeable == true)
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

        /// <summary>Reads a short from the message</summary>
        /// <param name="moveReadHead">If false, It won't move the read head</param>
        /// <returns>Short read from the message</returns>
        /// <exception cref="Exception">EoF message reached/Message is not valid</exception>
        public short ReadShort(bool moveReadHead = true)
        {
            if (readHead + sizeof(short) <= buffer.Count)
            {
                short value = BitConverter.ToInt16(buffer.ToArray(), readHead);
                if(moveReadHead == true)
                {
                    readHead += sizeof(short); //Move the read head!
                }

                return value;
            }
            else
            {
                throw new Exception("Unable to Read Short: End of Packet Reached");
            }
        }

        /// <summary>Reads an int from the message</summary>
        /// <param name="moveReadHead">If false, It won't move the read head</param>
        /// <returns>Int read from the message</returns>
        /// <exception cref="Exception">EoF message reached/Message is not valid</exception>
        public int ReadInt(bool moveReadHead = true)
        {
            if (readHead + sizeof(int) <= buffer.Count)
            {
                int value = BitConverter.ToInt32(buffer.ToArray(), readHead);
                if (moveReadHead == true)
                {
                    readHead += sizeof(int);
                }

                return value;
            }
            else
            {
                throw new Exception("Unable to Read Int: End of Packet Reached");
            }
        }

        /// <summary>Read a long from the message</summary>
        /// <param name="moveReadHead">If false, It won't move the read head</param>
        /// <returns>Long from the message</returns>
        /// <exception cref="Exception">EoF message reached/Message is not valid</exception>
        public long ReadLong(bool moveReadHead = true)
        {
            if (readHead + sizeof(long) <= buffer.Count)
            {
                long value = BitConverter.ToInt64(buffer.ToArray(), readHead);
                if(moveReadHead == true)
                {
                    readHead += sizeof(long);
                }

                return value;
            }
            else
            {
                throw new Exception("Unable to Read Long: End of Packet Reached");
            }
        }

        /// <summary>Reads a bool from the message</summary>
        /// <param name="moveReadHead">If false, It won't move the read head</param>
        /// <returns>Bool read from the message</returns>
        /// <exception cref="Exception">EoF message reached/Message is not valid</exception>
        public bool ReadBool(bool moveReadHead = true)
        {
            if (readHead + sizeof(bool) <= buffer.Count)
            {
                bool value = BitConverter.ToBoolean(buffer.ToArray(), readHead);
                if(moveReadHead == true)
                {
                    readHead += sizeof(bool);
                }

                return value;
            }
            else
            {
                throw new Exception("Unable to Read Bool: End Of Packet Reached");
            }
        }

        /// <summary>Reads a float from the message</summary>
        /// <param name="moveReadHead">If false, It won't move the read head</param>
        /// <returns>Float read from the message</returns>
        /// <exception cref="Exception">EoF message reached/Message is not valid</exception>
        public float ReadFloat(bool moveReadHead = true)
        {
            if (readHead + sizeof(float) <= buffer.Count)
            {
                float value = BitConverter.ToSingle(buffer.ToArray(), readHead);
                if(moveReadHead == true)
                {
                    readHead += sizeof(float);
                }

                return value;
            }
            else
            {
                throw new Exception("Unable to Read Float: End of Packet Reached");
            }
        }

        /// <summary>Reads a double from the message</summary>
        /// <param name="moveReadHead">If false, It won't move the read head</param>
        /// <returns>Double read from the message</returns>
        /// <exception cref="Exception">EoF message reached/Message is not valid</exception>
        public double ReadDouble(bool moveReadHead = true)
        {
            if (readHead + sizeof(double) <= buffer.Count)
            {
                double value = BitConverter.ToDouble(buffer.ToArray(), readHead);
                if(moveReadHead == true)
                {
                    readHead += sizeof(double);
                }

                return value;
            }
            else
            {
                throw new Exception("Unable to Read Double: End of Packet Reached");
            }
        }

        /// <summary>Reads a string from the message</summary>
        /// <param name="moveReadHead">If false, It won't move the read head</param>
        /// <returns>String read from the message</returns>
        /// <exception cref="Exception">EoF message reached/Message is not valid</exception>
        public string ReadString(bool moveReadHead = true)
        {
            //Check if you can read the size then check if you can read the string
            if (readHead + sizeof(int) <= buffer.Count)
            {
                int stringLength = ReadInt();
                if(readHead + stringLength <= buffer.Count)
                {
                    string text = Encoding.ASCII.GetString(buffer.ToArray(), readHead, stringLength);
                    
                    if(moveReadHead == true)
                    {
                        readHead += stringLength;
                    }
                    return text;
                }
                else
                {
                    throw new Exception("Unable to read: String is not complete!");
                }
            }
            else
            {
                throw new Exception("Unable to Read String: End of Packet Reached");
            }
        }

        #endregion

        #region Encryption Functions
        //TODO: Encryption
        #endregion
    }

}