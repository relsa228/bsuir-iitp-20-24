using System.Collections.ObjectModel;
using System.IO;
using System.Linq;

namespace LR_8
{
    class Program
    {
        static void Main(string[] args)
        {
            Collection<Employee> collection = new Collection<Employee>();
            string path = "EmployeeList.txt";
            
            Employee employeeFirst = new Employee("Бараболя Григорий", 21, true);
            collection.Add(employeeFirst);
            Employee employeeSecond = new Employee("Осадчий Олег", 27, true);
            collection.Add(employeeSecond);
            Employee employeeThird = new Employee("Жмышенко Валерий", 54, false);
            collection.Add(employeeThird);
            Employee employeeFourth = new Employee("Анисимов Владимир", 75, true);
            collection.Add(employeeFourth);
            Employee employeeFifth = new Employee("Владымцев Вадим", 25, false);
            collection.Add(employeeFifth);
            Employee employeeSixth = new Employee("Бутома Виталий", 27, true);
            collection.Add(employeeSixth);

            FileService fileService = new FileService();
            fileService.SaveData(collection, path);
            
            if(File.Exists("NewEmployeeList.txt"))
                File.Delete("NewEmployeeList.txt");
            File.Move("EmployeeList.txt", "NewEmployeeList.txt");

            Collection<Employee> newCollection = new Collection<Employee>();
            foreach (var employee in fileService.ReadFile("NewEmployeeList.txt"))
                newCollection.Add(employee);
                    
            IOrderedEnumerable<Employee> auto= newCollection.OrderBy(s=>s.Name);

            foreach (Employee employee in auto)
                employee.Info();
        }
    }
}