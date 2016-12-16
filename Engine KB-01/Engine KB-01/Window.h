#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <string>
#include <Windows.h>
#include "Logger.h"

class Window
{
	public:
		Window(std::string naam, int startX, int startY, int wWidth, int wHeight); //Constructor, in the constructor the createWindow() function is called and the window dimensions are set
		~Window(); //Deconstructor
		int Window::ShowMessagebox(std::string body, std::string title, UINT uType); //A messagebox that can be used to show a message to the user
		void updateWindow(); //Updates the window by checking for MSGprocs from the OS and dealing with them
		void closeWindow();	//Closes the window	
		HWND getHWND(); //Returns the windows HWND for identification purposes
		std::string getWindowName(); //Returns the name of the window. In the current OS iteration this name is always the same as the title of the window
		void Window::setActiveState(bool state); //Sets the activeState of the window
		bool Window::getActiveState(); //Returns the activeState of the window
	private:
		void createWindow(); //Creates the window, called internally in the constructor
		static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam); //The required MSGProc
		LRESULT Window::_WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam); //The usefull MSGproc
		HWND hwnd; //The window's HWND, used by the OS for identification and used internally a lot in various functions that need to be hooked to a window
		std::string windowName; //The name of the window, same as the title
		bool isActiveWindow; //The activeState
		Logger* loggerW; //The Window Logger, used to log messages to the log file
		LPCWSTR windowClass; //Windowclass, used to determine of which class the windows are a part of
		int startingX, startingY, windowWidth, windowHeight; //The starting dimensions of the window
};

#endif