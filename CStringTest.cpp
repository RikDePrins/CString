#include "CString.h"	// raptor::GetIntFromCString
#include <iostream>		// std::cerr, std::cout

int main()
{
	bool isAnInt = true;
	bool isOutOfRange = false;
	const int num{ raptor::GetIntFromCString("65536", isAnInt, isOutOfRange) };

	if (!isAnInt)
	{
		std::cerr << "Unable to convert contents of c-string to int\n";
		return 1;
	}

	if (isOutOfRange)
	{
		std::cerr << "Number inside c-string out of int range\n";
		return 2;
	}

	std::cout << num << '\n';	// 65536

	return 0;
}