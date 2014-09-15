#ifndef LEVELLOADER_H
#define LEVELLOADER_H

#include "vector"
#include "Resource_Manager.h"
#include "Scene.h" 
#include "VisualObject.h" 
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstddef>
#include <d3dx9.h>

class LevelLoader
{
public:
	LevelLoader();
	~LevelLoader();
	Scene* ReadFromFile(Resource_Manager* resourceManager, Scene* currentScene);
};

#endif