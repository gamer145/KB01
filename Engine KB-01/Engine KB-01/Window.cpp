#include "Window.h"

Window::Window(std::string naam)
{
	loggerW = Logger::GetLogger();
	hwnd = NULL;
	windowClass = L"Engine KB-01";
	createWindow(naam);
	schermnaam = naam;	
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
	MSG msg = { 0 };
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
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof wc;
	wc.hInstance = GetModuleHandle(NULL);
	wc.style = CS_CLASSDC;
	wc.lpfnWndProc = WindowProc;
	wc.lpszClassName = windowClass;

	if (!GetClassInfoEx(wc.hInstance, windowClass, &wc))
	{	
		if (!RegisterClassEx(&wc))
		{
			loggerW->WriteToFile(Error, "Window Registration Failed!");
		}
	}
   
	hwnd = CreateWindowEx(WS_EX_APPWINDOW, windowClass, windowNaamLPCWSTR,
                              WS_OVERLAPPEDWINDOW, 100, 100, 600, 600,
                              NULL, NULL, wc.hInstance, this );
	SetWindowText(hwnd, windowNaamLPCWSTR);
	ShowWindow(hwnd, SW_SHOWDEFAULT);
	Window::updateWindow();
}

HWND Window::getHWND()
{
	return hwnd;
}

void Window::setActiveState(bool state)
{
	isActiveWindow = state;
}

bool Window::getActiveState()
{
	return isActiveWindow;
}

LPCWSTR Window::getWindowClass()
{
	return windowClass;
}

void Window::setWindowClass(LPCWSTR newClassName)
{
	windowClass = newClassName;
}

std::string Window::getSchermNaam()
{
	return schermnaam;
}

void Window::closeWindow()
{
	exit(0);
}

LRESULT Window::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (WM_NCCREATE == uMsg)
	{
		SetLastError(0);
		if (!SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)((CREATESTRUCT*)lParam)->lpCreateParams))
		{
			if (GetLastError() != 0)
				return FALSE;
		}
		return TRUE;
	}

	return ((Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA))->_WindowProc(hwnd, uMsg, wParam, lParam);
}

LRESULT Window::_WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(S_OK);
		break;
	case WM_ACTIVATE:
		if (wParam == WA_INACTIVE)
		{
			isActiveWindow = false;
		}
		else if (wParam == WA_ACTIVE || wParam == WA_CLICKACTIVE)
		{
			isActiveWindow = true;
		}
		break;
	default:
		return DefWindowProcW(hwnd, uMsg, wParam, lParam);
	}
	return FALSE;
}

/*
LRESULT CALLBACK Window::WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_ACTIVATE:
		if (wParam == WA_INACTIVE)
		{
			//isActiveWindow = false;
		} else if (wParam == WA_ACTIVE || wParam == WA_CLICKACTIVE)
		{
			//isActiveWindow = true;
		}
		return 0;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}
*/