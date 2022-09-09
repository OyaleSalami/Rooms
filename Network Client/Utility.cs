namespace Rooms.Util
{
    class Utility
    { 
        public const int MAX_MSG_SIZE = 2048;
    };

    public class Vector2
    {
        public float x, y;
        public Vector2(int _x, int _y)
        {
            x = _x;
            y = _y;
        }
    }
    public class Vector3
    {
        public float x, y, z;
        public Vector3(int _x, int _y, int _z)
        {
            x = _x;
            y = _y;
            z = _z;
        }
    }
    public class Quaternion
    {
        public float x, y, z, w;
        public Quaternion(int _x, int _y, int _z, int _w)
        {
            x = _x;
            y = _y;
            z = _z;
            w = _w;
        }
    }
}
