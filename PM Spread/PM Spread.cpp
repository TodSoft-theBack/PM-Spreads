#include <Windows.h>
#include "Form.h"

int main()
{
	Form* form1 = new Form();
	bool isRunning = true;
	while (isRunning)
	{
		if (!form1->ProcessMessages())
			isRunning = false;
	}
	delete form1;
	return 0;
}