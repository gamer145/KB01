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
	CurrentWindow = RequestWindow("Game Engine1");
	myDirectXRenderer->setDrawWindow(CurrentWindow);
	
	myResourceManager->setDirectXRenderer(myDirectXRenderer);
	myLevelLoader = new LevelLoader();

	logCount = 0;
	newScene();
}

Window* Scene_Manager::RequestWindow(std::string windowTitle)
{
	Window* window = myWindowManager->getWindow(windowTitle);
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

void Scene_Manager::setCurrentScene(std::string windowname)
{
	for(std::map<Scene*, Window*>::iterator i = Scenes.begin(); i != Scenes.end(); ++i)
	{
		if (i->second->getSchermNaam() == windowname)
		{
			CurrentScene = i->first;		
		}
	}
}

ERUNSTATE Scene_Manager::UpdateScene()
{
	ERUNSTATE state = RUNNING;
	if (logCount >= 10)
	{
		myWindowManager->LogActiveWindow();
		logCount = -1;
	} 
	logCount++;
	if ((CurrentWindow = myWindowManager->getActiveWindow()) != NULL)
	{
		setCurrentScene(CurrentWindow->getSchermNaam());


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
		else
		{
			CurrentScene->clear();
			CurrentScene->beginS();
			//myDirectXRenderer->setupRenderToTextureOculus();
			

			state = CurrentScene->Update();

			//myDirectXRenderer->RenderToTexture();

			CurrentScene->endS();

			//myDirectXRenderer->Present();

			CurrentWindow->updateWindow();

			return state;
		}
	}
	return state;
}
