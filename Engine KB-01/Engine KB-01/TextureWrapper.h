#ifndef _TEXTUREWRAPPER_H_
#define _TEXTUREWRAPPER_H_

#include <d3dx9.h>

//Wrappers are used to make the rest of the engine not dependant on a specific framework, in this case directX.

	class TextureWrapper
	{
	public:
		//Constructor
		TextureWrapper(LPDIRECT3DTEXTURE9 _texture);

		//Destructor
		~TextureWrapper();

		//Sets the texture that's contained within this class
		void SetTexture(LPDIRECT3DTEXTURE9 _texture);

		//Gets the texture that's contained within this class
		LPDIRECT3DTEXTURE9 GetTexture();
	private:
		//The directX texture itself
		LPDIRECT3DTEXTURE9 texture;
	};



#endif