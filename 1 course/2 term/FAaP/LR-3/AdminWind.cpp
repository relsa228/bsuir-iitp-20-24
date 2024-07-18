//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "AdminWind.h"
#include "List.h"
#include "Train.h"
#include "IncorrectTime.h"
#include <math.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAdminWin *AdminWin;
List<Train> trains;
//---------------------------------------------------------------------------
__fastcall TAdminWin::TAdminWin(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TAdminWin::ExitButtonClick(TObject *Sender)
{
		AdminWin->Close();
}
//---------------------------------------------------------------------------
void __fastcall TAdminWin::AddButtonClick(TObject *Sender)
{
	Train train;
	try{
		int i = 0;
		float a, check = 0.59999999, prov;
		train.num = StrToInt(NumEdit -> Text);
		train.date = DateTime -> Date;
		train.time = StrToFloat(TimeEdit -> Text);
		prov = modf(train.time, &a);
		if (a > 24)
			throw IncorrectTime("Введенное время невърно. Помъняйте запись согласно общему формату.");
		else if (prov > check)
			throw IncorrectTime("Введенное время невърно. Помъняйте запись согласно общему формату.");
		train.finPoint = PointEdit -> Text;
		train.places = StrToInt(PlacesEdit -> Text);
		Train::showTrain(train, ResultMemo);
		trains.PushBack(train);
	}
	catch(IncorrectTime &e)
	{
		e.what();
	}
}
//---------------------------------------------------------------------------

void __fastcall TAdminWin::DeleteButtonClick(TObject *Sender)
{
	int del = StrToInt(DeleteEdit -> Text);
	for(int i = 0; i < trains.GetSize(); i++)
	{
		if (trains[i].num == del) {
			trains.DeleteElem(i);
		}
	}
	ResultMemo->Lines->Clear();
    for(int i = 0; i < trains.GetSize(); i++)
	{
		Train::showTrain(trains[i], ResultMemo);
	}
}
//---------------------------------------------------------------------------

