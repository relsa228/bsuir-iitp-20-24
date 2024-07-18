//---------------------------------------------------------------------------

#ifndef PolskaZapisH
#define PolskaZapisH
#include "Stack.h"
#include <vcl.h>
//---------------------------------------------------------------------------
#endif

using namespace std;

struct PolskaZapis
{
	String note;
	String polskNote;

	String convert()
	{
		List<char> symbol;

		for(int i = 1; i < note.Length(); i++)
		{
			if (note[i] == ' ')
			{
				note.Delete(i, 1);
			}
		}
		int check = 0,  f = 1;
		for (int i = 1; i <= note.Length(); i++)
		{
			int num = symbol.GetSize() - 1;
			if(isdigit(note[i]) || note[i] == ',')
			{
				polskNote.Insert(note[i],f);
				f++;
				check = 1;
			}
			else if (check == 1)
			{
				polskNote.Insert(" ",f);
				f++;
				check = 0;
				i--;
			}

			else if(note[i] == '+')
			{
				if (symbol.GetSize() == 0 || symbol[num] == '(')
				{
					symbol.PushBack(note[i]);
				}
				else if (symbol[num] == '-' || symbol[num] == '+')
				{
					polskNote.Insert(symbol[num],f);
					symbol.DeleteElem(num);
					f++;
					symbol.PushBack(note[i]);
				}
				else if (symbol[num] == '*' || symbol[num] == '/')
				{
					while (symbol.GetSize()!=0)
					{
						int j = symbol.GetSize() - 1;
						if (symbol[j] == '(')
							break;
						polskNote.Insert(symbol[j],f);
						f++;
						symbol.DeleteElem(j);
					}

					symbol.PushBack(note[i]);
				}
			}

			else if(note[i] == '-')
			{
				if (symbol.GetSize() == 0 || symbol[num] == '(')
				{
					symbol.PushBack(note[i]);
				}
				else if (symbol[num] == '-' || symbol[num] == '+')
				{
					polskNote.Insert(symbol[num],f);
					symbol.DeleteElem(num);
					f++;
					symbol.PushBack(note[i]);
				}
				else if (symbol[num] == '*' || symbol[num] == '/')
				{
					while (symbol.GetSize()!=0)
					{
						int j = symbol.GetSize() - 1;
						if (symbol[j] == '(')
							break;
						polskNote.Insert(symbol[j],f);
						f++;
						symbol.DeleteElem(j);
					}
					symbol.PushBack(note[i]);
				}
			}

			else if(note[i] == '*')
			{
				if (symbol.GetSize() == 0 || symbol[num] == '(')
				{
					symbol.PushBack(note[i]);
				}
				else if (symbol[num] == '-' || symbol[num] == '+')
				{
					symbol.PushBack(note[i]);
				}
				else if (symbol[num] == '*' || symbol[num] == '/')
				{
					polskNote.Insert(symbol[num],f);
					symbol.DeleteElem(num);
					f++;
					symbol.PushBack(note[i]);
				}
			}

			else if(note[i] == '/')
			{
				if (symbol.GetSize() == 0 || symbol[num] == '(')
				{
					symbol.PushBack(note[i]);
				}
				else if (symbol[num] == '-' || symbol[num] == '+')
				{
					symbol.PushBack(note[i]);
				}
				else if (symbol[num] == '*' || symbol[num] == '/')
				{
					polskNote.Insert(symbol[num],f);
					symbol.DeleteElem(num);
					f++;
					symbol.PushBack(note[i]);
				}
			}

			else if(note[i] == '(')
			{
				symbol.PushBack(note[i]);
			}

			else if(note[i] == ')')
			{
				while (symbol.GetSize()!=0)
				{
					int j = symbol.GetSize() - 1;
					if (symbol[j] == '(')
						break;
					polskNote.Insert(symbol[j],f);
					f++;
					symbol.DeleteElem(j);
				}
				int j = symbol.GetSize() - 1;
				symbol.DeleteElem(j);
				while (symbol.GetSize()!=0)
				{
					int j = symbol.GetSize() - 1;
                    if (symbol[j] == '(')
						break;
					polskNote.Insert(symbol[j],f);
					f++;
					symbol.DeleteElem(j);
				}
			}
		}
		while (symbol.GetSize()!=0)
		{
			int j = symbol.GetSize() - 1;
			polskNote.Insert(symbol[j],f);
			f++;
			symbol.DeleteElem(j);
		}
		return polskNote;
	}

	float schet()
	{
		List<float> nums;
		String num;
		int poz = polskNote.Length() - 1;
		if (polskNote[poz] != '-' && polskNote[poz] != '*' && polskNote[poz] != '/' && polskNote[poz] != '+')
		{
			polskNote.Insert(" ", poz+1);
		}
		for (int i = 1, f = 1; i <= polskNote.Length(); i++)
		{
			int top = nums.GetSize() - 1;
			if(isdigit(polskNote[i]) || polskNote[i] == ',')
			{
				num.Insert(polskNote[i],f);
				f++;
			}
			else if (polskNote[i] == '+' || polskNote[i] == '-' || polskNote[i] == '*' || polskNote[i] == '/' || polskNote[i] == ' ')
			{
				if (polskNote[i] == '+')
				{
					float sum = nums[top];
					nums.DeleteElem(top);
					top--;
					sum = sum + nums[top];
					nums.DeleteElem(top);
					nums.PushBack(sum);
				}
				else if (polskNote[i] == '-')
				{
					float sum = nums[top];
					nums.DeleteElem(top);
					top--;
					sum = nums[top] - sum;
					nums.DeleteElem(top);
					nums.PushBack(sum);
				}
				else if (polskNote[i] == '*')
				{
					float sum = nums[top];
					nums.DeleteElem(top);
					top--;
					sum = sum * nums[top];
					nums.DeleteElem(top);
					nums.PushBack(sum);
				}
				if (polskNote[i] == '/')
				{
					float sum = nums[top];
					nums.DeleteElem(top);
					top--;
					sum = nums[top] / sum;
					nums.DeleteElem(top);
					nums.PushBack(sum);
				}
				if (polskNote[i] == ' ')
				{
					float number = StrToFloat(num);
					//ShowMessage(number);
					num = " ";
					f = 1;
					nums.PushBack(number);
				}
			}
		}
		return nums[0];
	}
};