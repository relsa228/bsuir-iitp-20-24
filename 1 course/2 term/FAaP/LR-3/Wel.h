//---------------------------------------------------------------------------

#ifndef WelH
#define WelH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
//---------------------------------------------------------------------------
class TWelWind : public TForm
{
__published:	// IDE-managed Components
	TButton *User;
	TButton *Admin;
	TLabel *NameLabel;
	TLabel *NameLabelCont;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall UserClick(TObject *Sender);
	void __fastcall AdminClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TWelWind(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TWelWind *WelWind;
//---------------------------------------------------------------------------
#endif
