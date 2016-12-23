#ifndef LEVELLOADER_H
#define LEVELLOADER_H

#include "vector"
#include "Resource_Manager.h"
#include "Scene.h" 
#include "VisualObject.h"
#include "Light.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstddef>

class LevelLoader
{
public:
	//Constructor
	LevelLoader();

	//Destructor
	~LevelLoader();

	//Reads a .txt file and translates it into an existing scene the engine can use
	Scene* ReadFromFile(Resource_Manager* resourceManager, Scene* currentScene); 
};

#endif