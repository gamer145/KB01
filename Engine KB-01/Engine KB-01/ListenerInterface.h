#ifndef LISTENERINTERFACE_H 
#define LISTENERINTERFACE_H 

#include "EngineKB01Definitions.h"
#include "Window.h"
#include "Logger.h"

class ListenerInterface
{
public:
	//Constructor
	ListenerInterface(); 

	//Destructor
	~ListenerInterface(); 

	//Required function in a listener. Returns a bool whether there is an answer or not
	//Argument value will be filled inside the function, and be used if there is an answer
	virtual bool getAction(EACTION action, float& value) = 0;

	//Required function in a listener. Needs to be specified for the device, and always called inside the destructor
	//Clears up the device for monitoring
	virtual void SaveReleaseDevice() = 0;	
};

#endif
