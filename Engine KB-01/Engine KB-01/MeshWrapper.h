#ifndef _MESHWRAPPER_H_
#define _MESHWRAPPER_H_

#include <d3dx9.h>


	class MeshWrapper
	{
	public:
		MeshWrapper();
		~MeshWrapper();
		void SetMesh(LPD3DXMESH _mesh);
		LPD3DXMESH GetMesh();
	private:
		LPD3DXMESH mesh;
	};


#endif