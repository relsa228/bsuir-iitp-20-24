//№1

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LR_2_1
{
	class Program
	{
		static int Check(string str, int dlin, int num)
		{
			int result = 0;
			string check = num.ToString();
			for (int i = 0; i < dlin; i++)
			{
				string elem = Char.ToString(str[i]);
				if (String.Compare(elem, check) == 0)
				{
					result+=1;
				}
			}
			return result;
		}
		static void Main(string[] args)
		{
			DateTime date = new DateTime();
			date = DateTime.Now;
			Console.Write("Текущая дата и время: " + date);
			Console.WriteLine();
			string str = date.ToString("yyyyMMddHHmmss");
			for(int i = 0; i <10; i++)
			{
				int a = Check(str, str.Length, i);
				Console.Write("\nКолличество " + i + ": " + a);
			}
			Console.ReadKey();
		}
	}
}
