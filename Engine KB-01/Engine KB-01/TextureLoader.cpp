#include "TextureLoader.h"

TextureLoader::TextureLoader()
{
}

TextureLoader::~TextureLoader()
{
}

HRESULT TextureLoader::LoadTexture(std::string texturename, Renderer* DirectXRenderer)
{

	TextureWrapper* texture = new TextureWrapper(NULL);

	if (FAILED(DirectXRenderer->LoadTextureFromFile(texturename, 0, texture))) 
                {
                    MessageBox( NULL, L"Could not find texture map", L"Meshes.exe", MB_OK );
                }

	return S_OK;
}