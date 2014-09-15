#define DIRECTINPUT_VERSION 0x0800

#include <iostream>
#include "InputHandler.h"
#include "Logger.h"
#include "Renderer.h"
#include "Resource_Manager.h"
#include "Scene_Manager.h"
#include "Window_Manager.h"
#include "LevelLoader.h"

int main()
{

	Window_Manager* myWindowManager = new Window_Manager();

	Resource_Manager* myResourceManager = new Resource_Manager();
	Renderer* myRenderer = new Renderer();

	Scene_Manager* mySceneManager = new Scene_Manager();
	mySceneManager->SetUpManager(myWindowManager, myResourceManager, myRenderer);
	
	return 0;
	
}
