#include "Resource_Manager.h"
#include <Windows.h>

Resource_Manager::Resource_Manager()
{
	 	 
}


Resource_Manager::~Resource_Manager()
{

}


void Resource_Manager::setRenderer(Renderer* newRenderer)
{
	renderer = newRenderer;
}


VisualObject* Resource_Manager::LoadInModel(std::string modelname, std::string texturename)
{
	VisualObject* object = new VisualObject;
	modelLoader.LoadModel(modelname, renderer, object);
	object->setModel(modelname);
	textureLoader.LoadTexture(texturename, renderer);
	object->setTexture(texturename);
	return object;
}

void Resource_Manager::loadManualTexture(std::string texturename)
{
	textureLoader.LoadTexture(texturename, renderer);
}

bool Resource_Manager::checkText(std::string textname)
{

	std::map<std::string, LPDIRECT3DTEXTURE9> textures = renderer->getTextures();
	//std::map<std::string, LPDIRECT3DTEXTURE9>::iterator a = textures.end();

	for(std::map<std::string, LPDIRECT3DTEXTURE9>::iterator i = textures.begin(); i != textures.end(); ++i)
	{
		if(i->first == textname)
		{
			return true;
		}

	}
	return false;
}

bool Resource_Manager::checkMesh(std::string meshname)
{
	std::map<std::string, LPD3DXMESH> meshes = renderer->getMeshes();
	//std::map<std::string, LPD3DXMESH>::iterator a = meshes.end();

	for(std::map<std::string, LPD3DXMESH>::iterator i = meshes.begin(); i != meshes.end(); ++i)
	{
		if(i->first == meshname)
		{
			return true;
		}

	}
	return false;
}