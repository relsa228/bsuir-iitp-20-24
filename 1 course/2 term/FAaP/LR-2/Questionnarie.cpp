#include <vcl.h>
#pragma hdrstop
#include "Questionnarie.h"
#include "MaleFemale.h"
#include "Result.h"
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainWind *MainWind;
__fastcall TMainWind::TMainWind(TComponent* Owner)
	: TForm(Owner)
{
}

void __fastcall TMainWind::ReadyClick(TObject *Sender)
{
	int fullNum;
	TStringList* list = new TStringList;
	if(Gender->ItemIndex == 0)
	{
		list->LoadFromFile("suitors.txt");
		int num=(list->Count)/14+1;
		fullNum = num;
	}
	else if(Gender->ItemIndex == 1)
	{
		list->LoadFromFile("brides.txt");
		int num=(list->Count)/14+1;
		fullNum = num;
	}
	TFileStream *questionnarieF = new TFileStream("temporaryQuestionnarie.txt", fmCreate);

	AnsiString strNum = IntToStr(fullNum);
	questionnarieF->Write(strNum.c_str(), strNum.Length());

	if(Gender->ItemIndex == 0)
	{
		AnsiString strGender = "\n"+IntToStr(1);
		questionnarieF->Write(strGender.c_str(), strGender.Length());
	}
	else if(Gender->ItemIndex == 1)
	{
		AnsiString strGender = "\n"+IntToStr(0);
		questionnarieF->Write(strGender.c_str(), strGender.Length());
	}

	AnsiString strPair = "\n"+IntToStr(1);
	questionnarieF->Write(strPair.c_str(), strPair.Length());

	AnsiString strName = "\n"+NameEdit->Text;
	questionnarieF->Write(strName.c_str(), strName.Length());

	AnsiString strAge = "\n"+AgeEdit->Text;
	questionnarieF->Write(strAge.c_str(), strAge.Length());

	AnsiString strGrowth = "\n"+GrowthEdit->Text;
	questionnarieF->Write(strGrowth.c_str(), strGrowth.Length());

	AnsiString strWeight = "\n"+WeightEdit->Text;
	questionnarieF->Write(strWeight.c_str(), strWeight.Length());

	AnsiString strHobby = "\n"+HobbyMemo->Text;
	questionnarieF->Write(strHobby.c_str(), strHobby.Length());

	delete	questionnarieF;
	delete list;
	ResultWind->ShowModal();
	MainWind->Close();
}

//---------------------------------------------------------------------------





void __fastcall TMainWind::LoadFromFileClick(TObject *Sender)
{
	if(Dialog->Execute())
	{
		HobbyMemo->Lines->LoadFromFile(Dialog->FileName);

		if(HobbyMemo->Lines->Strings[0] == "1")
			Gender->ItemIndex = 0;
		else
            Gender->ItemIndex = 1;
		HobbyMemo->Lines->Delete(0);

		NameEdit->Text = HobbyMemo->Lines->Strings[0];
		HobbyMemo->Lines->Delete(0);

		AgeEdit->Text = HobbyMemo->Lines->Strings[0];
		HobbyMemo->Lines->Delete(0);

		GrowthEdit->Text = HobbyMemo->Lines->Strings[0];
		HobbyMemo->Lines->Delete(0);

		WeightEdit->Text = HobbyMemo->Lines->Strings[0];
		HobbyMemo->Lines->Delete(0);
	}
	else {}
}
//---------------------------------------------------------------------------

