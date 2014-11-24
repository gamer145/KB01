#ifndef LISTENERINTERFACE_H 
#define LISTENERINTERFACE_H 

#include "EngineKB01Definitions.h"
#include "Window.h"
#include "Logger.h"

class ListenerInterface
{
public:
	ListenerInterface();
	~ListenerInterface();
	virtual bool getAction(EACTION action, float& value) = 0;
	virtual void SaveReleaseDevice() = 0;
};

#endif
