//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Wel.h"
#include "UserWind.h"
#include "AdminWind.h"
#include "Train.h"
#include "List.h"
#include "IncorrectTime.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TUserWin *UserWin;
extern List<Train> trains;
//---------------------------------------------------------------------------
__fastcall TUserWin::TUserWin(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TUserWin::ExitButtonClick(TObject *Sender)
{
	UserWin->Close();
}
//---------------------------------------------------------------------------
void __fastcall TUserWin::FindButtonClick(TObject *Sender)
{
    ResultMemo->Clear();
	try
	{
		float time = StrToFloat(TimeEdit -> Text), a, prov, check = 0.599999999;
		prov = modf(time, &a);
		if (a > 24)
			throw IncorrectTime("Введенное время невърно. Помъняйте запись согласно общему формату.");
		else if (prov > check)
			throw IncorrectTime("Введенное время невърно. Помъняйте запись согласно общему формату.");
		int smotr = 0;
		for(int i = 0; i < trains.GetSize(); i++)
		{
			if(trains[i].time >= StrToFloat(TimeEdit -> Text))
				if(trains[i].date == DateTime->Date)
					if(trains[i].finPoint == PointEdit -> Text)
						if(trains[i].places != 0)
						{
							Train::showTrain(trains[i], ResultMemo);
							smotr++;
						}
		}
		if (smotr==0)
			ShowMessage("Рейса не найдено. Повторите запросъ позже.");
	}
	catch(IncorrectTime &e)
	{
		e.what();
	}
}
