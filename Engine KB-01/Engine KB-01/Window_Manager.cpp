#include "Window_Manager.h"

Window_Manager::Window_Manager()
{
	loggerWM = Logger::GetLogger();
}

Window_Manager::~Window_Manager()
{
	for each(Window* W in Windows)
	{
		if (W != NULL) {
			delete W;
		}
		
	}

	//delete myWindow_Manager;
}

void Window_Manager::createWindow(std::string title)
{
	Window* myWindow = new Window(title);
	Windows.push_back(myWindow);
}

/**
* Function:	Window_Manager::getWindow()
* Description: Provides a window with specified name for whichever function needs it, will create one if needed.
*/
Window* Window_Manager::getWindow(std::string schermnaam)
{
	for(std::vector<Window*>::iterator i = Windows.begin(); i != Windows.end(); ++i)
	{
		Window* currentWindow = *i;
		if (currentWindow->getSchermNaam().compare(schermnaam) == 0)
		{
			return currentWindow; //If a window is found with the name, return this one.
		}
	}
	//Else create a new window, and return this one
	createWindow(schermnaam);
	return getWindow(schermnaam);
}

/**
* Function:	Window_Manager::getWindow()
* Description: Searching for a window with the specified HWND and returns it. Returns null if nothing is found.
*/
Window* Window_Manager::getWindow(HWND hwnd)
{
	for (std::vector<Window*>::iterator i = Windows.begin(); i != Windows.end(); ++i)
	{
		Window* currentWindow = *i;
		if (currentWindow->getHWND() == hwnd)
		{
			return currentWindow; //If a window is found with the specified HWND, return this one.
		}
	}
	return NULL;
}

/**
* Function:	Window_Manager::LogActiveWindow()
* Description: Asks the OS which window has is active and logs its name to the log file, can log windows beyond project scope.
*/
void Window_Manager::LogActiveWindow()
{
	HWND activeWindow = GetForegroundWindow();
	std::string convertedHandleString = EngineTextHandling::HwndToString(activeWindow);
	loggerWM->WriteToFile(Error, convertedHandleString);
}

/**
* Function:	Window_Manager::getActiveWindow()
* Description: Checks which window says its active, and returns this window. If no active window is found, returns null.
*/
Window* Window_Manager::getActiveWindow()
{
	for (std::vector<Window*>::iterator i = Windows.begin(); i != Windows.end(); ++i)
	{
		Window* currentWindow = *i;
		currentWindow->updateWindow();
		if (currentWindow->getActiveState() == true)
		{
			return currentWindow;
		}
	}
	loggerWM->WriteToFile(Error, "No active Window found");
	return NULL;
}

/**
* Function:	Window_Manager::DestroyWindow()
* Description: Destroys the specified window, removes it from the window pool as well.
*/
void Window_Manager::DestroyWindow(Window* DeathRowWindow)
{
	for (std::vector<Window*>::iterator i = Windows.begin(); i != Windows.end(); ++i)
	{
		Window* currentWindow = *i;
		if (currentWindow == DeathRowWindow)
		{
			Windows.erase(i);
			DeathRowWindow->closeWindow();
			delete DeathRowWindow;
			break;
		}
	}
}