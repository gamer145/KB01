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
	Window_Manager(); 
	~Window_Manager();
	Window* getWindow(std::string schermnaam);
	Window* getWindow(HWND hwnd);
	Window* getActiveWindow();
	void LogActiveWindow();
	void DestroyWindow(Window* DeathRowWindow);
private:
	std::vector<Window*> Windows;
	Logger* loggerWM;
	void createWindow(std::string title);
};

#endif