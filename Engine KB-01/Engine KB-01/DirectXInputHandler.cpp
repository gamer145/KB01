#include "DirectXInputHandler.h"

/**
 * Function:	DirectXInputHandler::DirectXInputHandler()
 * Description:	constructor - setup DirectInput and listeners
 */
DirectXInputHandler::DirectXInputHandler()
{
	loggerIH = Logger::GetLogger();
}

HRESULT DirectXInputHandler::InitInputHandler(Window* argWindow)
{
	dInput = NULL; //Nullify the DirectInput pointer
	if (FAILED(InitDInput()))
	{
		//Can't initialize DirectInput so we're going to log the error, notify the user and stop the program with a negative exit code
		loggerIH->WriteToFile(FatalError, "Could not create DirectInput interface in DirectXInputHandler!");
		argWindow->ShowMessagebox("Could not create DirectInput interface in DirectXInputHandler!", "Error", MB_ICONERROR | MB_OK);
		return -1;
	}
	//Create the Listeners now that we have DirectInput
	mousewhisperer = new MouseListener(argWindow, dInput);
	mousewhisperer->setMouseAcceleration(5);
	keyboardwhisperer = new KeyboardListener(argWindow, dInput);
	return 0;
}

/**
 * Function:	DirectXInputHandler::~DirectXInputHandler()
 * Description:	destructor - get rid of leftovers
 */
DirectXInputHandler::~DirectXInputHandler()
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

/**
* Function:	DirectXInputHandler::getAction()
* Description: Asks the whisperers whether they know a certain action or not
*/
float DirectXInputHandler::getAction(EACTION action)
{
	float response = 0;

	keyboardwhisperer->getAction(action, response);

	mousewhisperer->getAction(action, response);

	return response;
}

/**
 * Function:	DirectXInputHandler::InitDInput()
 * Description:	Create a DirectInput instance
 */
HRESULT DirectXInputHandler::InitDInput()
{
	//Have DirectX fill the 'dInput' pointer with an instance of DirectInput, but check if it did this correctly and return the result accordingly
	HRESULT result = DirectInput8Create( GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&dInput, NULL );
	return result;
}