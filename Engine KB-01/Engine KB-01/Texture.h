#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <d3d9.h>
#include <d3dx9.h>


class Texture
{
public:
	Texture();
	~Texture();

	std::string getTextureName();
	void* getActualTexture();

	void setTextureName(std::string newName);
	void setActualTexture(void* newText);
private:
	std::string TextureName;
	void* ActualTexture;

	
};

#endif // TEXTURE_H //

