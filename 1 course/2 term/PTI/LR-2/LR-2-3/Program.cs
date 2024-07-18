//№13

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LR_2_3
{
	class Program
	{
		static void Main(string[] args)
		{
			StringBuilder str = new StringBuilder(256);
			char[] a = new char[256];
			Random rand = new Random();
			for (int i = 0; i < 256; i++)
			{
				str.Append((char)rand.Next('A', 'Z'));
			}
			Console.WriteLine("Строка: " + str);
			Console.Write("\nРяд символов: ");
			for (int i = 0; i < 30; i++)
			{
				int index = rand.Next(0, 30);
				Console.Write(str[index] + " ");
			}
			Console.ReadKey();
		}
	}
}
