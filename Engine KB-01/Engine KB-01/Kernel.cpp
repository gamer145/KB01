#define DIRECTINPUT_VERSION 0x0800

#include "Kernel.h"

Kernel::Kernel()
{
	myWindowManager = new Window_Manager();
	myResourceManager = new Resource_Manager();
	myRenderer = new DirectXRenderer();
	myRenderer->OculusNowYah(false);
	mySceneManager = new Scene_Manager();

}

Kernel::~Kernel()
{

}

void Kernel::Initialize()
{
	mySceneManager->SetUpManager(myWindowManager, myResourceManager, myRenderer);

}

void Kernel::Run()
{
	Runstate = mySceneManager->UpdateScene();

	while (Runstate == RUNNING)
	{
		Runstate = mySceneManager->UpdateScene();
	}
}