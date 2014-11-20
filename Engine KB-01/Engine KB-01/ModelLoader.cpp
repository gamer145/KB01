#include "ModelLoader.h"

ModelLoader::ModelLoader()
{
}

ModelLoader::~ModelLoader()
{
}

HRESULT ModelLoader::LoadModel(std::string modelname, RendererInterface* renderer, VisualObject* object)
{
	MeshWrapper* mesh = new MeshWrapper();
	
	
	if( FAILED( renderer->LoadMeshFromFile(modelname, 272, mesh) ) )
        {
            MessageBox( NULL, L"Could not find model", L"Meshes.exe", MB_OK );
          
        }



	object->setSubSet(272);

	return S_OK;
}