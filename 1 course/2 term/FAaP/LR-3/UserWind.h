//---------------------------------------------------------------------------

#ifndef UserWindH
#define UserWindH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
//---------------------------------------------------------------------------
class TUserWin : public TForm
{
__published:	// IDE-managed Components
	TEdit *PointEdit;
	TEdit *TimeEdit;
	TMemo *ResultMemo;
	TButton *FindButton;
	TButton *ExitButton;
	TLabel *DateLable;
	TLabel *TimeLable;
	TLabel *PointLable;
	TLabel *ResultLable;
	TDateTimePicker *DateTime;
	void __fastcall ExitButtonClick(TObject *Sender);
	void __fastcall FindButtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TUserWin(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TUserWin *UserWin;
//---------------------------------------------------------------------------
#endif
