#ifndef MODELLOADER_H
#define MODELLOADER_H

#include <d3d9.h>
#include <d3dx9.h>
#include <iostream>
#include <string>
#include "Model.h"
#include "DirectXRenderer.h"
#include "VisualObject.h"

class ModelLoader
{
public:
	//Constructor
	ModelLoader();

	//Destructor
	~ModelLoader();

	//Loads a model from a .x file, where modelname is the filepath in a string and object is the target visualtobject to load it into.
	HRESULT LoadModel(std::string modelname, Renderer* DirectXRenderer, VisualObject* object);
};

#endif