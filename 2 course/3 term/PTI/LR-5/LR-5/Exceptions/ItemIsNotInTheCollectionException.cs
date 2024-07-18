using System;

namespace LR_4.Exceptions
{
    public class ItemIsNotInTheCollectionException : Exception
    {
        public override string Message { get; }

        public ItemIsNotInTheCollectionException()
        {
            Message = "Объект отсутвует в коллекции.";
        }
    }
}