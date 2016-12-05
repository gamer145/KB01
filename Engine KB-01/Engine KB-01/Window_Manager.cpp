#include "Window_Manager.h"

Window_Manager::Window_Manager()
{
	loggerWM = Logger::GetLogger();
}

Window_Manager::~Window_Manager()
{
}

void Window_Manager::createWindow(std::string title)
{
	Window* myWindow = new Window(title);
	Windows.push_back(myWindow);
}

Window* Window_Manager::getWindow(std::string schermnaam)
{
	for(std::vector<Window*>::iterator i = Windows.begin(); i != Windows.end(); ++i)
	{
		Window* currentWindow = *i;
		if (currentWindow->getSchermNaam().compare(schermnaam) == 0)
		{
			return currentWindow; //Als er een window is gevonden met die titel, return dan die window.
		}
	}
	//Anders maak nieuw window en return deze.
	createWindow(schermnaam);
	return getWindow(schermnaam);
}

Window* Window_Manager::getWindow(HWND hwnd)
{
	for (std::vector<Window*>::iterator i = Windows.begin(); i != Windows.end(); ++i)
	{
		Window* currentWindow = *i;
		if (currentWindow->getHWND() == hwnd)
		{
			return currentWindow; //Als er een window is gevonden met die HWND, return dan die window.
		}
	}
}

void Window_Manager::LogActiveWindow()
{
	HWND activeWindow = GetForegroundWindow();
	std::string convertedHandleString = EngineTextHandling::HwndToString(activeWindow);
	loggerWM->WriteToFile(Error, convertedHandleString);
}
	
Window* Window_Manager::getActiveWindow()
{
	HWND activeWindow = GetForegroundWindow();
	for (std::vector<Window*>::iterator i = Windows.begin(); i != Windows.end(); ++i)
	{
		Window* currentWindow = *i;		
		if (currentWindow->getHWND() == activeWindow)
		{
			currentWindow->setActiveState(true);
			return currentWindow;
		}
		else
		{
			currentWindow->setActiveState(false);
		}
		
		//loggerWM->WriteToFile(Error, "No active Window found");
		return NULL;
	}
}