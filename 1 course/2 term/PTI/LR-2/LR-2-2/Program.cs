//№4

using System;
using System.Numerics;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LR_2_2
{
	class Program
	{
		static void PowerOfTwo (BigInteger dividend)
		{
			for (int i = 0; ; i++)
			{
				BigInteger power = new BigInteger();
				power = BigInteger.Pow(2, i);
				BigInteger div = new BigInteger();
				div = BigInteger.DivRem(dividend, power, out System.Numerics.BigInteger remainder);
				if (div < 1)
				{
					power = BigInteger.DivRem(power, 2, out System.Numerics.BigInteger rem);
					Console.Write("Степень двойки: " + (i - 1));
					break;
				}
			}
		}
		static void Main(string[] args)
		{
			BigInteger dividend = new BigInteger();
			BigInteger dividendPost = new BigInteger();
			Console.Write("Введите число а: ");
			double a = Convert.ToDouble(Console.ReadLine());
			Console.Write("Введите число b: ");
			double b = Convert.ToDouble(Console.ReadLine());
			if (a > b)
			{
				double ceiling = Math.Ceiling(a);
				if (Math.Ceiling(a) == a)
					ceiling += 1;
				dividend = 1;
				dividendPost = 1;
				for (; b <= ceiling - 1; b++)
				{
					dividendPost = dividend;
					dividend = Convert.ToInt64(Math.Ceiling(b)) * dividendPost;
					
				}
			}
			else if (a < b)
			{
				double ceiling = Math.Ceiling(b);
				if (Math.Ceiling(b) == b)
					ceiling += 1;
				dividend = 1;
				dividendPost = 1;
				for (; a <= ceiling-1; a++)
				{
					dividendPost = dividend;
					dividend = Convert.ToInt64(Math.Ceiling(a)) * dividendPost;
				}
			}
			else
			{
				Console.Write("\nЧисла равны");
				Console.ReadKey();
				System.Environment.Exit(0);
			}
			Console.WriteLine("\nПроизведение подряд идущих чисел от a до b: " + dividend);
			PowerOfTwo(dividend);
			Console.ReadKey();
		}
	}
}
