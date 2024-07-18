//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainFrame.h"
#include "PolskaZapis.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainWind *MainWind;
//---------------------------------------------------------------------------
__fastcall TMainWind::TMainWind(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TMainWind::OutputButtonClick(TObject *Sender)
{
	PolskaZapis zapis;
	zapis.note = InputEdit->Text;
	PolskaEdit->Text = zapis.convert();
    OutputEdit->Text = zapis.schet();
}
//---------------------------------------------------------------------------

