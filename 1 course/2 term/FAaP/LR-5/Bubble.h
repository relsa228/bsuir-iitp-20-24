//---------------------------------------------------------------------------
#ifndef BubbleH
#define BubbleH
//---------------------------------------------------------------------------
#endif

struct BubbleSort
{
	public: List<int> deque;

	void bubbleSort(deque)
	{
		for (int i = 0; i < deque.GetSize() - 1; i++)
		{
			for (int j = 0; j < deque.GetSize() - i - 1; j++)
			{
				if (deque[j + 1] < deque[j])
				{
					swap(deque[j], deque[j + 1]);
				}
			}
		}
	}

	void printDeque(deque, TListBox* DequeBox)
	{
		for(int i = 0; i < deque.GetSize(); i++)
			DequeBox->Items[i] = deque[i];
    }

};
