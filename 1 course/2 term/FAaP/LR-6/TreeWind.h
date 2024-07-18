//---------------------------------------------------------------------------

#ifndef TreeWindH
#define TreeWindH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Grids.hpp>
//---------------------------------------------------------------------------
class TTreeForm : public TForm
{
__published:	// IDE-managed Components
	TEdit *IndexEdit;
	TMemo *ResMemo;
	TEdit *DataEdit;
	TButton *AddButton;
	TButton *FindButton;
	TLabel *IndexLable;
	TLabel *DataLabel;
	TLabel *ResLable;
	TButton *DelButton;
	TButton *CleanButton;
	TButton *PreButton;
	TButton *PostButton;
	TButton *DeepButton;
	TStringGrid *SG;
	TLabel *ArrLable;
	TButton *AddArrButton;
	TButton *CleanArrButton;
	TButton *InButton;
	TTreeView *TreeView;
	TLabel *TreeLabel;
	void __fastcall DataEditChange(TObject *Sender);
	void __fastcall IndexEditChange(TObject *Sender);
	void __fastcall CleanButtonClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall CleanArrButtonClick(TObject *Sender);
	void __fastcall AddButtonClick(TObject *Sender);
	void __fastcall PreButtonClick(TObject *Sender);
	void __fastcall PostButtonClick(TObject *Sender);
	void __fastcall InButtonClick(TObject *Sender);
	void __fastcall FindButtonClick(TObject *Sender);
	void __fastcall DeepButtonClick(TObject *Sender);
	void __fastcall DelButtonClick(TObject *Sender);
	void __fastcall AddArrButtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TTreeForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTreeForm *TreeForm;
//---------------------------------------------------------------------------
#endif
