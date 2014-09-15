#ifndef MOUSELISTENER_H //Headerguard
#define MOUSELISTENER_H //Headerguard

//Tell DirectInput which version we want
#define DIRECTINPUT_VERSION 0x0800

//Include the necessary files
#include <dinput.h>
#include "Logger.h"
#include "Structs.h"
#include "Window.h"

class MouseListener
{
public:
	MouseListener(Window* argWindow, LPDIRECTINPUT8 argDInput); //Constructor
	~MouseListener(); //Destructor
	void SaveReleaseDevice(); //Release mouse
	long getXPos();
	long getYPos();
	long getMousewheel();
	bool isButtonDown(int button);
private:
	LPDIRECTINPUT8          dInput;
	LPDIRECTINPUTDEVICE8	dDeviceMouse;
	Window* window;
	DIPROPDWORD dipdw;
	MouseStruct bufferedMouse;
	Logger* loggerM;

	bool InitMouse(); //Initialize the mouse
	MouseStruct GetMouseInput(); //Get the current mouse values
	void SetTheMouseBuffer(); //?
	void ResetMouseStruct();
};

#endif //Headerguard