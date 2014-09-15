#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include <iostream>
#include <string>
#include "Renderer.h"
//#include "Resource_Manager.h"
#include "Texture.h"

class TextureLoader
{
public:
	TextureLoader();
	~TextureLoader();
	HRESULT LoadTexture(std::string texturename, Renderer* renderer);
};

#endif