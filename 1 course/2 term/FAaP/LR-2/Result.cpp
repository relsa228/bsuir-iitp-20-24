//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Result.h"
#include "MaleFemale.h"
#include "List.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TResultWind *ResultWind;

List<Human> suitors;
List<Human> brides;
Human questionnarie;
int num1, num2, listSize;
List<int> questNum;

__fastcall TResultWind::TResultWind(TComponent* Owner)
	: TForm(Owner)
{
	TStringList* suitorsF = new TStringList;
	suitorsF->LoadFromFile("suitors.txt");
	ResultMemo->Lines->LoadFromFile("suitors.txt");
	num1=(suitorsF->Count)/14;

	Human *suitorsArr = new Human[num1];
	for(int i = 0; i < num1; i++)
	{
		suitors.PushBack(suitorsArr[i]);
	}

	for(int i = 0; i < num1; i++)
	{
		suitors[i].num = StrToInt(ResultMemo->Lines->Strings[0]);
		ResultMemo->Lines->Delete(0);

		suitors[i].gender = StrToInt(ResultMemo->Lines->Strings[0]);
		ResultMemo->Lines->Delete(0);

		suitors[i].pair = StrToInt(ResultMemo->Lines->Strings[0]);
		ResultMemo->Lines->Delete(0);

		suitors[i].name = ResultMemo->Lines->Strings[0];
		ResultMemo->Lines->Delete(0);

		suitors[i].age = StrToInt(ResultMemo->Lines->Strings[0]);
		ResultMemo->Lines->Delete(0);

		suitors[i].fromAge = StrToInt(ResultMemo->Lines->Strings[0]);
		ResultMemo->Lines->Delete(0);

		suitors[i].toAge = StrToInt(ResultMemo->Lines->Strings[0]);
		ResultMemo->Lines->Delete(0);

		suitors[i].growth = StrToInt(ResultMemo->Lines->Strings[0]);
		ResultMemo->Lines->Delete(0);

		suitors[i].fromGrowth = StrToInt(ResultMemo->Lines->Strings[0]);
		ResultMemo->Lines->Delete(0);

		suitors[i].toGrowth = StrToInt(ResultMemo->Lines->Strings[0]);
		ResultMemo->Lines->Delete(0);

		suitors[i].weight = StrToInt(ResultMemo->Lines->Strings[0]);
		ResultMemo->Lines->Delete(0);

		suitors[i].fromWeight = StrToInt(ResultMemo->Lines->Strings[0]);
		ResultMemo->Lines->Delete(0);

		suitors[i].toWeight = StrToInt(ResultMemo->Lines->Strings[0]);
		ResultMemo->Lines->Delete(0);

		suitors[i].hobby = ResultMemo->Lines->Strings[0];
		ResultMemo->Lines->Delete(0);
	}
	for(int i = 0; i < num1; i++)
	{
		if(suitors[i].pair == 0)
			suitors.DeleteElem(i);
	}
	ResultMemo->Lines->Clear();
	delete suitorsF;

	TStringList* bridesF = new TStringList;
	bridesF->LoadFromFile("brides.txt");
	ResultMemo->Lines->LoadFromFile("brides.txt");
	num2=(bridesF->Count)/14;

	Human *bridesArr = new Human[num1];
	for(int i = 0; i < num1; i++)
	{
		brides.PushBack(bridesArr[i]);
	}

	for(int i = 0; i < num2; i++)
	{
		brides[i].num = StrToInt(ResultMemo->Lines->Strings[0]);
		ResultMemo->Lines->Delete(0);

		brides[i].gender = StrToInt(ResultMemo->Lines->Strings[0]);
		ResultMemo->Lines->Delete(0);

		brides[i].pair = StrToInt(ResultMemo->Lines->Strings[0]);
		ResultMemo->Lines->Delete(0);

		brides[i].name = ResultMemo->Lines->Strings[0];
		ResultMemo->Lines->Delete(0);

		brides[i].age = StrToInt(ResultMemo->Lines->Strings[0]);
		ResultMemo->Lines->Delete(0);

		brides[i].fromAge = StrToInt(ResultMemo->Lines->Strings[0]);
		ResultMemo->Lines->Delete(0);

		brides[i].toAge = StrToInt(ResultMemo->Lines->Strings[0]);
		ResultMemo->Lines->Delete(0);

		brides[i].growth = StrToInt(ResultMemo->Lines->Strings[0]);
		ResultMemo->Lines->Delete(0);

		brides[i].fromGrowth = StrToInt(ResultMemo->Lines->Strings[0]);
		ResultMemo->Lines->Delete(0);

		brides[i].toGrowth = StrToInt(ResultMemo->Lines->Strings[0]);
		ResultMemo->Lines->Delete(0);

		brides[i].weight = StrToInt(ResultMemo->Lines->Strings[0]);
		ResultMemo->Lines->Delete(0);

		brides[i].fromWeight = StrToInt(ResultMemo->Lines->Strings[0]);
		ResultMemo->Lines->Delete(0);

		brides[i].toWeight = StrToInt(ResultMemo->Lines->Strings[0]);
		ResultMemo->Lines->Delete(0);

		brides[i].hobby = ResultMemo->Lines->Strings[0];
		ResultMemo->Lines->Delete(0);
	}
	for(int i = 0; i < num2; i++)
	{
		if(	brides[i].pair == 0)
			brides.DeleteElem(i);
	}
	ResultMemo->Lines->Clear();
	delete bridesF;
}
//---------------------------------------------------------------------------

