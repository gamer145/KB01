#ifndef SHADERLOADER_H
#define SHADERLOADER_H

#include <iostream>
#include <string>
#include <vector>
#include "Renderer.h"

/*
* Work in progress, doesn't work.
* Probably never will
* Ne pas toucher!
*/

class ShaderLoader
{
public:
	ShaderLoader();
	~ShaderLoader();
	HRESULT LoadShaderIn(std::string shadername, Renderer* DirectXRenderer);
private:
	std::vector<std::string> shaders;
};

#endif