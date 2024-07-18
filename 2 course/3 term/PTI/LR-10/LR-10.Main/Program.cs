using System;
using System.Collections.Generic;
using System.Reflection;

namespace LR_10.Main
{
    class Program
    {
        static void Main(string[] args)
        {
            const string Dll = "LR-10FileServiceLib.dll";
            const string Json = "Metadata.json";

            List<Employee> employees = new List<Employee>();
            employees.Add(new Employee("Валерий Альбертович Жмышенко", 54, false));
            employees.Add(new Employee("Юрий Михайлович Хованский", 28, true));
            employees.Add(new Employee("Роман Мальцев", 34, false));
            employees.Add(new Employee("Андрей Нифедов", 40, true));

            Assembly asm = Assembly.LoadFrom(Dll);
            Type t = asm.GetType("LR_10FileServiceLib.FileService`1", true, true);
            t = t.MakeGenericType(typeof(Employee));
            object  obj = Activator.CreateInstance(t);
            
            MethodInfo saveData = t.GetMethod("SaveData");
            MethodInfo readFile = t.GetMethod("ReadFile");

            saveData.Invoke(obj, new object[] {employees, Json});
            var anser = readFile.Invoke(obj, new object[] {Json});
            
            var resultList = anser as List<Employee>;
            foreach (var employee in resultList)
                Console.WriteLine(employee.Info());
        }
    }
}