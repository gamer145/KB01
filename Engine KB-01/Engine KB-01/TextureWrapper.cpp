
#include "TextureWrapper.h"

	/**
	* TextureWrapper::TextureWrapper(LPDIRECT3DTEXTURE9 _texture)
	* Description: Constructor
	*/
	TextureWrapper::TextureWrapper(LPDIRECT3DTEXTURE9 _texture)
	{
		texture = _texture;
	};


	/**
	* Function: TextureWrapper::~TextureWrapper()
	* Description: Destructor
	*/
	TextureWrapper::~TextureWrapper()
	{
		if (texture != NULL) {
			delete texture;
		}
		
	};


	/**
	* Function: TextureWrapper::SetTexture(LPDIRECT3DTEXTURE9 _texture)
	* Description: Sets the texture that's contained within this class
	*/
	void TextureWrapper::SetTexture(LPDIRECT3DTEXTURE9 _texture)
	{
		texture = _texture;
	};


	/**
	* Function: TextureWrapper::GetTexture()
	* Description: Gets the texture that's contained within this class
	*/
	LPDIRECT3DTEXTURE9 TextureWrapper::GetTexture()
	{
		return texture;
	};

