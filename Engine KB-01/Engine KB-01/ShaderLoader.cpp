#include "ShaderLoader.h"

ShaderLoader::ShaderLoader()
{

}

ShaderLoader::~ShaderLoader()
{

}

HRESULT ShaderLoader::LoadShaderIn(std::string shadername, RendererInterface* renderer)
{
	HRESULT result;

	if (std::find(shaders.begin(), shaders.end(), shadername) != shaders.end())
	{
		
		 // make this result = LoadShaderFromFile in renderer
		
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