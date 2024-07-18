//---------------------------------------------------------------------------

#ifndef HashWindH
#define HashWindH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class THashForm : public TForm
{
__published:	// IDE-managed Components
	TMemo *HashTableMemo;
	TEdit *DataEdit;
	TButton *AddButton;
	TLabel *HashLabel;
	TLabel *AddLabel;
	TLabel *MinLabel;
	TButton *DelButton;
	TEdit *OutputEdit;
	TEdit *InputEdit;
	TButton *FindButton;
	TEdit *MinEdit;
	TLabel *FindLabel;
	TButton *MinButton;
	TButton *HashDelButton;
	void __fastcall AddButtonClick(TObject *Sender);
	void __fastcall DelButtonClick(TObject *Sender);
	void __fastcall InputEditChange(TObject *Sender);
	void __fastcall FindButtonClick(TObject *Sender);
	void __fastcall DataEditChange(TObject *Sender);
	void __fastcall MinButtonClick(TObject *Sender);
	void __fastcall HashDelButtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall THashForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE THashForm *HashForm;
//---------------------------------------------------------------------------
#endif
