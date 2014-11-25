#ifndef SHADERLOADER_H
#define SHADERLOADER_H

#include <iostream>
#include <string>
#include <vector>
#include "Renderer.h"


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