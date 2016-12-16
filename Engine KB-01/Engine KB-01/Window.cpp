#include "Window.h"

Window::Window(std::string naam, int startX, int startY, int wWidth, int wHeight)
{
	loggerW = Logger::GetLogger();
	hwnd = NULL;
	windowClass = L"Engine KB-01";
	windowName = naam;
	startingX = startX;
	startingY = startY;
	windowWidth = wWidth;
	windowHeight = wHeight;
	createWindow();		
}

Window::~Window()
{

}

/**
* Function:	Window::ShowMessagebox()
* Description: Functionality to show a message box with a certain message.
*/
int Window::ShowMessagebox(std::string body, std::string title, UINT uType)
{
	std::wstring stemp = std::wstring(body.begin(), body.end());
	LPCWSTR bodyLP = stemp.c_str();
	std::wstring stemp2 = std::wstring(title.begin(), title.end());
	LPCWSTR titleLP = stemp2.c_str();
	int msgboxID = MessageBox(hwnd, bodyLP, titleLP, uType);
	return msgboxID;
}

/**
* Function:	Window::updateWindow()
* Description: Checks whether the window has received an OS message. If so allows it to be processed
*/
void Window::updateWindow(){
	MSG msg = { 0 };
	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	UpdateWindow( hwnd );
}

/**
* Function:	Window::createWindow()
* Description: Creates a window with the specified name, starting coordinates, height and width.
*/
void Window::createWindow()
{
	std::wstring stemp = std::wstring(windowName.begin(), windowName.end());
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
                              WS_OVERLAPPEDWINDOW, startingX, startingY, windowWidth, windowHeight,
                              NULL, NULL, wc.hInstance, this );
	SetWindowText(hwnd, windowNaamLPCWSTR);
	ShowWindow(hwnd, SW_SHOWDEFAULT);
	Window::updateWindow();
}

/**
* Function:	Window::getHWND()
* Description: Returns the HWND value of the window
*/
HWND Window::getHWND()
{
	return hwnd;
}

/**
* Function:	Window::setActiveState()
* Description: Sets the activestate of the window, variable is used to check internally which window is active. Instead of relying on the OS for it.
*/
void Window::setActiveState(bool state)
{
	isActiveWindow = state;
}

/**
* Function:	Window::getActiveState()
* Description: Gets the activestate of the window, variable is used to check internally which window is active. Instead of relying on the OS for it.
*/
bool Window::getActiveState()
{
	return isActiveWindow;
}

/**
* Function:	Window::getWindowName()
* Description: Gets the windowName
*/
std::string Window::getWindowName()
{
	return windowName;
}

/**
* Function:	Window::closeWindow()
* Description: closes the Window
*/
void Window::closeWindow()
{
	DestroyWindow(hwnd);
}

/**
* Function:	Window::WindowProc()
* Description: The Windowproc, where the OS msgs are defined and determined what needs to be done with them. 
* A window pointer is used to be able to set variables instead of being tied down by the laws of man
*/
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

/**
* Function:	Window::_WindowProc()
* Description: The sneaky Windowproc, where the usefull OS msgs are defined and determined what needs to be done with them
*/
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