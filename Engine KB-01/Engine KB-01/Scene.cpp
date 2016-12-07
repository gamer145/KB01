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

void Scene::initGround(Resource_Manager* RManager)
{
	ground = new Ground();
	ground->SetTexture("grass.jpg");
	ground->CreateGround(myDirectXRenderer, RManager, L"..//Models//hoogtemap2.bmp");
	ground->SetupGroundMatrix(0, 0, 0);

}

void Scene::initSkybox(Resource_Manager* RManager)
{
	skybox = new Skybox();
	skybox->SetTexture("dome2.jpg");
	skybox->InitializeSkybox(myDirectXRenderer, RManager);	
}

void Scene::initCamera(InputHandlerInterface* IH)
{
	sceneState = RUNNING;
	
	currentCamera->Initialize();
	currentCamera->SetInputHandler(IH);
}

void Scene::setCamera(Camera* c)
{
	currentCamera = c;
}

Camera* Scene::getCamera()
{
	return currentCamera;
}

void Scene::AddObject(VisualObject* newObject)
{
	activeObjects.push_back(newObject);
}

void Scene::AddLight(Light* newLight)
{
	activeLights.push_back(newLight);
}

void Scene::SetDirectXRenderer(Renderer* render)
{
	myDirectXRenderer = render;
}

ERUNSTATE Scene::Update()
{
		currentCamera->Update(sceneState);
		Draw();
		return sceneState;
	
}

ERUNSTATE Scene::UpdateOculus(const OVR::Util::Render::StereoEyeParams& stereo)
{
	
		myDirectXRenderer->setViewportOculus(stereo);

//		currentCamera->UpdateOculus(myDirectXRenderer, stereo, SConfig, sceneState);
		Draw();
		return sceneState;

}

void Scene::clear()
{
	myDirectXRenderer->Clear( 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
                         D3DCOLOR_XRGB(255, 0, 0 ), 1.0f, 0 );
}

void Scene::beginS()
{
	myDirectXRenderer->BeginS();
}

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


