using System;
using LR_4.Exceptions;
using LR_4.Interfaces;

namespace LR_4.Collections
{
    public class MyCustomCollection<T> : ICustomCollection<T> where T : IComparable
    {
        public int Count { get; set; }
        public int Cursor;
        private Node<T> _head;

        public MyCustomCollection()
        {
            Count = 0;
            Cursor = 0;
            _head = new Node<T>();
        }
        
        public T this[int index]
        {
            get
            {
               try
                {
                    if (index < 1 || index > Count)
                      throw new IndexOutOfRangeException();
                    ref Node<T> temp = ref _head;
                    for (int i = 0; i < index; i++)
                        temp = ref temp.PNext;
                    return temp.Data;
               }
                catch (IndexOutOfRangeException e)
                {
                    Console.WriteLine(e.Message);
                }
                catch (NullReferenceException e)
                {
                    Console.WriteLine(e.Message);
                }
                return default;
            }
            set
            {
                try
                {
                    if (index < 1 || index > Count)
                        throw new IndexOutOfRangeException();
                    ref Node<T> temp = ref _head;
                    for (int i = 1; i < index; i++)
                        temp = ref temp.PNext;
                    temp.Data = value;
                }
                catch (NullReferenceException e)
                {
                    Console.WriteLine(e.Message);
                }
                catch (IndexOutOfRangeException e)
                {
                    Console.WriteLine(e);
                }
            }
        }

        public void Reset()
        {
            Cursor = 0;
        }

        public void Next()
        {
            if (Cursor == Count+1)
                Cursor = 1;
            else
                Cursor++;
        }

        public T Current()
        {
            return this[Cursor];
        }

        public void Add(T item)
        {
            try
            {
                ref Node<T> temp = ref _head;
                Count++;
                for (int i = 0; i < Count; i++)
                {
                    if (temp.PNext == null)
                    { 
                        temp.PNext = new Node<T>(); 
                        temp.PNext.PPrev = temp; 
                        temp.PNext.Data = item;
                        break;
                    }
                    else 
                        temp = ref temp.PNext;
                }
                
            }
            catch (NullReferenceException e)
            {
                Console.WriteLine(e.Message);
            }
        }

        public void Remove(T item)
        {
            try
            {
                if (Count == 0)
                    throw new ItemIsNotInTheCollectionException();
                ref Node<T> temp = ref _head.PNext;
                for (int i = 0; i < Count; i++)
                {
                    if (temp.Data.CompareTo(item) == 0)
                    {
                        if (temp.PNext == null)
                            temp.PPrev.PNext = null;
                        else
                        {
                            temp.PPrev.PNext = temp.PNext;
                            temp.PPrev.PNext.PPrev = temp.PPrev;
                        }
                    }
                    else if (i >= Count - 1)
                        throw new ItemIsNotInTheCollectionException();
                    else
                        temp = ref temp.PNext;
                }

                Count--;
            }
            catch (NullReferenceException e)
            {
                Console.WriteLine(e.Message);
            }
            catch (ItemIsNotInTheCollectionException e)
            {
                Console.WriteLine(e.Message);
            }
        }

        public void RemoveCurrent()
        {
            this.Remove(this[Cursor]);
            Count--;
        }
    }
}