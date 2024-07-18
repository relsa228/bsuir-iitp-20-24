//---------------------------------------------------------------------------
#include "List.h"
#include "HashElem.h"
#include <vcl.h>
#ifndef HashTableH
#define HashTableH
//---------------------------------------------------------------------------
#endif

class HashTable: public List<HashElem>, public HashElem
{
	public: List<HashElem> hashTable[12];
	public: HashElem elem;

	public: void toHashTable (TMemo* Memo)
	{
		elem.toHash();
		hashTable[elem.hash].PushBack(elem);
		if (hashTable[elem.hash].GetSize() == 1)
			Memo->Lines->Strings[elem.hash] += IntToStr(elem.data);
		else
			Memo->Lines->Strings[elem.hash] += ", " + IntToStr(elem.data);

	}

	public: void deleteElem (TMemo* Memo, int sizeL)
	{
		int check = 0;
		for(int i = sizeL-1; i >= 0; i--)
		{
			if(hashTable[elem.hash][i].data == elem.data)
			{
				hashTable[elem.hash].DeleteElem(i);
				check++;
			}
		}

		if (check == 0)
			ShowMessage("Элемента не существует");
		else
		{
			if(hashTable[elem.hash].GetSize() == 0)
				Memo->Lines->Strings[elem.hash] = IntToStr(elem.hash) + ". ";
			else
			{
				Memo->Lines->Strings[elem.hash] = IntToStr(elem.hash) + ". ";
				Memo->Lines->Strings[elem.hash] += IntToStr(hashTable[elem.hash][0].data);
				for(int i = 1; i < hashTable[elem.hash].GetSize(); i++)
					Memo->Lines->Strings[elem.hash] += ", " + IntToStr(hashTable[elem.hash][i].data);
			}
		}
	}

	public: void delHashBranch (TMemo* Memo)
	{
		elem.toHash();
		if (hashTable[elem.hash].GetSize() == 0)
			ShowMessage("Ветвь пуста");
		else
		{
			while(hashTable[elem.hash].GetSize())
				hashTable[elem.hash].PopFront();
			Memo->Lines->Strings[elem.hash] = IntToStr(elem.hash) + ". ";
		}
	}

	public: bool findElem (TEdit* Edit, int hash)
	{
		if(hash<=12 && hash>=0)
		{
			Edit->Text="";
			Edit->Font->Color = clWindowText;
			if (hashTable[hash].GetSize() == 0)
			{
				Edit->Text="Пусто";
				return false;
			}
			else
			{
				for(int i = 0; i < hashTable[hash].GetSize()-1; i++)
					Edit->Text+=IntToStr(hashTable[elem.hash][i].data)+", ";
				Edit->Text+=IntToStr(hashTable[elem.hash][hashTable[hash].GetSize()-1].data);
				return true;
			}
		}
		else
		{
			ShowMessage("Введите действительный хэш");
			return false;
		}
	}

	public: void minElem (TEdit* Edit)
	{
		int check = 0;
		Edit->Text = "";
		for(int i = 0; i < 12; i++)
			if (hashTable[i].GetSize() != 0)
			{
				for(int j = 0; j<hashTable[i].GetSize(); j++)
					if(j<hashTable[i].GetSize()-1)
						Edit->Text+=IntToStr(hashTable[i][j].data)+", ";
					else
						Edit->Text+=IntToStr(hashTable[i][j].data);
				check++;
				break;
			}
		if (check == 0)
            ShowMessage("В таблице отсутсвуют элементы");
	}
};