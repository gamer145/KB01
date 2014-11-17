#include "TextureLoader.h"

TextureLoader::TextureLoader()
{
}

TextureLoader::~TextureLoader()
{
}

HRESULT TextureLoader::LoadTexture(std::string texturename, Renderer* renderer)
{
	//Texture* text = new Texture;
	//text->setTextureName(texturename);
	std::string textLocation = "..\\Models\\" + texturename;
	LPDIRECT3DTEXTURE9 TheTexture = NULL;
	LPSTR textureLPSTR = const_cast<CHAR*>(textLocation.c_str());
	/*
	const CHAR* strPrefix = "..\\Models\\";
                CHAR strTexture[MAX_PATH];
                strcpy_s( strTexture, MAX_PATH, strPrefix );
                strcat_s( strTexture, MAX_PATH, texturename );
				*/

	if( FAILED( D3DXCreateTextureFromFileA( ((LPDIRECT3DDEVICE9)renderer->get3DDevice()),
                                                    textureLPSTR,
                                                    &TheTexture ) ) )
                {
                    MessageBox( NULL, L"Could not find texture map", L"Meshes.exe", MB_OK );
                }
	TextureWrapper* TheNewTexture = new TextureWrapper(TheTexture);
	renderer->addTexture(texturename, TheNewTexture);
	return S_OK;
}