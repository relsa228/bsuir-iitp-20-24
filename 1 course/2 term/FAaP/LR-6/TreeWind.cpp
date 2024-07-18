//---------------------------------------------------------------------------

#include <vcl.h>
#include "Tree.h"
#pragma hdrstop

#include "TreeWind.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TTreeForm *TreeForm;
BinaryNode* head;
int TreeSize = 0;
//---------------------------------------------------------------------------
__fastcall TTreeForm::TTreeForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------


void __fastcall TTreeForm::DataEditChange(TObject *Sender)
{
	if(DataEdit->Text!="" && IndexEdit->Text!="")
		AddButton->Enabled = true;
	else
		AddButton->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TTreeForm::IndexEditChange(TObject *Sender)
{
	if(DataEdit->Text!="" && IndexEdit->Text!="")
		AddButton->Enabled = true;
	else
		AddButton->Enabled = false;

	if(IndexEdit->Text!="")
	{
		FindButton->Enabled = true;
		DelButton->Enabled = true;
	}
	else
	{
		FindButton->Enabled = false;
		DelButton->Enabled = false;
	}
}
//---------------------------------------------------------------------------


void __fastcall TTreeForm::CleanButtonClick(TObject *Sender)
{
	ResMemo->Clear();
}
//---------------------------------------------------------------------------
void __fastcall TTreeForm::FormCreate(TObject *Sender)
{
	SG->Cells[0][0] = "Индексы";
	SG->Cells[1][0] = "Данные";
}
//---------------------------------------------------------------------------

void __fastcall TTreeForm::CleanArrButtonClick(TObject *Sender)
{
	for(int i = 1; i < 7; i++)
		for(int j = 0; j<2;j++)
			SG->Cells[j][i] = "";
}
//---------------------------------------------------------------------------



void __fastcall TTreeForm::AddButtonClick(TObject *Sender)
{
	BinaryNode* node = new BinaryNode;
	node->text = StrToInt(IndexEdit->Text);
	node->data = DataEdit->Text;

	if (TreeSize == 0)
	{
		head = node;
		TreeSize++;
	}
	else
	{
		BinaryNode* temp = head->AddNode(node);
		if (temp!=nullptr)
			head=head->AddNode(node);
		TreeSize++;
	}

	TreeView->Items->Clear();
	head->ViewTree(head, -1, TreeView);
}
//---------------------------------------------------------------------------

void __fastcall TTreeForm::PreButtonClick(TObject *Sender)
{
    ResMemo->Clear();
    head->TraversePreorder(ResMemo);
}
//---------------------------------------------------------------------------

void __fastcall TTreeForm::PostButtonClick(TObject *Sender)
{
	ResMemo->Clear();
    head->TraversePostorder(ResMemo);
}
//---------------------------------------------------------------------------

void __fastcall TTreeForm::InButtonClick(TObject *Sender)
{
	ResMemo->Clear();
	head->TraverseInorder(ResMemo);
}
//---------------------------------------------------------------------------

void __fastcall TTreeForm::FindButtonClick(TObject *Sender)
{
	BinaryNode* res = head->SearchNode(StrToInt(IndexEdit->Text));
	ResMemo->Text = res->data;
}
//---------------------------------------------------------------------------



void __fastcall TTreeForm::DeepButtonClick(TObject *Sender)
{
	head->FindDeep(head);
	ResMemo->Text=("Максимальная глубина: " + IntToStr(head->deep));
}
//---------------------------------------------------------------------------

void __fastcall TTreeForm::DelButtonClick(TObject *Sender)
{
	head = head->Delete(head, StrToInt(IndexEdit->Text));
	TreeView->Items->Clear();
	head->ViewTree(head, -1, TreeView);
}
//---------------------------------------------------------------------------

void __fastcall TTreeForm::AddArrButtonClick(TObject *Sender)
{
	for (int i = 1; i < 7; i++)
	{
		if(SG->Cells[0][i]!="")
		{
			BinaryNode* node = new BinaryNode;
			node->text = StrToInt(SG->Cells[0][i]);
			if (SG->Cells[1][i]!="")
				node->data = SG->Cells[1][i];
			else
				node->data = "empty";

			if (TreeSize == 0)
			{
				head = node;
				TreeSize++;
			}
			else
			{
				head=head->AddNode(node);
				TreeSize++;
			}
		}
	}

	TreeView->Items->Clear();
	head->ViewTree(head, -1, TreeView);
}
//---------------------------------------------------------------------------

