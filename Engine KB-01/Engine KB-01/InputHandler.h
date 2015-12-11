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
	float getAction(EACTION action);	// Checks wether one of the known listeners knows the action that is given as an argument.
										// Then the listener itself will fill out the float value, which is then passed on to the core logic asking about the action.

private:
	void pollWhisperers(); //Lets whisperers poll their devices. Used in getAction.
	MouseListener* mousewhisperer; //Pointer to MouseListener
	KeyboardListener* keyboardwhisperer; //Pointer to KeyboardListener
	LPDIRECTINPUT8 dInput; //Pointer to DirectInput
	Logger* loggerIH; //Pointer to Logger
	HRESULT InitDInput(); //The method used in InitInputHandler
};
#endif