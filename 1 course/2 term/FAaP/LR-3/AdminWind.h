//---------------------------------------------------------------------------

#ifndef AdminWindH
#define AdminWindH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
//---------------------------------------------------------------------------
class TAdminWin : public TForm
{
__published:	// IDE-managed Components
	TDateTimePicker *DateTime;
	TEdit *TimeEdit;
	TEdit *PlacesEdit;
	TEdit *PointEdit;
	TMemo *ResultMemo;
	TEdit *DeleteEdit;
	TButton *AddButton;
	TButton *ExitButton;
	TButton *DeleteButton;
	TLabel *PlacesLable;
	TLabel *ResultLable;
	TLabel *TimeLable;
	TLabel *DateLable;
	TLabel *PointLable;
	TLabel *DeleteLAble;
	TLabel *NumLabel;
	TEdit *NumEdit;
	void __fastcall ExitButtonClick(TObject *Sender);
	void __fastcall AddButtonClick(TObject *Sender);
	void __fastcall DeleteButtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TAdminWin(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAdminWin *AdminWin;
//---------------------------------------------------------------------------
#endif
