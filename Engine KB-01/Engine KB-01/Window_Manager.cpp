#include "Window_Manager.h"

Window_Manager::Window_Manager()
{
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
	
void Window_Manager::updateWindows()
{
	for(std::vector<Window*>::iterator i = Windows.begin(); i != Windows.end(); ++i)
	{
		Window* currentWindow = *i;
		currentWindow->updateWindow();
	}
}