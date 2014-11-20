#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include <iostream>
#include <string>
#include "RendererInterface.h"
//#include "Resource_Manager.h"
#include "Texture.h"

class TextureLoader
{
public:
	TextureLoader();
	~TextureLoader();
	HRESULT LoadTexture(std::string texturename, RendererInterface* renderer);
};

#endif