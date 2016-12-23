#include "EngineTextHandling.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>


/**
* Function:	EngineTextHandling::ReplaceCharsInString()
* Description: Reads through the provided string, and replaces char A with char B
* Used to filter out stuff that we don't want when writing to files and such
*/
std::string EngineTextHandling::ReplaceCharsInString(std::string strChange, char a, char b)
{
	for (int i = 0; i < strChange.length(); ++i)
	{
		if (strChange[i] == a)
			strChange[i] = b;
	}

	return strChange;
}

/**
* Function:	EngineTextHandling::HwndToString()
* Description: Converts the HWND to a string format
* Used to log Window Titles
*/
std::string EngineTextHandling::HwndToString(HWND hWnd)
{
	std::wstring HWNDWideString;	
	int nLength = GetWindowTextLength(hWnd);

	HWNDWideString.resize(nLength);

	GetWindowText(hWnd, &HWNDWideString[0], nLength + 1);

	std::string HWNDFormattedString(HWNDWideString.begin(), HWNDWideString.end());

	return HWNDFormattedString;
}
