#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <map>
#include <string>
#include <vector>
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
	void SetUpManager(Window_Manager* windowManager, Resource_Manager* resourceManager, Renderer* DirectXRenderer);
	void newScene();
	void newScene(int windowX, int windowY, int WindowWidth, int WindowHeight);
	ERUNSTATE UpdateScene();
	void setCurrentScene(std::string windowname);	
	void DeleteLinkedScenes(Window* doomedWindow);
	
private:
	Window* RequestWindow(std::string windowTitle);
	Window* RequestWindow(std::string windowTitle, int windowX, int windowY, int WindowWidth, int WindowHeight);
	std::map<Scene*, Window*> Scenes;
	Window_Manager* myWindowManager;
	Resource_Manager* myResourceManager;
	InputHandlerInterface* myInputHandler;
	LevelLoader* myLevelLoader;
	Scene* CurrentScene;
	Window* CurrentWindow;
	Renderer* myDirectXRenderer;
	int logCount;

};

#endif