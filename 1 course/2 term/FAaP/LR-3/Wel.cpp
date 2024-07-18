//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Wel.h"
#include "UserWind.h"
#include "AdminWind.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TWelWind *WelWind;
//---------------------------------------------------------------------------
__fastcall TWelWind::TWelWind(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TWelWind::Button1Click(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------
void __fastcall TWelWind::UserClick(TObject *Sender)
{
	UserWin->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TWelWind::AdminClick(TObject *Sender)
{
	AdminWin->ShowModal();
}
//---------------------------------------------------------------------------

