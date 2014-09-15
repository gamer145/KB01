#ifndef MODELLOADER_H
#define MODELLOADER_H

#include <d3d9.h>
#include <d3dx9.h>
#include <iostream>
#include <string>
#include "Model.h"
#include "Renderer.h"
#include "VisualObject.h"

class ModelLoader
{
public:
	ModelLoader();
	~ModelLoader();
	HRESULT LoadModel(std::string modelname, Renderer* renderer, VisualObject* object);
};

#endif