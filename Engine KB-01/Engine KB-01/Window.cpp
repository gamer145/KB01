#include "Window.h"

LRESULT CALLBACK MsgProc(HWND, UINT, WPARAM, LPARAM);
const int HEIGHT = 600;
const int WIDTH = 800;
HWND hwnd = NULL;
std::string schermnaam;
bool isActiveWindow = false;

Window::Window(std::string naam)
{
	createWindow(naam);
	schermnaam = naam;
	RenderState = false;
	isActiveWindow = true;
}

int Window::ShowMessagebox(std::string body, std::string title, UINT uType)
{
	std::wstring stemp = std::wstring(body.begin(), body.end());
	LPCWSTR bodyLP = stemp.c_str();
	std::wstring stemp2 = std::wstring(title.begin(), title.end());
	LPCWSTR titleLP = stemp2.c_str();
	int msgboxID = MessageBox(hwnd, bodyLP, titleLP, uType);
	return msgboxID;
}

void Window::updateWindow(){
	MSG msg = {0};
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		UpdateWindow( hwnd );
}

void Window::createWindow(std::string windowNaam)
{
	std::wstring stemp = std::wstring(windowNaam.begin(), windowNaam.end());
	LPCWSTR windowNaamLPCWSTR = stemp.c_str();

	WNDCLASSEXW wc =
    {
        sizeof( WNDCLASSEX ), CS_CLASSDC, ::MsgProc, 0L, 0L,
        GetModuleHandle( NULL ), NULL, NULL, NULL, NULL,
        L"Engine KB-01", NULL
    };
    RegisterClassExW( &wc );
   
	hwnd = CreateWindow( L"Engine KB-01", windowNaamLPCWSTR,
                              WS_OVERLAPPEDWINDOW, 100, 100, 600, 600,
                              NULL, NULL, wc.hInstance, NULL );
	ShowWindow(hwnd, 1);
	Window::updateWindow();
}

HWND Window::getHWND()
{
	return hwnd;
}

void Window::setRenderState(bool state)
{
	RenderState = state;
}

bool Window::getRenderState()
{
	return RenderState;
}

bool Window::isThisActiveWindow()
{
	return isActiveWindow;
}

std::string Window::getSchermNaam()
{
	return schermnaam;
}

void closeWindow()
{
	exit(0);
}

LRESULT CALLBACK MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HWND activeWindow = GetForegroundWindow();
	switch(msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_ACTIVATE:
		if (wParam == WA_INACTIVE)
		{
			isActiveWindow = false;
		} else if (wParam == WA_ACTIVE || wParam == WA_CLICKACTIVE)
		{
			isActiveWindow = true;
		}
		return 0;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}