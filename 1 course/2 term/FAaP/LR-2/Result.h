//---------------------------------------------------------------------------

#ifndef ResultH
#define ResultH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class TResultWind : public TForm
{
__published:	// IDE-managed Components
	TLabel *Age;
	TLabel *Growth;
	TLabel *Weight;
	TLabel *Result;
	TLabel *FromWeight;
	TLabel *ToAge;
	TLabel *FromAge;
	TLabel *ToGrowth;
	TLabel *FromGrowth;
	TLabel *ToWeight;
	TLabel *Num;
	TButton *FindResult;
	TButton *Choice;
	TEdit *FromAgeEdit;
	TEdit *ToWeightEdit;
	TEdit *ToGrowthEdit;
	TEdit *ToAgeEdit;
	TEdit *FromGrowthEdit;
	TEdit *FromWeightEdit;
	TEdit *ChoiceEdit;
	TEdit *Edit1;
	TMemo *ResultMemo;
	TButton *SaveQuest;
	TMemo *ViewMemo;
	void __fastcall FindResultClick(TObject *Sender);
	void __fastcall SaveQuestClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall ChoiceClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TResultWind(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TResultWind *ResultWind;
//---------------------------------------------------------------------------
#endif
