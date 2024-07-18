//---------------------------------------------------------------------------

#ifndef IncorrectTimeH
#define IncorrectTimeH

#include <vcl.h>

class IncorrectTime : public Exception
{
	public:
	String error;

	IncorrectTime(const String &error) : Exception(error)
	{
		this->error = error ;
	}

	void  what()
	{
		ShowMessage(error);
	}
};
#endif
