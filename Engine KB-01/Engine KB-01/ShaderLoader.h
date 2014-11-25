#ifndef SHADERLOADER_H
#define SHADERLOADER_H

#include <iostream>
#include <string>
#include <vector>
#include "RendererInterface.h"


class ShaderLoader
{
public:
	ShaderLoader();
	~ShaderLoader();
	HRESULT LoadShaderIn(std::string shadername, RendererInterface* renderer);
private:
	std::vector<std::string> shaders;
};

#endif