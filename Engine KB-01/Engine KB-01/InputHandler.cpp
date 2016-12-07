#include "InputHandler.h"

Logger* loggerIH = Logger::GetLogger();

/**
 * Function:	InputHandler::InputHandler(...)
 * Description:	constructor - setup DirectInput and listeners
 */
InputHandler::InputHandler()
{

}

HRESULT InputHandler::InitInputHandler(Window* argWindow)
{
	dInput = NULL; //Nullify the DirectInput pointer
	if (FAILED(InitDInput()))
	{
		//Can't initialize DirectInput so we're going to log the error, notify the user and stop the program with a negative exit code
		loggerIH->WriteToFile(FatalError, "Could not create DirectInput interface in InputHandler!");
		argWindow->ShowMessagebox("Could not create DirectInput interface in InputHandler!", "Error", MB_ICONERROR | MB_OK);
		return -1;
	}
	//Create the Listeners now that we have DirectInput
	mousewhisperer = new MouseListener(argWindow, dInput);
	mousewhisperer->setMouseAcceleration(5);
	keyboardwhisperer = new KeyboardListener(argWindow, dInput);
	return 0;
}

/**
 * Function:	InputHandler::~InputHandler(...)
 * Description:	destructor - get rid of leftovers
 */
InputHandler::~InputHandler()
{
	if (mousewhisperer != NULL) {
		delete mousewhisperer; //Call the destructor
	}
	if (keyboardwhisperer != NULL) {
		delete keyboardwhisperer; //Call the destructor
	}
	if (dInput != NULL) {
		dInput->Release(); //Formally tell DirectInput to let go and move on
		dInput = NULL; //Just to be safe, we nullify the pointer
	}


	
}

void InputHandler::pollWhisperers()
{
	//Avoid polling for each action? Is that usefull?
}

float InputHandler::getAction(EACTION action)
{
	float response = 0;

	pollWhisperers();

	keyboardwhisperer->getAction(action, response);

	mousewhisperer->getAction(action, response);

	return response;
}

/**
 * Function:	InputHandler::InitDInput()
 * Description:	Create a DirectInput instance
 */
HRESULT InputHandler::InitDInput()
{
	//Have DirectX fill the 'dInput' pointer with an instance of DirectInput, but check if it did this correctly and return the result accordingly
	HRESULT result = DirectInput8Create( GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&dInput, NULL );
	return result;
}