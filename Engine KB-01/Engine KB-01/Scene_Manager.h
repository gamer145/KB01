#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <map>
#include <string>
#include <vector>
#include "DirectXInputHandler.h"
#include "LevelLoader.h"
#include "Resource_Manager.h"
#include "Scene.h"
#include "Window_Manager.h"

class Scene_Manager
{
public:
	//Constructor
	Scene_Manager();

	//Destructor
	~Scene_Manager();

	//Initializes the Scene Manager and its further components, point of entry from the kernel
	void SetUpManager(Window_Manager* windowManager, Resource_Manager* resourceManager, Renderer* DirectXRenderer); 

	//Creates a new scene and adds it to the scene list.
	//It creates a window using default dimensions and attaches it to to the required components.
	void newScene();	

	//Creates a new scene and adds it to the scene list.
	//It creates a window using specified dimensions and attaches it to to the required components.
	void newScene(int windowX, int windowY, int WindowWidth, int WindowHeight);

	//Updates the current scene.
	//Checks which window is active, and then actives the corresponding scene.
	ERUNSTATE UpdateScene();
	
private:
	//Sets the current Scene corresponding to the window name
	void setCurrentScene(std::string windowname);

	//Goes through the collection of scenes and windows, finds and then deletes all scenes attached to the window.
	void DeleteLinkedScenes(Window* doomedWindow); 

	//Requests a window from the window manager with the specified name
	Window* RequestWindow(std::string windowTitle); 

	//Requests a window from the window manager with the specified name
	Window* RequestWindow(std::string windowTitle, int windowX, int windowY, int WindowWidth, int WindowHeight); 

	//The collection of scenes and their corresponding window
	std::map<Scene*, Window*> Scenes; 

	//The attached window Manager
	Window_Manager* myWindowManager; 

	//The attached resource Manager passed onto other lower level life forms
	Resource_Manager* myResourceManager; 

	//The attached level loader, used to.. load levels, what else?
	LevelLoader* myLevelLoader; 

	//The current Scene, used within update loop to determine what to update, and where the renderer is going to draw
	Scene* CurrentScene; 

	//The current window, the piece of paper to be scribbled upon. Used within the update loop
	Window* CurrentWindow; 

	//The known rendered object, use to pass onto lower level life forms
	Renderer* myDirectXRenderer; 

};

#endif