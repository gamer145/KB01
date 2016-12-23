#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include <iostream>
#include <string>
#include "Renderer.h"
#include "Texture.h"

class TextureLoader
{
public:
	//Constructor
	TextureLoader();

	//Destructor
	~TextureLoader();

	//Loads a texture into memory and graphs it.
	HRESULT LoadTexture(std::string texturename, Renderer* DirectXRenderer); 
};

#endif