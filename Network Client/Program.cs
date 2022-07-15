using System;

namespace NetworkClient
{
    class Program
    {
        static void Main(string[] args)
        {
            bool running = true;
            int x = 8;
            changeX(x);

            Console.WriteLine(x);
            Console.Read();
        }

        public static void changeX(int y)
        {
            y = 10;
            Console.WriteLine(y);
        }
    }
}
