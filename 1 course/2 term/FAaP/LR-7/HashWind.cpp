//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "HashWind.h"
#include "HashTable.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
THashForm *HashForm;
HashTable HT;
//---------------------------------------------------------------------------
__fastcall THashForm::THashForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall THashForm::AddButtonClick(TObject *Sender)
{
	HT.elem.data = StrToInt(DataEdit->Text);
	HT.toHashTable(HashTableMemo);
}
//---------------------------------------------------------------------------
void __fastcall THashForm::DelButtonClick(TObject *Sender)
{
	HT.elem.data = StrToInt(DataEdit->Text);
	HT.elem.toHash();
	HT.deleteElem(HashTableMemo, HT.hashTable[HT.elem.hash].GetSize());
}

void __fastcall THashForm::InputEditChange(TObject *Sender)
{
	if (InputEdit->Font->Color != clWindowText)
		InputEdit->Text = "";
	InputEdit->Font->Color = clWindowText;
	if (InputEdit->Text!="")
	{
		FindButton->Enabled = true;
		HashDelButton->Enabled = true;
	}
	else
	{
		FindButton->Enabled = false;
		HashDelButton->Enabled = false;
    }

}
//---------------------------------------------------------------------------

void __fastcall THashForm::FindButtonClick(TObject *Sender)
{
	HT.findElem(OutputEdit, StrToInt(InputEdit->Text));
}
//---------------------------------------------------------------------------

void __fastcall THashForm::DataEditChange(TObject *Sender)
{
	if (DataEdit->Text!="")
	{
		DelButton->Enabled = true;
		AddButton->Enabled = true;
	}
	else
	{
		DelButton->Enabled = false;
		AddButton->Enabled = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall THashForm::MinButtonClick(TObject *Sender)
{
    HT.minElem(MinEdit);
}
//---------------------------------------------------------------------------

void __fastcall THashForm::HashDelButtonClick(TObject *Sender)
{
	HT.elem.hash = StrToInt(InputEdit->Text);
	HT.delHashBranch(HashTableMemo);
}
//---------------------------------------------------------------------------

