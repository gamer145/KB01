#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <string>
#include <Windows.h> //Needed for showing a MessageBox
#include "Logger.h"

class Window
{
	public:
		Window(std::string naam);
		int Window::ShowMessagebox(std::string body, std::string title, UINT uType);
		void createWindow(std::string windowNaam);
		void updateWindow();
		void closeWindow();		
		HWND getHWND();
		std::string getSchermNaam();
		LPCWSTR getWindowClass();
		void setWindowClass(LPCWSTR newClassName);
		void Window::setActiveState(bool state);
		bool Window::getActiveState();

	private:
		static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
		LRESULT Window::_WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		HWND hwnd;
		std::string schermnaam;
		bool isActiveWindow;
		Logger* loggerW;
		LPCWSTR windowClass;
};

#endif