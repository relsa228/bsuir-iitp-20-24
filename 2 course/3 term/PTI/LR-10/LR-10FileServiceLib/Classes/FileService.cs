using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text.Json;

namespace LR_10FileServiceLib
{
    public class FileService<T>:IFileService<T> where T : class
    {
        public IEnumerable<T> ReadFile(string fileName)
        {
            using (FileStream fs = new FileStream(fileName,FileMode.Open))
            {
                var options = new JsonSerializerOptions { IncludeFields = true };
                var result = JsonSerializer.DeserializeAsync<List<T>>(fs,options).Result;
                return result;
            }
        }

        public void SaveData(IEnumerable<T> data, string fileName)
        { 
            using (FileStream fs = new FileStream(fileName, FileMode.OpenOrCreate))
            {
                var options = new JsonSerializerOptions { IncludeFields = true };
                JsonSerializer.SerializeAsync<List<T>>(fs,data.ToList(),options).Wait();
            }
        }
    }
}