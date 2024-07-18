using System;
using System.Runtime.InteropServices;

namespace LR_4_2
{
    class Program
    {
        [DllImport(@"..\..\..\..\..\Debug\Dll1.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int add(int a, int b);
        [DllImport(@"..\..\..\..\..\Debug\Dll1.dll", CallingConvention = CallingConvention.StdCall)]
        public static extern int minus(int a, int b);
        [DllImport(@"..\..\..\..\..\Debug\Dll1.dll", CallingConvention = CallingConvention.StdCall)]
        public static extern int divided(int a, int b);
        [DllImport(@"..\..\..\..\..\Debug\Dll1.dll", CallingConvention = CallingConvention.Winapi)]
        public static extern int power(int a, int b);
        static void Main(string[] args)
        {
            int s = add(3, 6);
            Console.WriteLine(s);
            int m = minus(9, 6);
            Console.WriteLine(m);
            int d = divided(18, 6);
            Console.WriteLine(d);
            int p = power(2, 2);
            Console.WriteLine(p);
        }
    }
}
