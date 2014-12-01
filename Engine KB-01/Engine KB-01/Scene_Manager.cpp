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

	myInputHandler = new InputHandler(CurrentWindow);
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

bool Scene_Manager::UpdateScene()
{

		CurrentScene->clear();
		CurrentScene->beginS();

		CurrentScene->Update();	

		hoogteMap->SetupHeightmapMatrix(0, 0, 0, CurrentScene->getCamera()->getOffSetMatrix());
		hoogteMap->RenderHeightmap(myDirectXRenderer);


		skybox->DrawSkybox(myDirectXRenderer, CurrentScene->getCamera()->getPosition());


		CurrentScene->endS();
		CurrentWindow->updateWindow();
	
		return myInputHandler->getKeyBoardListener()->ProcessKBInput((byte)DIKEYBOARD_ESCAPE);
	
}
