#include "ModelLoader.h"

ModelLoader::ModelLoader()
{
}

ModelLoader::~ModelLoader()
{
}

HRESULT ModelLoader::LoadModel(std::string modelname, Renderer* renderer, VisualObject* object)
{
	LPD3DXMESH mesh = NULL;

	//Model* mod = new Model;
	//mod->setMesh(mesh);
	//mod->setModelName(modelname);

	std::string modLocation = "..\\Models\\" + modelname;
	std::wstring stemp = std::wstring(modLocation.begin(), modLocation.end());
	LPCWSTR modelLPCWSTR = stemp.c_str();

	//LPDIRECT3DTEXTURE9* TheModel;

	HRESULT result = D3DXLoadMeshFromX( modelLPCWSTR, D3DXMESH_SYSTEMMEM,
										((LPDIRECT3DDEVICE9)renderer->get3DDevice()), NULL,
                                       NULL, NULL, NULL,
									   &mesh );

	
	if( FAILED( D3DXLoadMeshFromX( modelLPCWSTR, D3DXMESH_SYSTEMMEM,
										((LPDIRECT3DDEVICE9)renderer->get3DDevice()), NULL,
                                       NULL, NULL, NULL,
									   &mesh ) ) )
        {
            MessageBox( NULL, L"Could not find model", L"Meshes.exe", MB_OK );
          
        }

	MeshWrapper* TheNewMesh = new MeshWrapper(mesh);

	renderer->addMesh(modelname, TheNewMesh);

	object->setSubSet(D3DXMESH_SYSTEMMEM);

	return S_OK;
}