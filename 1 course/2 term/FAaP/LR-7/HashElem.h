//---------------------------------------------------------------------------

#ifndef HashElemH
#define HashElemH
//---------------------------------------------------------------------------
#endif

class HashElem
{
	public:
	int hash;
	int data;

	void toHash()
	{
		hash = data%12;
	}
};