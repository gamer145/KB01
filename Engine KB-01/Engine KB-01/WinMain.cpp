#define WIN32_LEAN_AND_MEAN

#include <Windows.h>

bool initMainWindow(HINSTANCE, int);
LRESULT CALLBACK MsgProc(HWND, UINT, WPARAM, LPARAM);

const int HEIGHT = 600;
const int WIDTH = 800;
HWND hwnd1 = NULL;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreviousInstance, LPSTR lpCmdLine, int nCmdShow)
{
	hInstance = hInstance;
	nCmdShow = nCmdShow;

	if(!initMainWindow(hInstance, nCmdShow))
		return(1);

	MSG msg = {0};
	while(WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	
	return static_cast<int>(msg.wParam);
}

bool initMainWindow(HINSTANCE hInstance, int nCmdShow)
{
	WNDCLASSEXA wcex;
	ZeroMemory(&wcex, sizeof(WNDCLASSEX));
	wcex.cbClsExtra = 0; 
	wcex.cbWndExtra = 0;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.hInstance = hInstance;
	wcex.lpfnWndProc = MsgProc;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_CROSS); 
	wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); 
	wcex.lpszClassName = "WIN32WINDOWCLASS";
	wcex.lpszMenuName = NULL; 
	wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION); 

	if(!RegisterClassExA(&wcex))
		return false;

		hwnd1 = CreateWindowA(
			"WIN32WINDOWCLASS",
			"Window Window",
			WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION,
			GetSystemMetrics(SM_CXSCREEN)/2 - WIDTH / 2,
			GetSystemMetrics(SM_CYSCREEN)/2 - HEIGHT / 2,
			WIDTH,
			HEIGHT,
			(HWND)NULL,
			(HMENU)NULL,
			hInstance,
			(LPVOID*)NULL);
			
			if (!hwnd1)
			return false;

			ShowWindow(hwnd1, nCmdShow);
	return true;
}

LRESULT CALLBACK MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	
	case WM_CHAR:
		switch(wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			return 0;

		case VK_RETURN:
			PostQuitMessage(0);
			return 0;
		}
		return 0;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}