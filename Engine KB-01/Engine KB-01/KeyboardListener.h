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
	//Constructor
	KeyboardListener(Window* argWindow, LPDIRECTINPUT8 argDInput); 

	//Destructor
	~KeyboardListener();

	//Initializes the keyboard
	bool InitKeyboard(); 

	//Asks the listener whether it knows the action or not and if the conditions have been met for it
	//Argument value will be filled inside the function, and be used if there is an answer
	bool getAction(EACTION action, float& value);

	//Always called inside the destructor
	//Clears up the device for monitoring
	void SaveReleaseDevice();	

	//Method to see if the keyboardbuffer can be red or that a aquire is needed
	bool ProcessKBInput(byte argKeyIsPressed);

	//Function that checks whether the program can connect to the keyboard or not
	bool DoAcquire(); 
private:
	//DirectXinput version
	LPDIRECTINPUT8 dInput; 

	//The input device
	LPDIRECTINPUTDEVICE8 dDeviceKeyboard; 

	//The key buffer
	char keyBuffer[256];

	//The connected window
	Window* window;

	//The connected logger
	Logger* loggerKB;
};

#endif //Headerguard