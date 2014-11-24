#ifndef INPUTHANDLERINTERFACE_H
#define INPUTHANDLERINTERFACE_H

#include "EngineKB01Definitions.h"
#include "Window.h"
#include "Window_Manager.h"
#include "Logger.h"

class InputHandlerInterface
{
public:
	InputHandlerInterface();
	~InputHandlerInterface();
	virtual HRESULT InitInputHandler(Window* argWindow) = 0;
};

#endif