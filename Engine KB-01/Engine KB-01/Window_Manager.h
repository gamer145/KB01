#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include <iostream>
#include <string>
#include <vector>
#include "Window.h"
#include "Logger.h"
#include "EngineTextHandling.h"

class Window_Manager
{
public:
	//Constructor, default window Values are set in here
	Window_Manager(); 

	//Destructor
	~Window_Manager();

	//Looks for a window with specified name, if none exists, creates one with specified name and default window values.
	Window* getWindow(std::string schermnaam);

	//Looks for a window with specified name, if none exists, creates one with specified name and specified window values.
	Window* getWindow(std::string schermnaam, int startX, int startY, int wWidth, int wHeight); 

	//Looks for a window with specified HWND
	Window* getWindow(HWND hwnd); 

	//Looks through all available windows for the active one, the one with activeState set to true
	Window* getActiveWindow(); 

	//Asks the OS what the active window is, and logs it to the logfile
	void LogActiveWindow(); 

	//Sets the DefaultWindow X starting position
	void setDefaultX(int newX);

	//Sets the DefaultWindow Y starting position
	void setDefaultY(int newY); 

	//Sets the DefaultWindow Width
	void setDefaultWidth(int newWidth); 

	//Sets the DefaultWindow Height
	void setDefaultHeight(int newHeight); 

	//Murders the window
	void DestroyWindow(Window* DeathRowWindow); 
private:	

	//Collection of windows
	std::vector<Window*> Windows;

	//The logger file used by the WindowManager
	Logger* loggerWM; 

	//The function used to create windows, called in the getWindow function
	void createWindow(std::string title, int startX, int startY, int wWidth, int wHeight); 

	//Default window values
	int defaulWindowtX, defaultWindowY, defaultWindowWidth, defaultWindowHeight; 
};

#endif