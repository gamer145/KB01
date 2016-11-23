#include "EngineTextHandling.h"
#include <fstream>
#include <iostream>
#include <sstream>


std::string EngineTextHandling::ReplaceCharsInString(std::string strChange, char a, char b)
{
	for (int i = 0; i < strChange.length(); ++i)
	{
		if (strChange[i] == a)
			strChange[i] = b;
	}

	return strChange;
}
