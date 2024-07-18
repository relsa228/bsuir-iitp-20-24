//---------------------------------------------------------------------------

#ifndef QuestionnarieH
#define QuestionnarieH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtDlgs.hpp>
//---------------------------------------------------------------------------
class TMainWind : public TForm
{
__published:	// IDE-managed Components
	TLabel *FullName;
	TLabel *Age;
	TLabel *Growth;
	TLabel *Hobby;
	TLabel *Weight;
	TButton *Ready;
	TEdit *NameEdit;
	TEdit *AgeEdit;
	TEdit *GrowthEdit;
	TEdit *WeightEdit;
	TRadioGroup *Gender;
	TMemo *HobbyMemo;
	TLabel *GenderLabel;
	TOpenTextFileDialog *Dialog;
	TButton *LoadFromFile;
	void __fastcall ReadyClick(TObject *Sender);
	void __fastcall LoadFromFileClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TMainWind(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainWind *MainWind;
//---------------------------------------------------------------------------
#endif
