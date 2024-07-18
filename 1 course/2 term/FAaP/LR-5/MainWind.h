//---------------------------------------------------------------------------

#ifndef MainWindH
#define MainWindH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class TMain : public TForm
{
__published:	// IDE-managed Components
	TListBox *DequeBox;
	TLabel *DequeLable;
	TEdit *NumEdit;
	TLabel *AddEdit;
	TButton *AddButton;
	TButton *BubleButton;
	TButton *DelButton;
	TEdit *TailHeadEbit;
	TButton *HeadButton;
	TButton *TailButton;
	TLabel *OutputLabel;
	TLabel *EmptyLable;
	TEdit *EmptyEdit;
	TButton *EmptyButton;
	void __fastcall NumEditChange(TObject *Sender);
	void __fastcall AddButtonClick(TObject *Sender);
	void __fastcall DelButtonClick(TObject *Sender);
	void __fastcall BubleButtonClick(TObject *Sender);
	void __fastcall HeadButtonClick(TObject *Sender);
	void __fastcall TailButtonClick(TObject *Sender);
	void __fastcall EmptyButtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMain *Main;
//---------------------------------------------------------------------------
#endif
