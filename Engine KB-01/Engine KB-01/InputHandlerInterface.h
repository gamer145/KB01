#ifndef INPUTHANDLERINTERFACE_H
#define INPUTHANDLERINTERFACE_H

#include "EngineKB01Definitions.h"
#include "Window.h"
#include "Window_Manager.h"
#include "Logger.h"

class InputHandlerInterface
{
public:
	//Constructor
	InputHandlerInterface();

	//Destructor
	~InputHandlerInterface();

	//Attempt to initialize the InputHandler object, virtual function of interface
	virtual HRESULT InitInputHandler(Window* argWindow) = 0;

	// Checks wether one of the known listeners knows the action that is given as an argument.
	// Then the listener itself will fill out the float value, which is then passed on to the core logic asking about the action.
	virtual float getAction(EACTION action) = 0;
};

#endif