#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <string>
#include <Windows.h>
#include "Logger.h"

class Window
{
	public:
		//Constructor, in the constructor the createWindow() function is called and the window dimensions are set
		Window(std::string naam, int startX, int startY, int wWidth, int wHeight); 

		//Deconstructor
		~Window();

		//A messagebox that can be used to show a message to the user
		int Window::ShowMessagebox(std::string body, std::string title, UINT uType);

		//Updates the window by checking for MSGprocs from the OS and dealing with them
		void updateWindow(); 

		//Closes the window	
		void closeWindow();	

		//Returns the windows HWND for identification purposes
		HWND getHWND(); 

		//Returns the name of the window. In the current OS iteration this name is always the same as the title of the window
		std::string getWindowName(); 

		//Sets the activeState of the window
		void Window::setActiveState(bool state);

		//Returns the activeState of the window
		bool Window::getActiveState(); 
	private:
		//Creates the window, called internally in the constructor
		void createWindow(); 

		//The required MSGProc
		static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam); 

		//The usefull MSGproc
		LRESULT Window::_WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam); 

		//The window's HWND, used by the OS for identification and used internally a lot in various functions that need to be hooked to a window
		HWND hwnd; 

		//The name of the window, same as the title
		std::string windowName; 

		//The activeState
		bool isActiveWindow;

		//The Window Logger, used to log messages to the log file
		Logger* loggerW; 

		//Windowclass, used to determine of which class the windows are a part of
		LPCWSTR windowClass; 

		//The starting dimensions of the window
		int startingX, startingY, windowWidth, windowHeight; 
};

#endif