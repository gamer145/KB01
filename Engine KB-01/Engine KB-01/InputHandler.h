#ifndef INPUTHANDLER_H 
#define INPUTHANDLER_H 

//Tell DirectInput which version we want
#define DIRECTINPUT_VERSION 0x0800

//Include the necessary files
#include "KeyboardListener.h"

#include "MouseListener.h"

#include "InputHandlerInterface.h"

class InputHandler : public InputHandlerInterface
{
public:
	InputHandler(); //Constructor
	~InputHandler(); //Destructor
	HRESULT InitInputHandler(Window* argWindow); //Attempt to initialize the InputHandler object
	float getAction(EACTION action);
private:
	MouseListener* mousewhisperer; //Pointer to MouseListener
	KeyboardListener* keyboardwhisperer; //Pointer to KeyboardListener
	LPDIRECTINPUT8 dInput; //Pointer to DirectInput
	Logger* loggerIH; //Pointer to Logger
	HRESULT InitDInput(); //The method used in InitInputHandler
};
#endif