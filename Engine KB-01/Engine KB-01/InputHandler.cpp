#include "InputHandler.h"

Logger* loggerIH = Logger::GetLogger();

/**
 * Function:	InputHandler::InputHandler(...)
 * Description:	constructor - setup DirectInput and listeners
 */
InputHandler::InputHandler(Window* argWindow)
{
	dInput = NULL; //Nullify the DirectInput pointer
	if (!InitDInput())
	{
		//Can't initialize DirectInput so we're going to log the error, notify the user and stop the program with a negative exit code
		loggerIH->WriteToFile(FatalError, "Could not create DirectInput interface in InputHandler!", __LINE__);
		argWindow->ShowMessagebox("Could not create DirectInput interface in InputHandler!", "Error", MB_ICONERROR | MB_OK);
		exit(-1);
	}
	//Create the Listeners now that we have DirectInput
	mousewhisperer = new MouseListener(argWindow, dInput);
	keyboardwhisperer = new KeyboardListener(argWindow, dInput);
}

/**
 * Function:	InputHandler::~InputHandler(...)
 * Description:	destructor - get rid of leftovers
 */
InputHandler::~InputHandler()
{
	delete mousewhisperer; //Call the destructor
	delete keyboardwhisperer; //Call the destructor
	dInput->Release(); //Formally tell DirectInput to let go and move on
	dInput = NULL; //Just to be safe, we nullify the pointer
}

KeyboardListener* InputHandler::getKeyBoardListener()
{
	return keyboardwhisperer;
}

MouseListener* InputHandler::getMouseListener()
{
	return mousewhisperer;
}

/**
 * Function:	InputHandler::InitDInput()
 * Description:	Create a DirectInput instance
 */
bool InputHandler::InitDInput()
{
	//Have DirectX fill the 'dInput' pointer with an instance of DirectInput, but check if it did this correctly and return the result accordingly
	HRESULT result = DirectInput8Create( GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&dInput, NULL );
	if( FAILED( result ) )
	{
		return false;
	} else {
		return true;
	}
}