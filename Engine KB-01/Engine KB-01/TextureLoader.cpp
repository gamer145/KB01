#include "TextureLoader.h"

TextureLoader::TextureLoader()
{
}

TextureLoader::~TextureLoader()
{
}


/**
* Function:	TextureLoader::LoadTexture(std::string texturename, Renderer* DirectXRenderer)
* Description:	Loads a texture into memory and graphs it.
*/
HRESULT TextureLoader::LoadTexture(std::string texturename, Renderer* DirectXRenderer)
{

	TextureWrapper* texture = new TextureWrapper(NULL);

	if (FAILED(DirectXRenderer->LoadTextureFromFile(texturename, 0, texture))) 
                {
                    MessageBox( NULL, L"Could not find texture map", L"Meshes.exe", MB_OK );
                }

	return S_OK;
}