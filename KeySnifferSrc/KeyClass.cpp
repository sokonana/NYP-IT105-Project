#include "KeyClass.h"
#include <sstream>

bool KeyClass::Validate()
{
	bool results = true;
	const char expected[] = ".tie5Roanl";

	// check that all the character sequence is correct
	// last key stroke for carriage return is not counted into total_presses
	try
	{
		// Total character count must be 10
		if (total_presses != 10)
			throw(false);

		// Make sure all char pressed can match to expected string
		if (strncmp(expected, keypressed, 10) != 0)
			throw(false);
		
	}
	catch (bool check)
	{
		results = check;
	}
	
	return results;
}

double KeyClass::GetHoldInterval(int index)
{
	if (index <= total_presses)
	{
		return (double) (keyup[index] - keydown[index]);
	}
	
	return 0.0;
}

double KeyClass::GetTransferInterval(int index)
{
	if (index < total_presses)
	{
		return (double) (keydown[index+1] - keyup[index]);
	}
	

	return 0.0;
}

std::string KeyClass::ToString()
{
	std::stringstream OutStream;
	std::string OutStr;

	for (int col=0; col <= total_presses; col++)
	{
		if (col != total_presses)
		{
			OutStream << "," << GetHoldInterval(col) << "," << GetTransferInterval(col);
		}
		else  // last key - carriage return
		{
			OutStream << "," << GetHoldInterval(col);
		}
		
	}
	OutStream << std::endl;

	std::getline(OutStream, OutStr);

	return OutStr;
}