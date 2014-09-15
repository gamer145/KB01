#ifndef SCENE_H
#define SCENE_H

#include <sstream>
#include <string>
#include <vector>
#include "Camera.h"
#include "Renderer.h"
#include "Resource_Manager.h"
#include "InputHandler.h"
#include <d3dx9.h>
#include "VisualObject.h"

class Scene
{
public:
	Scene();
	~Scene();
	std::string writeToString();
	void initCamera(InputHandler* IH);
	void Update();
	void SetRenderer(Renderer* render);
	void setResourceManager(Resource_Manager* r);
	void AddObject(VisualObject* newObject);
	void setCamera(Camera* c);
	Camera* getCamera();

	void beginS();
	void endS();
	void clear();
	
private:
	std::vector<VisualObject*> activeObjects;
	Camera* currentCamera;
	Resource_Manager* RManager;
	Renderer* myRenderer;
	void Draw();

	
};

#endif