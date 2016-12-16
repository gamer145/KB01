#ifndef ENGINETEXTHANDLING_H
#define ENGINETEXTHANDLING_H
#include <string>
#include <Windows.h>

namespace EngineTextHandling
{
	//Replaces characters in a string, used internally to fix some format issues. Returns a new formatted string.
	std::string ReplaceCharsInString(std::string strChange, char a, char b); 

	//Converts a HWND to a string, used for logging purposes. Basically just gets the title of a window
	std::string HwndToString(HWND hWnd);
};

#endif