//---------------------------------------------------------------------------

#ifndef MainFrameH
#define MainFrameH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class TMainWind : public TForm
{
__published:	// IDE-managed Components
	TEdit *OutputEdit;
	TEdit *PolskaEdit;
	TEdit *InputEdit;
	TButton *OutputButton;
	TLabel *OutputLable;
	TLabel *PolskaLable;
	TLabel *InputLable;
	void __fastcall OutputButtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TMainWind(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainWind *MainWind;
//---------------------------------------------------------------------------
#endif
