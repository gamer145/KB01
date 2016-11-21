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
	Scene(); //Constructor
	~Scene(); //Destructor
	void initCamera(InputHandlerInterface* IH); //Initialize a new camera and give it the needs to read Input
	ERUNSTATE Update();	//Update loop, what needs to be calculated or processed during runtime goes here
	ERUNSTATE UpdateOculus(const OVR::Util::Render::StereoEyeParams& stereo); //Update loop for Oculus
	void SetDirectXRenderer(Renderer* render); //Assigns a existing directX renderer device to the scene
	void setResourceManager(Resource_Manager* r); //Assigns a existing Resource Manager to the scene
	void AddObject(VisualObject* newObject); //Adds a new object to the list of VisualObjects in the scene
	void AddLight(Light* newLight); //Adds a new light to the list of Lights in the scene
	void setCamera(Camera* c); //Assigns a existing Camera to the scene
	Camera* getCamera(); //Returns the Camera currently assigned to the scene
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