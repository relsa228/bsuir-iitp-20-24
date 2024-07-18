#ifndef ListH
#define ListH
#pragma once
#endif

template<typename ItemType>
class Node
{
public:
	Node *pNext;
	ItemType data;

	Node(ItemType data=ItemType(), Node *pNext = nullptr)
	{
		this->data=data;
		this->pNext=pNext;
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
	void DeleteElem(int index);
	int GetSize() {return size;}
	ItemType& operator[](int index);
private:
	unsigned int size;
	Node<ItemType> *head;
};

template<typename ItemType>
List<ItemType>::List()
{
	size = 0;
	head = nullptr;
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
	else
	{
		Node<ItemType> *current = this->head;
		while(current->pNext!= nullptr)
		{
			current = current->pNext;
		}
		current->pNext = new Node<ItemType>(data);
	}
	size++;
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

template<typename ItemType>
void List<ItemType>::PopFront()
{
	Node<ItemType> *temp = head;
	head = head->pNext;
	delete temp;
	size--;
}

template<typename ItemType>
void List<ItemType>::DeleteElem(int index)
{
	if ((head != nullptr) && (index < size) && (index >= 0))
	{
		Node<ItemType> *temp = head, *helping = head;

		for (int i = 0; i < index; i++)
		{
			helping = temp;
			temp = temp->pNext;
		}

		if (temp == head)
		{
			head = temp->pNext;
		}
		else
		{
			helping->pNext = temp->pNext;
		}
		delete temp;
		size--;
	}
}

