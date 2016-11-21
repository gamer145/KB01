#ifndef LISTENERINTERFACE_H 
#define LISTENERINTERFACE_H 

#include "EngineKB01Definitions.h"
#include "Window.h"
#include "Logger.h"

class ListenerInterface
{
public:
	ListenerInterface(); //Constructor
	~ListenerInterface(); //Destructor
	virtual bool getAction(EACTION action, float& value) = 0;	//Required function in a listener. Returns a bool whether there is an answer or not
																//Argument value will be filled inside the function, and be used if there is an answer
	virtual void SaveReleaseDevice() = 0;	//Required function in a listener. Needs to be specified for the device, and always called inside the destructor
											//Clears up the device for monitoring
};

#endif