void __fastcall TResultWind::FindResultClick(TObject *Sender)
{	if (questionnarie.gender == 1)
	{
		int check = 0;
		for(int i = 0; i < num2; i++)
		{
			if (Human::comparison(questionnarie, brides[i]))
			{
				Human::showElem(brides[i], ViewMemo);
				check++;
				questNum.PushBack(brides[i].num);
				listSize++;
			}
		}

		if (check==0)
		{
			ShowMessage("Пріемлемаго знакомца не найдено. Ваша анкета занесена въ списокъ.");
			TFileStream *suitorsF = new TFileStream("suitors.txt", fmOpenReadWrite);
			Human::WriteInFile(suitorsF, questionnarie);
			delete suitorsF;
			Close();
		}
		else
		{
			ChoiceEdit->Enabled = true;
			Choice->Enabled = true;
			Num->Enabled = true;
		}
	}
	else if (questionnarie.gender == 0)
	{
		int check = 0;
		for(int i = 0; i < num1; i++)
		{
			if (Human::comparison(questionnarie, suitors[i]))
			{
				Human::showElem(suitors[i], ViewMemo);
				check++;
				questNum.PushBack(suitors[i].num);
				listSize++;
			}
		}

		if (check==0)
		{
			ShowMessage("Пріемлемаго знакомца не найдено. Ваша анкета занесена въ списокъ.");
			TFileStream *bridesF = new TFileStream("brides.txt", fmOpenReadWrite);
			Human::WriteInFile(bridesF, questionnarie);
			delete bridesF;
			Close();
		}
		else
		{
			ChoiceEdit->Enabled = true;
            Choice->Enabled = true;
			Num->Enabled = true;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TResultWind::SaveQuestClick(TObject *Sender)
{
	questionnarie.fromAge = StrToInt(FromAgeEdit->Text);
	questionnarie.toAge =  StrToInt(ToAgeEdit->Text);
	questionnarie.fromGrowth =  StrToInt(FromGrowthEdit->Text);
	questionnarie.toGrowth = StrToInt(ToGrowthEdit->Text);
	questionnarie.fromWeight =  StrToInt(FromWeightEdit->Text);
	questionnarie.toWeight = StrToInt(ToWeightEdit->Text);
	if (Human::check(questionnarie) == true)
	{
		FindResult->Enabled = true;
	}
	else
	{
		ShowMessage("Казусъ. Провѣрьте введенную метрику.");
	}
}
//---------------------------------------------------------------------------

void __fastcall TResultWind::FormShow(TObject *Sender)
{
	ResultMemo->Lines->LoadFromFile("temporaryQuestionnarie.txt");
	DeleteFile("temporaryQuestionnarie.txt");

	questionnarie.num = StrToInt(ResultMemo->Lines->Strings[0]);
	questionnarie.gender = StrToInt(ResultMemo->Lines->Strings[1]);
	questionnarie.pair = StrToInt(ResultMemo->Lines->Strings[2]);
	questionnarie.name = ResultMemo->Lines->Strings[3];
	questionnarie.age = StrToInt(ResultMemo->Lines->Strings[4]);
	questionnarie.growth = StrToInt(ResultMemo->Lines->Strings[5]);
	questionnarie.weight = StrToInt(ResultMemo->Lines->Strings[6]);
	questionnarie.hobby = ResultMemo->Lines->Strings[7];
	ResultMemo->Lines->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TResultWind::ChoiceClick(TObject *Sender)
{
	int questiNum = StrToInt(ChoiceEdit->Text);
	int check = 0;
	for(int i = 0; i < listSize; i++)
	{
		if (questiNum == questNum[i])
		{
			ShowMessage("Знакомецъ нашелся.");
			if (questionnarie.gender == 0)
			{
				for(int j = 0; j < num1; j++)
				{
					if (suitors[j].num == questiNum)
					{
						suitors[j].pair = 0;
					}
				}
				questionnarie.pair = 0;
				brides.PushBack(questionnarie);
			}
			else
			{
				for(int j = 0; j < num2; j++)
				{
					if (brides[j].num == questiNum)
					{
						brides[j].pair = 0;
					}
				}
				questionnarie.pair = 0;
				suitors.PushBack(questionnarie);
			}
			AnsiString FileNameS="suitors.txt";
			AnsiString FileNameB="brides.txt";
			DeleteFile(FileNameS);
			DeleteFile(FileNameB);

			TFileStream *suitorsF = new TFileStream("suitors.txt", fmCreate);
			for (int i = 0; i < suitors.GetSize(); i++)
			{
				Human::WriteInFile(suitorsF, suitors[i]);
			}
			delete suitorsF;

			TFileStream *bridesF = new TFileStream("brides.txt", fmCreate);
			for (int i = 0; i < brides.GetSize(); i++)
			{
				Human::WriteInFile(bridesF, brides[i]);
			}
			delete bridesF;

			check++;
			Close();
		}
	}

	if (check == 0)
	{
		ShowMessage("Введите дѣйствительный номеръ анкеты.");
	}
}
//---------------------------------------------------------------------------
