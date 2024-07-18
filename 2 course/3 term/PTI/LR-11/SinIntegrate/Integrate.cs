using System;
using System.Diagnostics;

namespace SinIntegrate
{
    public delegate void CulcFinish(double res, Stopwatch stopwatch, object s);
    public class Integrate
    {
        public event CulcFinish Finish;
        
        private double Step = 0.00000001;
        private int HBorder = 1;
        private int LBorder = 0;
        
        public void Integration(object s)
        {
            double res = 0;
            
            Stopwatch stopWatch = new Stopwatch();
            stopWatch.Start();

            for (double i = LBorder; i < HBorder; i += Step)
            {
                res += Math.Sin(i);
            }
            res *= Step;
            
            stopWatch.Stop();

            Finish?.Invoke(res, stopWatch, s);
        }

        public void Result(double res, Stopwatch stopwatch, object s)
        {
            Console.WriteLine($"Поток: {s}\nРезультат: {res}\nВремя, затраченное на выполнение метода: " +
                              $"{stopwatch.Elapsed}\n");
        }
    }
}