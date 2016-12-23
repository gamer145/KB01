#ifndef _MATERIALWRAPPER_H_
#define _MATERIALWRAPPER_H_

#include <d3dx9.h>


	class MaterialWrapper
	{
	public:
		MaterialWrapper(D3DMATERIAL9 _material);
		~MaterialWrapper();
		//sets the material that's contained within this class
		void SetMaterial(D3DMATERIAL9 _material);
		//gets the material that's contained within this class
		D3DMATERIAL9 GetMaterial();
	private:
		D3DMATERIAL9 material;
	};



#endif