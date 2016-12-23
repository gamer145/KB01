#include "ShaderLoader.h"

/*
* Work in progress, doesn't work.
* Probably never will
* Ne pas toucher!
*/

ShaderLoader::ShaderLoader()
{

}

ShaderLoader::~ShaderLoader()
{

}

HRESULT ShaderLoader::LoadShaderIn(std::string shadername, Renderer* DirectXRenderer)
{
	HRESULT result;

	if (std::find(shaders.begin(), shaders.end(), shadername) != shaders.end())
	{
		
		 // make this result = LoadShaderFromFile in DirectXRenderer
		
		if (FAILED(result))
		{
			// log error
		}
		else
		{
			shaders.push_back(shadername);
		}
	}
	else
	{
		//log "already exists"
		
	}

	return result;

}