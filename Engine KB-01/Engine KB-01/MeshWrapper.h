#ifndef _MESHWRAPPER_H_
#define _MESHWRAPPER_H_

#include <d3dx9.h>


	class MeshWrapper
	{
	public:
		MeshWrapper();
		~MeshWrapper();
		//sets the Mesh that's contained within this class
		void SetMesh(LPD3DXMESH _mesh);
		//gets the Mesh that's contained within this class
		LPD3DXMESH GetMesh();
	private:
		LPD3DXMESH mesh;
	};


#endif