#include "Texture.h"


Texture::Texture(void)
{
}


Texture::~Texture(void)
{
}

std::string Texture::getTextureName()
{
	return TextureName;
}
void* Texture::getActualTexture()
{
	return ActualTexture;
}

void Texture::setTextureName(std::string newName)
{
	TextureName = newName;
}

void Texture::setActualTexture(void* newText)
{
	ActualTexture = newText;
}
