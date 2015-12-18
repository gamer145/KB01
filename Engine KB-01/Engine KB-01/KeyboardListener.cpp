#define KEYDOWN(name, key) (name[key] & 0x80)

#include "KeyboardListener.h"



KeyboardListener::KeyboardListener( Window* argWindow, LPDIRECTINPUT8 argDInput )
{
	loggerKB = Logger::GetLogger();
	dInput				= argDInput; 
	dDeviceKeyboard				= NULL; 
	window = argWindow;
	if (!InitKeyboard())
	{
		//Kan toetsenbord niet vangen, eerst loggen en dan waarschuwen.
		loggerKB->WriteToFile(FatalError, "KeyboardListener: kan toetsenbord niet vangen.");
		int result = window->ShowMessagebox("KeyboardListener: kan toetsenbord niet vangen.", "Fatal Error", MB_ICONERROR | MB_OK); //met result nog iets doen?
		exit(-1);
	}
}

KeyboardListener::~KeyboardListener()
{
	SaveReleaseDevice();
}

/**
 * Function:	Keyboard::InitKeyboard()
 * Description:	initializing the keyboard (creating the device and setting the coopertive level)
 */
bool KeyboardListener::InitKeyboard()
{
	HRESULT hr = dInput->CreateDevice( GUID_SysKeyboard, &dDeviceKeyboard, NULL );
	if FAILED( hr ) 
	{ 
		SaveReleaseDevice(); 
		return false; 
	}

	hr = dDeviceKeyboard->SetDataFormat( &c_dfDIKeyboard ); 
	if FAILED( hr ) 
	{ 
		SaveReleaseDevice(); 
		return false; 
	} 

	hr = dDeviceKeyboard->SetCooperativeLevel( window->getHWND(), DISCL_EXCLUSIVE | DISCL_FOREGROUND );
	if FAILED( hr )
	{ 
		SaveReleaseDevice(); 
		return false; 
	} 

	return true; 
}

/**
 * Function:	Keyboard::saveReleaseDevice() 
 * Description:	Cleaning up the mess left if a keyboard is lost
 */
void KeyboardListener::SaveReleaseDevice() 
{ 
	if (dDeviceKeyboard)
	{
		dDeviceKeyboard->Unacquire();
		dDeviceKeyboard->Release();
		dDeviceKeyboard = NULL;
	}
} 

bool KeyboardListener::getAction(EACTION action, float& value)
{
	if (action == ACTION_ZAXISMOVE)
	{
		if (ProcessKBInput((byte)DIKEYBOARD_W))
		{
			value = 0.1f;
			return true;
		}
		else if (ProcessKBInput((byte)DIKEYBOARD_S))
		{
			value = -0.1f;
			return true;
		}
		return false;
	}

	if (action == ACTION_YAXISMOVE)
	{
		if (ProcessKBInput((byte)DIKEYBOARD_SPACE))
		{
			value = 0.1f;
			return true;
		}
		else if (ProcessKBInput((byte)DIKEYBOARD_LCONTROL))
		{
			value = -0.1f;
			return true;
		}
		return false;
	}

	if (action == ACTION_XAXISMOVE)
	{
		if (ProcessKBInput((byte)DIKEYBOARD_Q))
		{
			value = -0.1f;
			return true;
		}
		else if (ProcessKBInput((byte)DIKEYBOARD_E))
		{
			value = 0.1f;
			return true;
		}
		return false;
	}

	if (action == ACTION_ROTATECAMERA_X)
	{
		if (ProcessKBInput((byte)DIKEYBOARD_A))
		{
			value = -0.1f;
			return true;
		}
		else if (ProcessKBInput((byte)DIKEYBOARD_D))
		{
			value = 0.1f;
			return true;
		}
		return false;
	}

	if (action == ACTION_ROTATECAMERA_Y)
	{
		if (ProcessKBInput((byte)DIKEYBOARD_F))
		{
			value = -0.1f;
			return true;
		}
		else if (ProcessKBInput((byte)DIKEYBOARD_R))
		{
			value = 0.1f;
			return true;
		}
		return false;
	}

	if (action == ACTION_EXIT)
	{
		if (ProcessKBInput((byte)DIKEYBOARD_ESCAPE))
		{
			value = -0.1f;
			return true;
		}
		return false;
	}

	return false;
}


/**
 * Function:	Keyboard::ProcessKBInput(...)
 * Description:	Method to see if the keyboardbuffer can be red or that a aquire is needed
 * @ param argIsToggle
 *	 Boolean to see if the key that is pressed a togglebutton is
 * @ param argKeyIsPressed
 *	 Byte containing the key that must be checked
 */
bool KeyboardListener::ProcessKBInput( byte argKeyIsPressed ) 
{ 
	if(!SUCCEEDED( dDeviceKeyboard->Poll() ))
	{
		DoAcquire();
	}
	
	ZeroMemory(keyBuffer, sizeof(keyBuffer));

	dDeviceKeyboard->GetDeviceState( sizeof( keyBuffer ) , (LPVOID)&keyBuffer );

	// Check if keybuffer contains given key
	int pressed = KEYDOWN( keyBuffer, argKeyIsPressed );

	// pressed == 0 or 128 (0x80); meaning false or true
	if( pressed == 0 )
	{
		return false;
	}
	else
	{
		return true;
	}
}

/**
 * Function:	Keyboard::DoAcquire()
 * Description:	Acquiring the device
 */
bool KeyboardListener::DoAcquire()
{
	if( SUCCEEDED( dDeviceKeyboard->Acquire() ) )
	{
		return true;
	}
	return false;
}