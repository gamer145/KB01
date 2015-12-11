#ifndef SCENE_H
#define SCENE_H

#include <sstream>
#include <string>
#include <vector>
#include "Light.h"
#include "Camera.h"
#include "Renderer.h"
#include "Resource_Manager.h"
#include "InputHandler.h"
#include <d3dx9.h>
#include "VisualObject.h"
#include "OVR.h"

class Scene
{
public:
	Scene();
	~Scene();
	std::string writeToString();
	void initCamera(InputHandlerInterface* IH);
	ERUNSTATE Update();
	ERUNSTATE UpdateOculus(const OVR::Util::Render::StereoEyeParams& stereo);
	void SetDirectXRenderer(Renderer* render);
	void setResourceManager(Resource_Manager* r);
	void AddObject(VisualObject* newObject);
	void AddLight(Light* newLight);
	void setCamera(Camera* c);
	Camera* getCamera();
	OVR::Util::Render::StereoConfig GetConfig();


	void beginS();
	void endS();
	void clear();
	
private:
	std::vector<VisualObject*> activeObjects;
	std::vector<Light*> activeLights;
	Camera* currentCamera;
	Resource_Manager* RManager;
	Renderer* myDirectXRenderer;
	void Draw();
	OVR::Util::Render::StereoConfig SConfig;
	bool oculus;
	ERUNSTATE sceneState;
	
};

#endif