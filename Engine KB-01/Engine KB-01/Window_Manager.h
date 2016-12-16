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
	Window_Manager(); //Constructor, default window Values are set in here
	~Window_Manager(); //Destructor
	Window* getWindow(std::string schermnaam); //Looks for a window with specified name, if none exists, creates one with specified name and default window values.
	Window* getWindow(std::string schermnaam, int startX, int startY, int wWidth, int wHeight); //Looks for a window with specified name, if none exists, creates one with specified name and specified window values.
	Window* getWindow(HWND hwnd); //Looks for a window with specified HWND
	Window* getActiveWindow(); //Looks through all available windows for the active one, the one with activeState set to true
	void LogActiveWindow(); //Asks the OS what the active window is, and logs it to the logfile
	void setDefaultX(int newX); //Sets the DefaultWindow X starting position
	void setDefaultY(int newY); //Sets the DefaultWindow Y starting position
	void setDefaultWidth(int newWidth); //Sets the DefaultWindow Width
	void setDefaultHeight(int newHeight); //Sets the DefaultWindow Height
	void DestroyWindow(Window* DeathRowWindow); //Murders the window
private:	
	std::vector<Window*> Windows; //Collection of windows
	Logger* loggerWM; //The logger file used by the WindowManager
	void createWindow(std::string title, int startX, int startY, int wWidth, int wHeight); //The function used to create windows, called in the getWindow function
	int defaulWindowtX, defaultWindowY, defaultWindowWidth, defaultWindowHeight; //Default window values
};

#endif