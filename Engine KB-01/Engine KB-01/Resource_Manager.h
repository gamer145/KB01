#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <d3d9.h>
#include <d3dx9.h>
#include <Windows.h>
#include "CameraLoader.h"
//#include "LevelLoader.h"
#include "Model.h"
#include "ModelLoader.h"
#include "Renderer.h"
#include "SkyboxLoader.h"
#include "Texture.h"
#include "TextureLoader.h"
#include "VisualObject.h"
#include "Window_Manager.h"

class Resource_Manager
{
public:
	Resource_Manager();
	~Resource_Manager();
	void setRenderer(Renderer* newRenderer);
	VisualObject* LoadInModel(std::string modelname, std::string texturename);
	void loadManualTexture(std::string texturename);

	bool checkText(std::string textname);
	bool checkMesh(std::string meshname);

private:
	CameraLoader cameraLoader;
	//LevelLoader levelLoader;
	ModelLoader modelLoader;
	Renderer* renderer;
	SkyboxLoader skyboxLoader;
	TextureLoader textureLoader;
};

#endif

