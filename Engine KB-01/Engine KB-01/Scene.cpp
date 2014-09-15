#include "Scene.h"

Scene::Scene()
{

}


Scene::~Scene()
{

}

void Scene::initCamera(InputHandler* IH)
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

void Scene::SetRenderer(Renderer* render)
{
	myRenderer = render;
}

void Scene::setResourceManager(Resource_Manager* r)
{
	RManager = r;
}

void Scene::Update()
{
	currentCamera->Update();
	Draw();
}

void Scene::clear()
{
	myRenderer->Clear( 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
                         D3DCOLOR_XRGB(0, 0, 0 ), 1.0f, 0 );
}

void Scene::beginS()
{
	myRenderer->BeginS();
}

void Scene::endS()
{
	myRenderer->EndS();

	myRenderer->Present();
}

void Scene::Draw()
{

			myRenderer->SetUpWorld(currentCamera->getOffSetMatrix(), currentCamera->getPosition(), currentCamera->getProjectionMatrix());

			for(std::vector<VisualObject*>::iterator i = activeObjects.begin(); i != activeObjects.end(); ++i)
			{
				VisualObject* currentobj = *i;

				currentobj->draw(myRenderer, currentCamera->getOffSetMatrix());
				

    
			}
}


