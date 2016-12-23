#ifndef _MESHWRAPPER_H_
#define _MESHWRAPPER_H_

#include <d3dx9.h>

//Wrappers are used to make the rest of the engine not dependant on a specific framework, in this case directX.

	class MeshWrapper
	{
	public:
		//Constructor
		MeshWrapper();

		//Destructor
		~MeshWrapper();

		//Sets the Mesh that's contained within this class
		void SetMesh(LPD3DXMESH _mesh);

		//Gets the Mesh that's contained within this class
		LPD3DXMESH GetMesh();
	private:
		//The DirectX mesh itself
		LPD3DXMESH mesh;
	};


#endif