#ifndef KERNEL_H
#define KERNEL_H

#include <iostream>
#include "Renderer.h"
#include "Resource_Manager.h"
#include "Scene_Manager.h"
#include "Window_Manager.h"

class Kernel
{
public:
	//Constructor, all components (the managers) are created here
	Kernel();

	//Destructor
	~Kernel();

	//Initializes the kernel, this links the various components (the managers) who then take over functionality once run is called
	void Initialize();

	//Runs the kernel, only used as entry point, the various managers and their sub components do all logic
	void Run();

private:
	//The WindowManager used throughout the entire engine
	Window_Manager* myWindowManager; 

	//The ResourceManager used throughout the entire engine
	Resource_Manager* myResourceManager;

	//The Renderer used throughout the entire engine
	Renderer* myRenderer;

	//The SceneManager used throughout the entire engine
	Scene_Manager* mySceneManager;

	//The RUNSTATE of the engine
	ERUNSTATE Runstate;

};

#endif