#include "MeshWrapper.h"

	/**
	* Function: MeshWrapper::MeshWrapper()
	* Description: constructor
	*/
    MeshWrapper::MeshWrapper()
	{
		LPD3DXMESH _mesh = NULL;

		mesh = _mesh;
	};

	/**
	* Function: MeshWrapper::~MeshWrapper()
	* Description: Destructor
	*/
	MeshWrapper::~MeshWrapper()
	{
		if (mesh != NULL) {
			delete mesh;
		}
		
	};

	/**
	* Function: MeshWrapper::SetMesh(LPD3DXMESH _mesh)
	* Description: Sets the Mesh that's contained within this class
	*/
	void MeshWrapper::SetMesh(LPD3DXMESH _mesh)
	{
		mesh = _mesh;
	};

	/**
	* Function: MeshWrapper::GetMesh()
	* Description: Gets the Mesh that's contained within this class
	*/
	LPD3DXMESH MeshWrapper::GetMesh()
	{
		return mesh;
	};



