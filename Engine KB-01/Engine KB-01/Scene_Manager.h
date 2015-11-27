#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <map>
#include <string>
#include <vector>
#include "Ground.h"
#include "InputHandler.h"
#include "LevelLoader.h"
#include "Resource_Manager.h"
#include "Scene.h"
#include "Window_Manager.h"
#include "Skybox.h"

class Scene_Manager
{
public:
	Scene_Manager();
	~Scene_Manager();
	void SetUpManager(Window_Manager* windowManager, Resource_Manager* resourceManager, Renderer* DirectXRenderer);
	void addScene();
	ERUNSTATE UpdateScene();
	void setCurrentScene(std::string windowname);
	Window* RequestWindow();
	
private:
	std::map<Scene*, Window*> Scenes;
	Window_Manager* myWindowManager;
	Resource_Manager* myResourceManager;
	InputHandlerInterface* myInputHandler;
	Scene* CurrentScene;
	Window* CurrentWindow;
	Renderer* myDirectXRenderer;
	Ground* hoogteMap;
	Skybox* skybox;
};

#endif