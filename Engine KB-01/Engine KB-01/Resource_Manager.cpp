#include "Resource_Manager.h"
#include <Windows.h>

Resource_Manager::Resource_Manager()
{
	 	 
}


Resource_Manager::~Resource_Manager()
{
	if (DirectXRenderer != NULL) {
		delete DirectXRenderer;
	}

}

/**
* Function:	Renderer::setDrawWindow(Window* windowtodrawin)
* Description:	Set the current window to draw our scene to
*/
void Resource_Manager::setDirectXRenderer(Renderer* newDirectXRenderer)
{
	DirectXRenderer = newDirectXRenderer;
}

/**
* Function:	Renderer::setDrawWindow(Window* windowtodrawin)
* Description:	Set the current window to draw our scene to
*/
VisualObject* Resource_Manager::LoadInModel(std::string modelname, std::string texturename)
{
	VisualObject* object = new VisualObject;
	modelLoader.LoadModel(modelname, DirectXRenderer, object);
	object->setModel(modelname);
	textureLoader.LoadTexture(texturename, DirectXRenderer);
	object->setTexture(texturename);
	return object;
}

/**
* Function:	Renderer::setDrawWindow(Window* windowtodrawin)
* Description:	Set the current window to draw our scene to
*/
void Resource_Manager::loadManualTexture(std::string texturename)
{
	textureLoader.LoadTexture(texturename, DirectXRenderer);
}

/**
* Function:	Renderer::setDrawWindow(Window* windowtodrawin)
* Description:	Set the current window to draw our scene to
*/
bool Resource_Manager::checkText(std::string textname)
{

	std::map<std::string, TextureWrapper*> textures = DirectXRenderer->getTextures();
	//std::map<std::string, LPDIRECT3DTEXTURE9>::iterator a = textures.end();

	for (std::map<std::string, TextureWrapper*>::iterator i = textures.begin(); i != textures.end(); ++i)
	{
		if(i->first == textname)
		{
			return true;
		}

	}
	return false;
}


/**
* Function:	Renderer::setDrawWindow(Window* windowtodrawin)
* Description:	Set the current window to draw our scene to
*/
bool Resource_Manager::checkMesh(std::string meshname)
{
	std::map<std::string, MeshWrapper*> meshes = DirectXRenderer->getMeshes();
	//std::map<std::string, LPD3DXMESH>::iterator a = meshes.end();

	for (std::map<std::string, MeshWrapper*>::iterator i = meshes.begin(); i != meshes.end(); ++i)
	{
		if(i->first == meshname)
		{
			return true;
		}

	}
	return false;
}