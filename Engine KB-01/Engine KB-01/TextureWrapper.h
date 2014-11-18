#ifndef _TEXTUREWRAPPER_H_
#define _TEXTUREWRAPPER_H_

#include <d3dx9.h>



	class TextureWrapper
	{
	public:
		TextureWrapper(LPDIRECT3DTEXTURE9 _texture);
		~TextureWrapper();
		void SetTexture(LPDIRECT3DTEXTURE9 _texture);
		LPDIRECT3DTEXTURE9 GetTexture();
	private:
		LPDIRECT3DTEXTURE9 texture;
	};



#endif