#ifndef INPUTHANDLER_H //Headerguard
#define INPUTHANDLER_H //Headerguard

//Tell DirectInput which version we want
#define DIRECTINPUT_VERSION 0x0800

//Include the necessary files
#include "KeyboardListener.h"
#include "Logger.h"
#include "MouseListener.h"
#include "Window.h"
#include "Window_Manager.h"

class InputHandler
{
public:
	InputHandler(Window* argWindow); //Constructor
	~InputHandler(); //Destructor
	bool InitDInput(); //Attempt to initialize DirectInput, returns the result in a boolean
	MouseListener* mousewhisperer; //Pointer to MouseListener
	KeyboardListener* keyboardwhisperer; //Pointer to KeyboardListener
private:

	LPDIRECTINPUT8 dInput; //Pointer to DirectInput
	Logger* loggerIH; //Pointer to Logger
};
#endif //Headerguard