#include "Scene_Manager.h"


Scene_Manager::Scene_Manager()
{
}

Scene_Manager::~Scene_Manager()
{
}

void Scene_Manager::SetUpManager(Window_Manager* windowManager, Resource_Manager* resourceManager, Renderer* DirectXRenderer)
{
	myWindowManager = windowManager;
	myResourceManager = resourceManager;
	myDirectXRenderer = DirectXRenderer;
	CurrentWindow = RequestWindow();
	myDirectXRenderer->setDrawWindow(CurrentWindow);
	
	myResourceManager->setDirectXRenderer(myDirectXRenderer);
	LevelLoader* levelLoader = new LevelLoader();

	CurrentScene = new Scene();
	CurrentScene->SetDirectXRenderer(myDirectXRenderer);
	CurrentScene->setResourceManager(myResourceManager);
	CurrentScene = levelLoader->ReadFromFile(myResourceManager, CurrentScene);


	myResourceManager->loadManualTexture("dome.jpg");
	hoogteMap = new Heightmap();
	hoogteMap->CreateHeightmap(myDirectXRenderer, L"..//Models//hoogtemap2.bmp");

	skybox = new Skybox();
	skybox->InitializeSkybox(myDirectXRenderer, myResourceManager);
	hoogteMap->SetupHeightmapMatrix(0, 0, 0);

	myInputHandler = new InputHandler();
	myInputHandler->InitInputHandler(CurrentWindow);
	CurrentScene->initCamera(myInputHandler);

	Scenes.insert (std::pair<Scene*, Window*>(CurrentScene, CurrentWindow));
}

Window* Scene_Manager::RequestWindow()
{
	std::string windowTitle = "3D Game Engine";
	Window* window = myWindowManager->getWindow(windowTitle);
	return window;
}

void Scene_Manager::addScene()
{
	Window* window = RequestWindow();
	Scene* scene = new Scene();	
	Scenes.insert ( std::pair<Scene*, Window*>(scene, window) ); 
}

void Scene_Manager::setCurrentScene(std::string windowname)
{
	for(std::map<Scene*, Window*>::iterator i = Scenes.begin(); i != Scenes.end(); ++i)
	{
		if (i->second->getSchermNaam() == windowname)
		{
			CurrentScene = i->first;
			CurrentWindow = i->second;			
		}
	}
}
/*
synch test 2
*/

ERUNSTATE Scene_Manager::UpdateScene()
{
		ERUNSTATE state;
		CurrentScene->clear();
		CurrentScene->beginS();

		state = CurrentScene->Update();	

		hoogteMap->RenderHeightmap(myDirectXRenderer);


		skybox->DrawSkybox(myDirectXRenderer, CurrentScene->getCamera()->getPosition());


		CurrentScene->endS();
		CurrentWindow->updateWindow();
	
		return state;
}
