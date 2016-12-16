#include "Scene.h"

Scene::Scene()
{

}


Scene::~Scene()
{
	if (currentCamera!=NULL) {
		delete currentCamera;
	}
	if (myDirectXRenderer != NULL) {
		myDirectXRenderer = NULL;
		delete myDirectXRenderer;
	}
	if (ground != NULL) {
		delete ground;
	}

	if (skybox != NULL) {
		delete skybox;
	}

	for each (VisualObject* V in activeObjects)
	{
		delete V;
	}
	for each (Light* L in activeLights)
	{
		delete L;
	}
}


/**
* Function:	Scene::initGround()
* Description: Initializes the ground of the scene
*/
void Scene::initGround(Resource_Manager* RManager)
{
	ground = new Ground();
	ground->SetTexture("grass.jpg");
	ground->CreateGround(myDirectXRenderer, RManager, L"..//Models//hoogtemap2.bmp");
	ground->SetupGroundMatrix(0, 0, 0);

}


/**
* Function:	Scene::initSkybox()
* Description: Initializes the skybox of the scene
*/
void Scene::initSkybox(Resource_Manager* RManager)
{
	skybox = new Skybox();
	skybox->SetTexture("dome2.jpg");
	skybox->InitializeSkybox(myDirectXRenderer, RManager);	
}


/**
* Function:	Scene::initCamera()
* Description: Initializes the camera of the scene
*/
void Scene::initCamera(InputHandlerInterface* IH)
{
	sceneState = RUNNING;
	
	currentCamera->Initialize();
	currentCamera->SetInputHandler(IH);
}


/**
* Function:	Scene::setCamera()
* Description: Sets the camera of the scene to an already build camera
*/
void Scene::setCamera(Camera* c)
{
	currentCamera = c;
}

/**
* Function:	Scene::getCamera()
* Description: Returns this specific scene's camera
*/
Camera* Scene::getCamera()
{
	return currentCamera;
}

/**
* Function:	Scene::AddObject()
* Description: Adds a VisualObject to the active object list
*/
void Scene::AddObject(VisualObject* newObject)
{
	activeObjects.push_back(newObject);
}

/**
* Function:	Scene::AddLight()
* Description: Adds a light to the collection of lights present in this scene
*/
void Scene::AddLight(Light* newLight)
{
	activeLights.push_back(newLight);
}

/**
* Function:	Scene::SetRenderer()
* Description: Sets the renderer used by this scene
*/
void Scene::SetRenderer(Renderer* render)
{
	myDirectXRenderer = render;
}

/**
* Function:	Scene::Update()
* Description: Updates the current scene and it's runtime components
* Returns a runstate based on what input is received from the inputHandler
*/
ERUNSTATE Scene::Update()
{
		currentCamera->Update(sceneState);
		Draw();
		return sceneState;
	
}

/**
* Function:	Scene::UpdateOculus()
* Description: Updates the current scene and it's runtime components
* Returns a runstate based on what input is received from the inputHandler
* Oculus version
*/
ERUNSTATE Scene::UpdateOculus(const OVR::Util::Render::StereoEyeParams& stereo)
{
	
		myDirectXRenderer->setViewportOculus(stereo);

//		currentCamera->UpdateOculus(myDirectXRenderer, stereo, SConfig, sceneState);
		Draw();
		return sceneState;

}


/**
* Function:	Scene::clear()
* Description: Clears the window, in preparation for the new draw with updated values
*/
void Scene::clear()
{
	myDirectXRenderer->Clear( 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
                         D3DCOLOR_XRGB(255, 0, 0 ), 1.0f, 0 );
}


/**
* Function:	Scene::beginS()
* Description: Tells the renderer it's time to begin
*/
void Scene::beginS()
{
	myDirectXRenderer->BeginS();
}


/**
* Function:	Scene::endS()
* Description: Tells the renderer it's time to end and to present it's handiwork to the world
*/
void Scene::endS()
{
	myDirectXRenderer->EndS();

	myDirectXRenderer->Present();
}

/*
OVR::Util::Render::StereoConfig Scene::GetConfig()
{
//	return SConfig;
	return NULL;
}

*/

/**
* Function:	Scene::Draw()
* Description: Use the renderer to draw what needs to be drawn onto the surface that needs to be drawn upon, what a drawn out charade
*/
void Scene::Draw()
{

	//myDirectXRenderer->LoadShaderFromFile("firstshader", "../Shaders/TextShader.fx", "TextShader", "ColorShader");

	myDirectXRenderer->SetUpWorld(currentCamera->getPosition(), currentCamera->getProjectionMatrix());
	
	skybox->DrawSkybox(myDirectXRenderer, currentCamera->getPosition());
			
	ground->DrawGround(myDirectXRenderer);			

	for(std::vector<VisualObject*>::iterator i = activeObjects.begin(); i != activeObjects.end(); ++i)
		{
			VisualObject* currentobj = *i;
			currentobj->draw(myDirectXRenderer);
		}

	//myDirectXRenderer->StopRenderingWithShaders();

}


