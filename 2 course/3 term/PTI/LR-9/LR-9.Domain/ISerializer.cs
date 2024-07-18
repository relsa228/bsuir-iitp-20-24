using System.Collections.Generic;
using System.Threading.Tasks;

namespace LR_9.Domain
{
    public interface ISerializer
    {
        IEnumerable<Factory.Factory> DeSerializeByLINQ(string fileName); 
        IEnumerable<Factory.Factory> DeSerializeXML(string fileName); 
        IEnumerable<Factory.Factory> DeSerializeJSON(string fileName); 
        void SerializeByLINQ(IEnumerable<Factory.Factory> xxx,	string fileName); 
        void SerializeXML(IEnumerable<Factory.Factory> xxx,	string fileName); 
        void SerializeJSON(IEnumerable<Factory.Factory> xxx, string fileName); 
    }
}