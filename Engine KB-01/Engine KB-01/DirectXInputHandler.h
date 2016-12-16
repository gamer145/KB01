#ifndef INPUTHANDLER_H 
#define INPUTHANDLER_H 

//Tell DirectInput which version we want
#define DIRECTINPUT_VERSION 0x0800

//Include the necessary files
#include "KeyboardListener.h"

#include "MouseListener.h"

#include "InputHandlerInterface.h"

class DirectXInputHandler : public InputHandlerInterface
{
public:
	//Constructor
	DirectXInputHandler();

	//Destructor
	~DirectXInputHandler(); 

	//Attempt to initialize the DirectXInputHandler object
	HRESULT InitInputHandler(Window* argWindow); 

	// Checks wether one of the known listeners knows the action that is given as an argument.
	// Then the listener itself will fill out the float value, which is then passed on to the core logic asking about the action.
	float getAction(EACTION action);	

private:

	//Pointer to MouseListener
	MouseListener* mousewhisperer; 

	//Pointer to KeyboardListener
	KeyboardListener* keyboardwhisperer;

	//Pointer to DirectInput
	LPDIRECTINPUT8 dInput; 

	//Pointer to Logger
	Logger* loggerIH; 

	//Method used in InitInputHandler
	HRESULT InitDInput(); 
};
#endif