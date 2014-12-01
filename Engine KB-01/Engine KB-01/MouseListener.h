#ifndef MOUSELISTENER_H 
#define MOUSELISTENER_H 

//Tell DirectInput which version we want
#define DIRECTINPUT_VERSION 0x0800

//Include the necessary files
#include <dinput.h>
#include "Structs.h"
#include "ListenerInterface.h"

class MouseListener
{
public:
	MouseListener(Window* argWindow, LPDIRECTINPUT8 argDInput); //Constructor
	~MouseListener(); //Destructor
	bool getAction(EACTION action, float& value); //Asks the listener whether it knows the action or not and if the conditions have been met for it
	void SaveReleaseDevice(); //Release mouse
	long getMousewheel();
	bool isButtonDown(int button);
	void setMouseAcceleration(float newAcceleration);
	
private:
	LPDIRECTINPUT8          dInput;
	LPDIRECTINPUTDEVICE8	dDeviceMouse;
	Window* window;
	DIPROPDWORD dipdw;
	MouseStruct bufferedMouse;
	MouseStruct oldMouseState;
	float mouseAcceleration;
	Logger* loggerM;

	bool InitMouse(); //Initialize the mouse
	MouseStruct GetMouseInput(); //Get the current mouse values
	void SetTheMouseBuffer(); //?
	void ResetMouseStruct();
};

#endif