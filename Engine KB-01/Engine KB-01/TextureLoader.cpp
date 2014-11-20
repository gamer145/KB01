#include "TextureLoader.h"

TextureLoader::TextureLoader()
{
}

TextureLoader::~TextureLoader()
{
}

HRESULT TextureLoader::LoadTexture(std::string texturename, RendererInterface* renderer)
{

	TextureWrapper* texture = new TextureWrapper(NULL);

	if (FAILED(renderer->LoadTextureFromFile(texturename, 272, texture))) 
                {
                    MessageBox( NULL, L"Could not find texture map", L"Meshes.exe", MB_OK );
                }
	renderer->addTexture(texturename, texture);
	return S_OK;
}