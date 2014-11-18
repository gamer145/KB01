#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <string>
#include <Windows.h> //Needed for showing a MessageBox

class Window
{
	public:
		Window(std::string naam);
		int Window::ShowMessagebox(std::string body, std::string title, UINT uType);
		void createWindow(std::string windowNaam);
		void updateWindow();
		void closeWindow();
		LRESULT CALLBACK MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
		HWND getHWND();
		std::string getSchermNaam();
		void Window::setRenderState(bool state);
		bool Window::getRenderState();
		bool Window::isThisActiveWindow();
	private:
		HWND hwnd;
		std::string schermnaam;
		bool RenderState;
		bool isActiveWindow;
};

#endif