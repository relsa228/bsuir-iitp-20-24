using System.Collections.Generic;
using System.IO;

namespace LR_8
{
    public class FileService : IFileService

    {
        public IEnumerable<Employee> ReadFile(string fileName)
        {
            using (BinaryReader reader = new BinaryReader(File.Open(fileName, FileMode.Open)))
            {
                while (reader.PeekChar() > -1)
                {
                    Employee employee = new Employee(default, default, default);
                    
                    employee.Name = reader.ReadString();
                    employee.Age = reader.ReadInt32();
                    employee.HigherEducation = reader.ReadBoolean();
                    
                    yield return employee;
                }
            }
        }

        public void SaveData(IEnumerable<Employee> data, string fileName)
        {
            using (BinaryWriter writer = new BinaryWriter(File.Open(fileName, FileMode.OpenOrCreate)))
            {
                foreach (Employee employee in data)
                {
                    writer.Write(employee.Name);
                    writer.Write(employee.Age);
                    writer.Write(employee.HigherEducation);
                }
            }
        }
    }
}