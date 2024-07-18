//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainWind.h"
#include "Bubbble.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMain *Main;
//---------------------------------------------------------------------------

Bubble bub;
List<int> deque;

__fastcall TMain::TMain(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TMain::NumEditChange(TObject *Sender)
{
	AddButton->Enabled = True;
}
//---------------------------------------------------------------------------

void __fastcall TMain::AddButtonClick(TObject *Sender)
{
	deque.PushBack(StrToInt(NumEdit->Text));
	DequeBox->Items->Add(deque[deque.GetSize()-1]);
	NumEdit->Clear();
	if (deque.GetSize()>=2)
		TailButton->Enabled=true;
	HeadButton->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TMain::DelButtonClick(TObject *Sender)
{
	if(deque.GetSize()!=1)
	{
		deque.PopFront();
		DequeBox->Items->Delete(0);
	}
	else
		ShowMessage("Удаление невозможно");
}
//---------------------------------------------------------------------------

void __fastcall TMain::BubleButtonClick(TObject *Sender)
{
	bub.bubbleSort(deque);
	DequeBox->Items->Clear();
	for(int i = 0; i < deque.GetSize(); i++)
		DequeBox->Items->Add(deque[i]);
}
//---------------------------------------------------------------------------

void __fastcall TMain::HeadButtonClick(TObject *Sender)
{
	TailHeadEbit->Text= IntToStr(bub.retHead(deque));
}
//---------------------------------------------------------------------------


void __fastcall TMain::TailButtonClick(TObject *Sender)
{
	TailHeadEbit->Text= IntToStr(bub.retTail(deque));
}
//---------------------------------------------------------------------------

void __fastcall TMain::EmptyButtonClick(TObject *Sender)
{
	if (bub.IsEmpty(deque) == 1)
		EmptyEdit->Text="Пустой";
	else
		EmptyEdit->Text="Не пустой";
}
//---------------------------------------------------------------------------

