#ifndef MOUSELISTENER_H 
#define MOUSELISTENER_H 

//Tell DirectInput which version we want
#define DIRECTINPUT_VERSION 0x0800

//Include the necessary files
#include <dinput.h>
#include "ListenerInterface.h"

class MouseListener
{
public:
	//Constructor
	MouseListener(Window* argWindow, LPDIRECTINPUT8 argDInput); 

	//Destructor
	~MouseListener();

	//Asks the listener whether it knows the action or not and if the conditions have been met for it
	//Argument value will be filled inside the function, and be used if there is an answer
	bool getAction(EACTION action, float& value);	

	//Always called inside the destructor
	//Clears up the device for monitoring	
	void SaveReleaseDevice();	

	//Changes how much mouse movement translates into in game movement
	void setMouseAcceleration(float newAcceleration); 
	
private:
	LPDIRECTINPUT8          dInput;
	LPDIRECTINPUTDEVICE8	dDeviceMouse;
	Window* window; 
	DIPROPDWORD dipdw;

	//The mouse struct after its filled with values given by OS
	MouseStruct bufferedMouse;	

	//The previous cycles mouseStruct, used to determine wether something has changed.
	MouseStruct oldMouseState;

	//Value used to calculate the internal changes made by a mouse positional change. 
	//The higher the acceleration, the more impact a single position of mouse movement has.
	float mouseAcceleration;

	//The logger used within the MouseListener
	Logger* loggerM; 

	//Checks wether the mousewheel has scrolled or not, and in which direction.
	long getMousewheel(); 

	//Checks wether a given button is down. See EngineDefinitions for which button is which
	bool isButtonDown(int button, MouseStruct mouse); 

	//Initialize the mouse
	bool InitMouse(); 

	//Get the current mouse values
	MouseStruct GetMouseInput(); 

	//Links the custom mouse struct to the one provided by the OS
	void SetTheMouseBuffer(); 

	//Resets the mouse structs values
	void ResetMouseStruct(); 
};

#endif