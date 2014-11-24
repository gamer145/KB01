#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <map>
#include <string>
#include <vector>
#include "Heightmap.h"
#include "InputHandler.h"
#include "LevelLoader.h"
#include "Resource_Manager.h"
#include "Scene.h"
#include "Window_Manager.h"

class Scene_Manager
{
public:
	Scene_Manager();
	~Scene_Manager();
	void SetUpManager(Window_Manager* windowManager, Resource_Manager* resourceManager, Renderer* renderer);
	void addScene();
	bool UpdateScene();
	void setCurrentScene(std::string windowname);
	Window* RequestWindow();
	
private:
	std::map<Scene*, Window*> Scenes;
	Window_Manager* myWindowManager;
	Resource_Manager* myResourceManager;
	InputHandlerInterface* myInputHandler;
	Scene* CurrentScene;
	Window* CurrentWindow;
	Renderer* myRenderer;
	Heightmap* hoogteMap;
};

#endif