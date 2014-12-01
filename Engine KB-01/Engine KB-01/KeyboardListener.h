#ifndef KEYBOARDLISTENER_H 
#define KEYBOARDLISTENER_H 

//Tell DirectInput which version we want
#define DIRECTINPUT_VERSION 0x0800

//Include the necessary files
#include <dinput.h>
#include "ListenerInterface.h"

class KeyboardListener
{
public:
	KeyboardListener(Window* argWindow, LPDIRECTINPUT8 argDInput);
	~KeyboardListener();
	bool  InitKeyboard();
	bool getAction(EACTION action, float& value); //Asks the listener whether it knows the action or not and if the conditions have been met for it
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