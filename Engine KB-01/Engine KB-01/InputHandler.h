#ifndef INPUTHANDLER_H 
#define INPUTHANDLER_H 

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
	MouseListener* getMouseListener();
	KeyboardListener* getKeyBoardListener();

private:
	MouseListener* mousewhisperer; //Pointer to MouseListener
	KeyboardListener* keyboardwhisperer; //Pointer to KeyboardListener
	LPDIRECTINPUT8 dInput; //Pointer to DirectInput
	Logger* loggerIH; //Pointer to Logger
};
#endif