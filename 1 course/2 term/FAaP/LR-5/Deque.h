//---------------------------------------------------------------------------

#ifndef DequeH
#define DequeH
//---------------------------------------------------------------------------
#endif

template<typename ItemType>
class Node
{
public:
    Node *pNext;
    Node *pPrev;
    ItemType data;

    Node(ItemType data=ItemType(), Node *pNext = nullptr, Node *pPrev = nullptr)
	{
        this->data=data;
        this->pNext=pNext;
        this->pPrev=pPrev;
    }
};

template<typename ItemType>
class List
{
public:
    List();
    ~List();
    void PushBack(ItemType data);
    void PopFront();
    int GetSize() {return size;}
    ItemType& operator[](int index);
	unsigned int size;
	public: Node<ItemType> *head;
	public: Node<ItemType> *tail;
};

template<typename ItemType>
List<ItemType>::List()
{
    size = 0;
	head = nullptr;
    tail = nullptr;
}

template<typename ItemType>
List<ItemType>::~List()
{
    while(size)
    {
		PopFront();
    }
}



template<typename ItemType>
void List<ItemType>::PushBack(ItemType data)
{
	if(head == nullptr)
    {
        head = new Node<ItemType>(data);
    }
    else if (tail == nullptr)
    {
        head->pNext = new Node<ItemType>(data);
        tail = head->pNext;
		tail->pPrev = head;
    }
    else
    {
        tail->pNext = new Node<ItemType>(data);
        tail=tail->pNext;
    }
    size++;
}

template<typename ItemType>
void List<ItemType>::PopFront()
{
    Node<ItemType> *temp = head;
    head = head->pNext;
    head->pPrev = nullptr;
	delete temp;
    size--;
}


template<typename ItemType>
ItemType & List<ItemType>::operator[](int index)
{
    int counter = 0;
    Node<ItemType> *current = this->head;
    while(current!=nullptr)
    {
		if(counter == index)
		{
			return current->data;
		}
		current = current->pNext;
		counter++;
	}
}
