#include "Scene.h"

Scene::Scene()
{

}


Scene::~Scene()
{

}

void Scene::initCamera(InputHandlerInterface* IH)
{
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

void Scene::setResourceManager(Resource_Manager* r)
{
	RManager = r;
}

ERUNSTATE Scene::Update()
{
	
		ERUNSTATE state = currentCamera->Update();
		Draw();
		return state;
	
}

ERUNSTATE Scene::UpdateOculus(const OVR::Util::Render::StereoEyeParams& stereo)
{
	
		myDirectXRenderer->setViewportOculus(stereo);

		ERUNSTATE state = currentCamera->UpdateOculus(myDirectXRenderer, stereo, SConfig);
		Draw();
		return state;

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

OVR::Util::Render::StereoConfig Scene::GetConfig()
{
	return SConfig;
}

void Scene::Draw()
{

	//myDirectXRenderer->LoadShaderFromFile("firstshader", "../Shaders/TextShader.fx", "TextShader", "ColorShader");

			myDirectXRenderer->SetUpWorld(currentCamera->getPosition(), currentCamera->getProjectionMatrix());

			//myDirectXRenderer->SetShader("firstshader");

			for(std::vector<VisualObject*>::iterator i = activeObjects.begin(); i != activeObjects.end(); ++i)
			{
				VisualObject* currentobj = *i;



				currentobj->draw(myDirectXRenderer);
				
    
    
			}

			//myDirectXRenderer->StopRenderingWithShaders();

}


