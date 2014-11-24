#ifndef KERNEL_H
#define KERNEL_H

#include <iostream>
#include "InputHandler.h"
#include "Logger.h"
#include "RendererInterface.h"
#include "Resource_Manager.h"
#include "Scene_Manager.h"
#include "Window_Manager.h"
#include "LevelLoader.h"

class Kernel
{
public:	
	Kernel();
	~Kernel();
	void Initialize();
	void Run();

private:
	Window_Manager* myWindowManager;
	Resource_Manager* myResourceManager;
	RendererInterface* myRenderer;
	Scene_Manager* mySceneManager;
	bool TemporaryStopChecker;

};

#endif