#include "Window_Manager.h"

Window_Manager::Window_Manager()
{
	loggerWM = Logger::GetLogger();
	int defaulWindowtX = 100;
	int defaultWindowY = 100;
	int defaultWindowWidth = 600;
	int defaultWindowHeight = 600;
}

Window_Manager::~Window_Manager()
{
	for each(Window* W in Windows)
	{
		if (W != NULL) {
			delete W;
		}		
	}
}

/**
* Function:	Window_Manager::createWindow()
* Description: Used internally to talk to the Window.cpp class, just creates a window and adds it to the window collection.
*/
void Window_Manager::createWindow(std::string title, int startX, int startY, int wWidth, int wHeight)
{
	Window* myWindow = new Window(title, startX, startY, wWidth, wHeight);
	Windows.push_back(myWindow);
}

/**
* Function:	Window_Manager::getWindow()
* Description: Provides a window with specified name for whichever function needs it, will create one using default values if needed.
*/
Window* Window_Manager::getWindow(std::string title)
{
	for(std::vector<Window*>::iterator i = Windows.begin(); i != Windows.end(); ++i)
	{
		Window* currentWindow = *i;
		if (currentWindow->getWindowName().compare(title) == 0)
		{
			return currentWindow; //If a window is found with the name, return this one.
		}
	}
	//Else create a new window, and return this one

	createWindow(title, 100, 100, 600, 600);
	return getWindow(title);
}

/**
* Function:	Window_Manager::getWindow()
* Description: Provides a window with specified name for whichever function needs it, will create one using specified values if needed.
*/
Window* Window_Manager::getWindow(std::string title, int startX, int startY, int wWidth, int wHeight)
{
	for (std::vector<Window*>::iterator i = Windows.begin(); i != Windows.end(); ++i)
	{
		Window* currentWindow = *i;
		if (currentWindow->getWindowName().compare(title) == 0)
		{
			return currentWindow; //If a window is found with the name, return this one.
		}
	}
	//Else create a new window, and return this one
	createWindow(title, startX, startY, wWidth, wHeight);
	return getWindow(title);
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

/**
* Function:	Window_Manager::setDefaultX()
* Description: Sets the default X position for new windows
*/
void Window_Manager::setDefaultX(int newX)
{
	defaulWindowtX = newX;
}


/**
* Function:	Window_Manager::setDefaultY()
* Description: Sets the default Y position for new windows
*/
void Window_Manager::setDefaultY(int newY)
{
	defaultWindowY = newY;
}

/**
* Function:	Window_Manager::setDefaultWidth()
* Description: Sets the default Window Width
*/
void Window_Manager::setDefaultWidth(int newWidth)
{
	defaultWindowWidth = newWidth;
}

/**
* Function:	Window_Manager::setDefaultHeight()
* Description: Sets the default Window Heigth
*/
void Window_Manager::setDefaultHeight(int newHeight)
{
	defaultWindowHeight = newHeight;
}