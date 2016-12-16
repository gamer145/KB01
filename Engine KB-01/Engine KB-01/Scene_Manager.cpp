#include "Scene_Manager.h"


Scene_Manager::Scene_Manager()
{
}

Scene_Manager::~Scene_Manager()
{
	if (myDirectXRenderer != NULL) {
		delete myDirectXRenderer;
	}
	if (myInputHandler != NULL) {
		delete myInputHandler;
	}
	if (myLevelLoader != NULL) {
		delete myLevelLoader;
	}
	if (myResourceManager != NULL) {
		delete myResourceManager;
	}
	if (myWindowManager != NULL) {
		delete myWindowManager;
	}
	if (CurrentScene != NULL) {
		delete CurrentScene;
	}
	if (CurrentWindow != NULL) {
		delete CurrentWindow;
	}

	for each (std::pair<Scene*, Window*> S in Scenes)
	{
		delete S.first;
		delete S.second;
	}
}

void Scene_Manager::SetUpManager(Window_Manager* windowManager, Resource_Manager* resourceManager, Renderer* DirectXRenderer)
{
	myWindowManager = windowManager;
	myResourceManager = resourceManager;
	myDirectXRenderer = DirectXRenderer;
	CurrentWindow = RequestWindow("Game Engine1");
	myDirectXRenderer->InitGraphics(CurrentWindow);

	
	myResourceManager->setDirectXRenderer(myDirectXRenderer);
	myLevelLoader = new LevelLoader();

	logCount = 0;
	newScene();
	newScene(700, 100, 600, 600);
}

/**
* Function:	Scene_Manager::RequestWindow()
* Description: Asks the windowManager for a window with the specified name. If it doesn't exist yet it will be created
*/
Window* Scene_Manager::RequestWindow(std::string windowTitle)
{
	Window* window = myWindowManager->getWindow(windowTitle);
	return window;
}

/**
* Function:	Scene_Manager::RequestWindow()
* Description: Asks the windowManager for a window with the specified name. If it doesn't exist yet it will be created with the specified dimensions
*/
Window* Scene_Manager::RequestWindow(std::string windowTitle, int windowX, int windowY, int windowWidth, int windowHeight)
{
	Window* window = myWindowManager->getWindow(windowTitle, windowX, windowY, windowWidth, windowHeight);
	return window;
}

void Scene_Manager::newScene()
{
	Window* window = RequestWindow("Game Engine" + (std::to_string(Scenes.size() + 1)));
	CurrentScene = new Scene();	
	CurrentScene->SetDirectXRenderer(myDirectXRenderer);
	myDirectXRenderer->setDrawWindow(window);
	CurrentScene = myLevelLoader->ReadFromFile(myResourceManager, CurrentScene);
	CurrentScene->initGround(myResourceManager);
	CurrentScene->initSkybox(myResourceManager);

	myInputHandler = new InputHandler();
	myInputHandler->InitInputHandler(window);
	CurrentScene->initCamera(myInputHandler);
	Scenes.insert ( std::pair<Scene*, Window*>(CurrentScene, window) );
}

void Scene_Manager::newScene(int windowX, int windowY, int windowWidth, int windowHeight)
{
	Window* window = RequestWindow("Game Engine" + (std::to_string(Scenes.size() + 1)), windowX, windowY, windowWidth, windowHeight);
	CurrentScene = new Scene();
	CurrentScene->SetDirectXRenderer(myDirectXRenderer);
	myDirectXRenderer->setDrawWindow(window);
	CurrentScene = myLevelLoader->ReadFromFile(myResourceManager, CurrentScene);
	CurrentScene->initGround(myResourceManager);
	CurrentScene->initSkybox(myResourceManager);

	myInputHandler = new InputHandler();
	myInputHandler->InitInputHandler(window);
	CurrentScene->initCamera(myInputHandler);
	Scenes.insert(std::pair<Scene*, Window*>(CurrentScene, window));
}

void Scene_Manager::setCurrentScene(std::string windowname)
{
	for(std::map<Scene*, Window*>::iterator i = Scenes.begin(); i != Scenes.end(); ++i)
	{
		if (i->second->getWindowName() == windowname)
		{
			CurrentScene = i->first;		
		}
	}
}

void Scene_Manager::DeleteLinkedScenes(Window* doomedWindow)
{
	if (Scenes.size() >= 1)
	{
		std::vector<Scene*> linkedScenes;

		for (std::map<Scene*, Window*>::iterator i = Scenes.begin(); i != Scenes.end(); ++i)
		{	
			if (i->second == doomedWindow)
			{
				linkedScenes.push_back(i->first);
			}
		}

		if (linkedScenes.size() >= 1)
		{
			for each(Scene* S in linkedScenes)
			{
				for (std::map<Scene*, Window*>::iterator i = Scenes.begin(); i != Scenes.end(); ++i)
				{
					if (i->first == S)
					{
						Scenes.erase(i);
						break;
					}
				}
				delete S;
			}
		}

	}
}

ERUNSTATE Scene_Manager::UpdateScene()
{
	ERUNSTATE state;

	if ((CurrentWindow = myWindowManager->getActiveWindow()) != NULL)
	{
		setCurrentScene(CurrentWindow->getWindowName());

		myDirectXRenderer->setDrawWindow(CurrentWindow);
		/*
		if (myDirectXRenderer->OculusOrNah())
		{
			myDirectXRenderer->setupRenderToTextureOculus();
			//CurrentScene->clear();
			//CurrentScene->beginS();

			state = CurrentScene->UpdateOculus(CurrentScene->GetConfig().GetEyeRenderParams(OVR::Util::Render::StereoEye_Left));
			state = CurrentScene->UpdateOculus(CurrentScene->GetConfig().GetEyeRenderParams(OVR::Util::Render::StereoEye_Right));

			//CurrentScene->endS();

			myDirectXRenderer->endRenderToTextureOculus();

			myDirectXRenderer->setTransform(E_WORLD, CurrentScene->getCamera()->getPosition());

			//distort the textures
			myDirectXRenderer->renderEyeOculus(CurrentScene->GetConfig().GetEyeRenderParams(OVR::Util::Render::StereoEye_Left), CurrentScene->GetConfig());
			myDirectXRenderer->renderEyeOculus(CurrentScene->GetConfig().GetEyeRenderParams(OVR::Util::Render::StereoEye_Right), CurrentScene->GetConfig());
			//present the textures
			myDirectXRenderer->renderSceneOculus(CurrentScene->GetConfig().GetEyeRenderParams(OVR::Util::Render::StereoEye_Left), CurrentScene->GetConfig());
			myDirectXRenderer->renderSceneOculus(CurrentScene->GetConfig().GetEyeRenderParams(OVR::Util::Render::StereoEye_Right), CurrentScene->GetConfig());

			myDirectXRenderer->Present();
			//myDirectXRenderer->PresentWithWindow(CurrentWindow->getHWND());

			CurrentWindow->updateWindow();

			return state;
		}
		*/
		
			CurrentScene->clear();
			CurrentScene->beginS();
			//myDirectXRenderer->setupRenderToTextureOculus();
			

			state = CurrentScene->Update();

			//myDirectXRenderer->RenderToTexture();

			CurrentScene->endS();

			if (state == EXIT)
			{
				DeleteLinkedScenes(CurrentWindow);
				myWindowManager->DestroyWindow(CurrentWindow);
				if (Scenes.size() >= 1)
				{
					state = RUNNING;
				}
			}

			//myDirectXRenderer->Present();

			return state;
		
	}
	state = RUNNING;
	return state;

}
