#ifndef SCENE_H
#define SCENE_H

#include <sstream>
#include <string>
#include <vector>
#include "Light.h"
#include "Camera.h"
#include "Renderer.h"
#include "Ground.h"
#include "Skybox.h"
#include "Resource_Manager.h"
#include "InputHandlerInterface.h"
#include <d3dx9.h>
#include "VisualObject.h"
#include "OVR.h"

class Scene
{
public:
	//Constructor
	Scene();

	//Destructor
	~Scene(); 

	//Initialize a new camera and give it the needs to read Input
	void initCamera(InputHandlerInterface* IH);

	//Update loop, what needs to be calculated or processed during runtime goes here
	ERUNSTATE Update();	

	//Update loop for Oculus
	ERUNSTATE UpdateOculus(const OVR::Util::Render::StereoEyeParams& stereo); 

	//Assigns a existing directX renderer device to the scene
	void SetRenderer(Renderer* render); 

	//Adds a new object to the list of VisualObjects in the scene
	void AddObject(VisualObject* newObject); 

	//Adds a new light to the list of Lights in the scene
	void AddLight(Light* newLight); 

	//Assigns a existing Camera to the scene
	void setCamera(Camera* c); 

	//Returns the Camera currently assigned to the scene
	Camera* getCamera(); 

	//OVR::Util::Render::StereoConfig GetConfig(); //WARNING: UNFINISHED/DEPRECATED CODE, DO NOT USE.

	//Initializes a new ground for this scene
	void initGround(Resource_Manager* RManager); 

	//Initializes a new skybox for this scene
	void initSkybox(Resource_Manager* RManager); 


	/*
		Draw loop = Clear -> BeginS -> UpdateScene -> EndS
	*/

	//Tells the renderer it's time to begin
	void beginS();

	//Tells the renderer it's time to end and to present it's handiwork to the world
	void endS();

	//Clears the window, in preparation for the new draw with updated values
	void clear();
	
private:
	//The collection of visual objects in the scene
	std::vector<VisualObject*> activeObjects;

	//The collection of lights in the scene
	std::vector<Light*> activeLights;

	//The camera of the scene
	Camera* currentCamera;

	//The attached renderer, used to draw the components of the scene
	Renderer* myDirectXRenderer;

	//Use the renderer to draw what needs to be drawn onto the surface that needs to be drawn upon, what a drawn out charade
	void Draw();

	//OVR::Util::Render::StereoConfig SConfig;

	//Is oculus mode on or not
	bool oculus;

	//In what state is the scene
	ERUNSTATE sceneState;

	//The ground of the scene
	Ground* ground;

	//The skybox of the scene
	Skybox* skybox;
	
};

#endif