#ifndef ENGINETEXTHANDLING_H
#define ENGINETEXTHANDLING_H
#include <string>

namespace EngineTextHandling
{
	std::string ReplaceCharsInString(std::string strChange, char a, char b); //Replaces characters in a string, used internally to fix some format issues. Returns a new formatted string.
};

#endif