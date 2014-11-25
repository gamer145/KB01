#include "ModelLoader.h"

ModelLoader::ModelLoader()
{
}

ModelLoader::~ModelLoader()
{
}

HRESULT ModelLoader::LoadModel(std::string modelname, Renderer* DirectXRenderer, VisualObject* object)
{
	MeshWrapper* mesh = new MeshWrapper();
	
	
	if( FAILED( DirectXRenderer->LoadMeshFromFile(modelname, 272, mesh) ) )
        {
            MessageBox( NULL, L"Could not find model", L"Meshes.exe", MB_OK );
          
        }



	object->setSubSet(272);

	return S_OK;
}