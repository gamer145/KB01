#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <d3d9.h>
#include <d3dx9.h>
#include <Windows.h>
//#include "LevelLoader.h"
#include "Model.h"
#include "ModelLoader.h"
#include "Renderer.h"
#include "Texture.h"
#include "TextureLoader.h"
#include "VisualObject.h"
#include "Window_Manager.h"

class Resource_Manager
{
public:
	Resource_Manager();
	~Resource_Manager();

	//Sets the renderer to use in the loading of all resources
	void setDirectXRenderer(Renderer* newDirectXRenderer); 

	//Loads in a complete model with mesh and texture, using both the model and texture loader, and returns the visual object it is loaded into.
	VisualObject* LoadInModel(std::string modelname, std::string texturename); 

	//Loads just a texture to use.
	void loadManualTexture(std::string texturename); 

	//Checks if a texture has already been loaded.
	bool checkText(std::string textname); 

	//Checks if a mesh has already been loaded.
	bool checkMesh(std::string meshname); 

private:
	ModelLoader modelLoader;
	//The man the myth the legend.
	Renderer* DirectXRenderer; 
	TextureLoader textureLoader;
};

#endif

