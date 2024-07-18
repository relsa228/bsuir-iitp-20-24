using System.Collections.Generic;

namespace LR_8
{
    public class EmployeeComparer<T>:IComparer<T>
    where T:Employee
    {
        public int Compare(T x, T y)
        {
            if (x.Name[0] < y.Name[0])
                return-1;
            if (x.Name[0] > y.Name[0])
                return 1;
            return 0;
        }
    }
}