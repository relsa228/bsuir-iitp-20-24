using System;
using System.Text.RegularExpressions;

namespace LR_7
{
    public class Fraction: IEquatable<Fraction>, IComparable<Fraction>
    {
        public int Numerator;
        public uint Denominator;

        public Fraction()
        {
            Numerator = 1;
            Denominator = 1;
        }
        private uint CommonDenominator(Fraction fr1, Fraction fr2)
        {
            for (uint i = 0; i < (fr1.Denominator * fr2.Denominator + 1); i++)
            {
                if (i % fr1.Denominator == 0 && i % fr2.Denominator == 0)
                    if (i != 0)
                        return i;
            }
            return 0;
        }

        public static Fraction Input(String str)
        {
            Console.Write(str);
            Fraction fr = new Fraction(); 
            String frStr = Console.ReadLine(); 
            while (!fr.FromString(frStr))
            { 
                Console.Write(str);
                frStr = Console.ReadLine();
            }
            return fr;
        }

        public override string ToString()
        {
            String frStr = "", denominatorStr, numeratorStr;
            denominatorStr = Convert.ToString(Denominator);
            numeratorStr = Convert.ToString(Numerator);
            frStr=frStr.Insert(frStr.Length, numeratorStr);
            frStr=frStr.Insert(frStr.Length, "/");
            frStr=frStr.Insert(frStr.Length, denominatorStr);
            return frStr;
        }

        public bool FromString(String frStr)
        {
            bool rCheck = false;
            int i;
            String denominatorStr = "", numeratorStr = "";
            String pattern1 = @"^-?[0-9]+[/][0-9]+$";
            String pattern2 = @"^-?[0-9]+[,]?[.]?[0-9]+$";
            if (Regex.IsMatch(frStr, pattern1, RegexOptions.IgnoreCase))
            {
                if (frStr[0] == '-')
                    rCheck = true;
                if (rCheck)
                    i = 1;
                else
                    i = 0;
            
                while (Char.IsDigit(frStr[i]))
                {
                    numeratorStr=numeratorStr.Insert(numeratorStr.Length, frStr[i].ToString());
                    i++;
                }
            
                i++;
            
                while (i < frStr.Length)
                {
                    denominatorStr=denominatorStr.Insert(denominatorStr.Length, frStr[i].ToString());
                    i++;
                }
                
                Denominator = Convert.ToUInt32(denominatorStr);
                Numerator = Convert.ToInt32(numeratorStr);

                if (rCheck)
                    Numerator *= (-1);
                return true;
            }

            if (Regex.IsMatch(frStr, pattern2, RegexOptions.IgnoreCase))
            {
                int j;
                double temp = 0;
                double ten = 0;
                if (frStr[0] == '-')
                    rCheck = true;
                if (rCheck)
                    j = 1;
                else
                    j = 0;
                for (; j < frStr.Length; j++)
                {
                    if (Char.IsDigit(frStr[j]))
                        numeratorStr = numeratorStr.Insert(numeratorStr.Length, frStr[j].ToString());
                    else
                        temp = j;
                }

                if (temp == 0)
                    denominatorStr = "1";
                else
                {
                    while (temp < frStr.Length)
                    {
                        ten++;
                        temp++;
                    }

                    temp = Math.Pow(10, ten-1);

                    denominatorStr = temp.ToString();
                }
                
                Denominator = Convert.ToUInt32(denominatorStr);
                Numerator = Convert.ToInt32(numeratorStr);

                if (rCheck)
                    Numerator *= (-1);
                return true;
            }
            Console.WriteLine("Проверьте ввод.");

            return false;
        }

        public static Fraction operator +(Fraction fr1, Fraction fr2)
        {
            Fraction result = new Fraction();
            result.Denominator = result.CommonDenominator(fr1, fr2);
            result.Numerator = (int) (fr1.Numerator * (result.Denominator / fr1.Denominator) +
                                      fr2.Numerator * (result.Denominator / fr2.Denominator));
            return result;
        }

