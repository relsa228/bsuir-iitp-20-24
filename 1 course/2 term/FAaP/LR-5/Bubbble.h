//---------------------------------------------------------------------------
#ifndef BubbbleH
#define BubbbleH
#include "Deque.h"
//---------------------------------------------------------------------------
#endif

class Bubble: public List<int>, public Node<int>
{
	public: void bubbleSort(List<int> &A)
	{
		for (int i = 0; i < A.GetSize() - 1; i++)
		{
			for (int j = 0; j < A.GetSize() - i - 1; j++)
			{
				if (A[j + 1] < A[j])
				{
					int temp1 = A[j], temp2 = A[j + 1];
					A[j] = temp2;
					A[j+1]=temp1;
				}
			}
		}
	}

	public: int retHead(List<int> &A)
	{
		return A.head->data;
	}

	public: int retTail(List<int> &A)
	{
		return A.tail->data;
	}

	public: int IsEmpty(List<int> &A)
	{
		if (A.GetSize() == 0)
			return 1;
		else
			return 0;

	}
};
