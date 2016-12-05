#include "EngineTextHandling.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>



std::string EngineTextHandling::ReplaceCharsInString(std::string strChange, char a, char b)
{
	for (int i = 0; i < strChange.length(); ++i)
	{
		if (strChange[i] == a)
			strChange[i] = b;
	}

	return strChange;
}

std::string EngineTextHandling::HwndToString(HWND hWnd)
{
	std::wstring HWNDWideString;	
	int nLength = GetWindowTextLength(hWnd);

	HWNDWideString.resize(nLength);

	GetWindowText(hWnd, &HWNDWideString[0], nLength + 1);

	std::string HWNDFormattedString(HWNDWideString.begin(), HWNDWideString.end());

	return HWNDFormattedString;
}
