#ifndef _MATERIALWRAPPER_H_
#define _MATERIALWRAPPER_H_

#include <d3dx9.h>

//Wrappers are used to make the rest of the engine not dependant on a specific framework, in this case directX.

	class MaterialWrapper
	{
	public:
		//Constructor
		MaterialWrapper(D3DMATERIAL9 _material);

		//Destructor
		~MaterialWrapper();

		//Sets the material that's contained within this class
		void SetMaterial(D3DMATERIAL9 _material);

		//Gets the material that's contained within this class
		D3DMATERIAL9 GetMaterial();
	private:
		//The directX material itself
		D3DMATERIAL9 material;
	};



#endif