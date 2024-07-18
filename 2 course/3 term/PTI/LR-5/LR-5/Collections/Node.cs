namespace LR_4.Collections
{
    public class Node<T>
    {
        public T Data;
        public Node<T> PNext;
        public Node<T> PPrev;

        public Node()
        {
            PNext = null;
            Data = default;
        }
    }
}