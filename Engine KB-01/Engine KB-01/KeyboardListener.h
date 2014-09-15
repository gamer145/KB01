#ifndef KEYBOARDLISTENER_H //Headerguard
#define KEYBOARDLISTENER_H //Headerguard

//Tell DirectInput which version we want
#define DIRECTINPUT_VERSION 0x0800

//Include the necessary files
#include <dinput.h>
#include "Logger.h"
#include "Window.h"

class KeyboardListener
{
public:
	KeyboardListener(Window* argWindow, LPDIRECTINPUT8 argDInput);
	~KeyboardListener();
	bool  InitKeyboard();
	void SaveReleaseDevice();
	bool ProcessKBInput(byte argKeyIsPressed);
	bool DoAcquire();
private:
	LPDIRECTINPUT8 dInput; 
	LPDIRECTINPUTDEVICE8 dDeviceKeyboard; 
	char keyBuffer[256];
	Window* window;
	Logger* loggerKB;
};

#endif //Headerguard