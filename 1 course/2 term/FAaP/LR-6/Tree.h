//---------------------------------------------------------------------------
#include <vcl.h>
#ifndef TreeH
#define TreeH
//---------------------------------------------------------------------------
#endif

class BinaryNode
{
	public:
		unsigned int height;
		int text;
		String data;
		int deep = 0;
		BinaryNode* left_child = nullptr;
		BinaryNode* right_child = nullptr;
		void TraversePreorder(TMemo *Memo);
		void TraverseInorder(TMemo *Memo);
		void TraversePostorder(TMemo *Memo);
		static BinaryNode* SearchNode(String text);
		static BinaryNode* DeleteNode(BinaryNode* root, int text);
		BinaryNode* Balance();
		void FindDeep(BinaryNode* head);
		void ViewTree(BinaryNode *t, int kl, TTreeView *TreeView1);
		BinaryNode* AddNode(BinaryNode* node);
		BinaryNode* deleteMinNode(BinaryNode* ptr);
		BinaryNode* Delete(BinaryNode* ptr, int key);
		BinaryNode* SearchNode(int text);
		BinaryNode* findMinNode(BinaryNode * ptr);

		BinaryNode* RotateRight()
		{
		  BinaryNode* p = this;
		  BinaryNode* q = p->left_child;
		  p->left_child = q->right_child;
		  q->right_child = p;

		  p->UpdateHeight();
		  q->UpdateHeight();

		  return q;
		}

		BinaryNode* RotateLeft()
		{
		  BinaryNode* q = this;
		  BinaryNode* p = q->right_child;
		  q->right_child = p->left_child;
		  p->left_child = q;

		  q->UpdateHeight();
		  p->UpdateHeight();

		  return p;
		}

		int GetBFactor()
		{
		  unsigned int hleft = Heigh(this->left_child);
		  unsigned int hright = Heigh(this->right_child);
		  return hright - hleft;
		}

		int Heigh(BinaryNode * ptr)
		{
			if (ptr != nullptr)
				return ptr->height;
			else return 0;
		}

		void UpdateHeight()
		{
		  unsigned int hleft = Heigh(this->left_child);
		  unsigned int hright = Heigh(this->right_child);
		  height = (hleft > hright ? hleft : hright) + 1;
		}
};

void BinaryNode::TraversePreorder(TMemo *Memo)
{
	Memo->Lines->Add(this->text);

	if (this->left_child)
		this->left_child->TraversePreorder(Memo);

	if (this->right_child)
		this->right_child->TraversePreorder(Memo);
}

void BinaryNode::TraverseInorder(TMemo *Memo)
{
	if (this->left_child)
		this->left_child->TraverseInorder(Memo);

	Memo->Lines->Add(this->text);

	if (this->right_child)
		this->right_child->TraverseInorder(Memo);
}

void BinaryNode::TraversePostorder(TMemo *Memo)
{
	if (this->left_child)
		this->left_child->TraversePostorder(Memo);

	if (this->right_child)
		this->right_child->TraversePostorder(Memo);

	Memo->Lines->Add(this->text);
}

BinaryNode* BinaryNode::SearchNode(int text)
{
	if (this->text == text)
		return this;

	if (this->text > text)
		if (this->left_child)
			return this->left_child->SearchNode(text);
		else
			return nullptr;
	else
		return this->right_child
			? this->right_child->SearchNode(text)
			: nullptr;
}

BinaryNode* BinaryNode::Delete(BinaryNode* ptr, int key)
{
	if(ptr == nullptr)
	return nullptr;

	if(key < ptr->text)
	ptr->left_child = Delete(ptr->left_child,key);
	else if(key > ptr->text)
	ptr->right_child = Delete(ptr->right_child,key);
	else //  k == p->key
	{
		BinaryNode* cur   = ptr->left_child;
		BinaryNode* cur_2 = ptr->right_child;
		delete ptr;

		if(!cur_2)
			return cur_2;

		BinaryNode* minimum = findMinNode(cur_2);
		minimum->right_child = deleteMinNode(cur_2);
		minimum->left_child = cur;
		return minimum->Balance();
	}
	return ptr->Balance();
}

BinaryNode* BinaryNode::findMinNode(BinaryNode * ptr)
{
	if (ptr->left_child == nullptr)
	return ptr;
	else findMinNode(ptr->left_child);
}

BinaryNode* BinaryNode::deleteMinNode(BinaryNode * ptr)
{
	if (ptr->left_child == nullptr)
	return ptr->right_child;
	ptr->left_child = deleteMinNode(ptr->left_child);
	return ptr->Balance();
}

BinaryNode* BinaryNode::Balance()
{
	  this->UpdateHeight();
	  if( GetBFactor() == 2 )
	  {
		if( this->right_child->GetBFactor() < 0 )
		  this->right_child = this->right_child->RotateRight();
		return this->RotateLeft();
	  }

	  if( GetBFactor() == -2 )
	  {
		if( this->left_child->GetBFactor() > 0 )
		  this->left_child = this->left_child->RotateLeft();
		return this->RotateRight();
	  }
  return this;
}

BinaryNode* BinaryNode::AddNode(BinaryNode* node)
{
	if (node->text < this->text)
	{
		if (!this->left_child)
			this->left_child = node = node -> Balance();
		else
			this -> left_child = this->left_child->AddNode(node);
	}

	else if (node->text > this->text)
	{
		if (!this->right_child)
			this->right_child = node = node -> Balance();
		else
			this -> right_child = this->right_child->AddNode(node);
	}

	return this->Balance();
}

void BinaryNode::FindDeep(BinaryNode* head)
{
	if (this->left_child)
		this->left_child->FindDeep(head);

	if (this->right_child)
		this->right_child->FindDeep(head);

	if (this->left_child==nullptr && this->right_child==nullptr)
	{
		int tempDeep = 0;
		BinaryNode* current = head;
		while(current->text != this->text)
		{
			if (current->text > this->text)
			{
				current = current->left_child;
				tempDeep++;
			}
			else
			{
				current = current->right_child;
				tempDeep++;
			}

			if(head->deep < tempDeep)
				head->deep = tempDeep;
		}
	}
}

void BinaryNode::ViewTree(BinaryNode *t, int kl, TTreeView *TreeView1)
{
	if (t == NULL)
		return;
	if (kl == -1)
		TreeView1->Items->AddFirst(NULL, IntToStr(t->text));
	else
		TreeView1->Items->AddChildFirst(TreeView1->Items->Item[kl], IntToStr(t->text));
	kl++;
	ViewTree(t->left_child, kl, TreeView1);
	ViewTree(t->right_child, kl, TreeView1);

	kl--;
}
