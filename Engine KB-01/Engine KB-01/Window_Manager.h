#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include <iostream>
#include <string>
#include <vector>
#include "Window.h"

class Window_Manager
{
public:
	Window_Manager(); 
	~Window_Manager();
	Window* getWindow(std::string schermnaam);
	void updateWindows();
private:
	std::vector<Window*> Windows;
	static Window_Manager* myWindow_Manager;
	void createWindow(std::string title);
};

#endif