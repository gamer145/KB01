#include "MeshWrapper.h"

    MeshWrapper::MeshWrapper()
	{
		LPD3DXMESH _mesh = NULL;

		mesh = _mesh;
	};

	MeshWrapper::~MeshWrapper()
	{

	};

	void MeshWrapper::SetMesh(LPD3DXMESH _mesh)
	{
		mesh = _mesh;
	};

	LPD3DXMESH MeshWrapper::GetMesh()
	{
		return mesh;
	};