        public static Fraction operator -(Fraction fr1, Fraction fr2)
        {
            Fraction result = new Fraction();
            result.Denominator = result.CommonDenominator(fr1, fr2);
            result.Numerator = (int) (fr1.Numerator * (result.Denominator / fr1.Denominator) -
                                      fr2.Numerator * (result.Denominator / fr2.Denominator));
            return result;
        }

        public static Fraction operator *(Fraction fr1, Fraction fr2)
        {
            Fraction result = new Fraction();
            result.Numerator = fr1.Numerator * fr2.Numerator;
            result.Denominator = fr1.Denominator * fr2.Denominator;
            return result;
        }

        public static Fraction operator /(Fraction fr1, Fraction fr2)
        {
            int temp1 = fr2.Numerator;
            uint temp2 = fr2.Denominator;
            if (temp1 < 0)
                fr2.Numerator = (int) fr2.Denominator * (-1);
            else
                fr2.Numerator = (int) fr2.Denominator;
            fr2.Denominator = (uint) Math.Abs(temp1);
            var result = fr1 * fr2;
            fr2.Numerator = temp1;
            fr2.Denominator = temp2;
            return result;
        }

        public static bool operator ==(Fraction fr1, Fraction fr2)
        {
            if (fr2 is not null && fr2.Equals(fr1))
                return true;
            return false;
        }

        public static bool operator !=(Fraction fr1, Fraction fr2)
        {
            return !(fr1 == fr2);
        }

        public static bool operator >(Fraction fr1, Fraction fr2)
        {
            if (fr1 == fr2)
                return false;
            if (fr1.Numerator * (fr1.CommonDenominator(fr1, fr2) / fr1.Denominator) >
                fr2.Numerator * (fr2.CommonDenominator(fr1, fr2) / fr2.Denominator))
                return true;
            return false;
        }

        public static bool operator <(Fraction fr1, Fraction fr2)
        {
            if (fr1 != fr2)
                if (fr1 > fr2)
                    return false;
                else
                    return true;
            return false;
        }

        public static bool operator <=(Fraction fr1, Fraction fr2)
        {
            if (fr1 < fr2 || fr1 == fr2)
                return true;
            return false;
        }

        public static bool operator >=(Fraction fr1, Fraction fr2)
        {
            if (fr1 > fr2 || fr1 == fr2)
                return true;
            return false;
        }

        public static implicit operator int(Fraction fr1)
        {
            int result = (int) (fr1.Numerator / fr1.Denominator);
            return result;
        }
        
        public static implicit operator Fraction(int num)
        {
            Fraction result = new Fraction();
            result.Numerator = num;
            result.Denominator = 1;
            return result;
        }
        
        public static implicit operator double(Fraction fr1)
        {
            double result = (double) fr1.Numerator / fr1.Denominator;
            return result;
        }
        
        public static implicit operator Fraction(double num)
        {
            int ten = 0;
            while (true)
            {
                double temp = num % 10;
                if (temp == 0)
                    break;
                num *= 10;
                ten++;
            }

            Fraction result = new Fraction();
            result.Numerator = (int) num;
            result.Denominator = (uint) (Math.Pow(10,ten));
            return result;
        }

        public bool Equals(Fraction other)
        {
            if (ReferenceEquals(null, other)) return false;
            if (ReferenceEquals(this, other)) return true;
            return Numerator == other.Numerator && Denominator == other.Denominator;
        }

        public override bool Equals(object obj)
        {
            if (ReferenceEquals(null, obj)) return false;
            if (ReferenceEquals(this, obj)) return true;
            if (obj.GetType() != this.GetType()) return false;
            return Equals((Fraction) obj);
        }

        public override int GetHashCode()
        {
            return HashCode.Combine(Numerator, Denominator);
        }

        public int CompareTo(Fraction other)
        {
            if (ReferenceEquals(this, other)) return 0;
            if (ReferenceEquals(null, other)) return 1;
            var numeratorComparison = Numerator.CompareTo(other.Numerator);
            if (numeratorComparison != 0) return numeratorComparison;
            return Denominator.CompareTo(other.Denominator);
        }
    }
}