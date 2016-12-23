#include "ModelLoader.h"

ModelLoader::ModelLoader()
{
}

ModelLoader::~ModelLoader()
{
}

/**
* Function:	ModelLoader::LoadModel(std::string modelname, Renderer* DirectXRenderer, VisualObject* object)
* Description:	Loads a model from a .x file, where modelname is the filepath in a string and object is the target visualtobject to load it into.
*/
HRESULT ModelLoader::LoadModel(std::string modelname, Renderer* DirectXRenderer, VisualObject* object)
{
	MeshWrapper* mesh = new MeshWrapper();
	
	
	if( FAILED( DirectXRenderer->LoadMeshFromFile(modelname, NULL, mesh) ) )
        {
            MessageBox( NULL, L"Could not find model", L"Meshes.exe", MB_OK );
          
        }



	object->setSubSet(NULL);

	return S_OK;
}