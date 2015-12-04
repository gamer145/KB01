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
	MouseListener(Window* argWindow, LPDIRECTINPUT8 argDInput); //Constructor
	~MouseListener(); //Destructor
	bool getAction(EACTION action, float& value); //Asks the listener whether it knows the action or not and if the conditions have been met for it
	void SaveReleaseDevice(); //Release mouse		
	void setMouseAcceleration(float newAcceleration); 
	
private:
	LPDIRECTINPUT8          dInput;
	LPDIRECTINPUTDEVICE8	dDeviceMouse;
	Window* window;
	DIPROPDWORD dipdw;
	MouseStruct bufferedMouse;	//The mouse struct after its filled with values given by OS
	MouseStruct oldMouseState;	//The previous cycles mouseStruct, used to determine wether something has changed.
	float mouseAcceleration;	//Value used to calculate the internal changes made by a mouse positional change. 
								//The higher the acceleration, the more impact a single position of mouse movement has.
	Logger* loggerM;			

	long getMousewheel(); //Checks wether the mousewheel has scrolled or not, and in which direction.
	bool isButtonDown(int button, MouseStruct mouse); //Checks wether a given button is down. See EngineDefinitions for which button is which
	bool InitMouse(); //Initialize the mouse
	MouseStruct GetMouseInput(); //Get the current mouse values
	void SetTheMouseBuffer(); //Links the custom mouse struct to the one provided by the OS
	void ResetMouseStruct(); //Resets the mouse structs values
};

#endif