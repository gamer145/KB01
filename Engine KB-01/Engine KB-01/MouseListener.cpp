#include "MouseListener.h"

Logger* loggerM = Logger::GetLogger(); //Get a pointer to the Logger object

MouseListener::MouseListener( Window* argWindow, LPDIRECTINPUT8 argDInput )
{
	//Set the default values and pass on the parameters to our own variables
	const int MOUSEBUFFER		= 8;
	dipdw.diph.dwSize			= sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize		= sizeof(DIPROPHEADER);
	dipdw.diph.dwObj			= 0;
	dipdw.diph.dwHow			= DIPH_DEVICE;
	dipdw.dwData				= MOUSEBUFFER;
	window						= argWindow;
	dInput						= argDInput;
	dDeviceMouse				= NULL; //Nullify the mouse pointer
	mouseAcceleration			= 10;
	ResetMouseStruct(); //Set default values of the data that the mouse can provide such as X- and Y-position etc.

	if (!InitMouse()) //Try to create a mouse object
	{
		//Creation failed, we need to log the error, notify the user and stop the program with a negative exit code
		loggerM->WriteToFile(FatalError, "MouseListener: kan muis niet vangen.", __LINE__);
		int result = window->ShowMessagebox("MouseListener: kan muis niet vangen.", "Fatal Error", MB_ICONERROR | MB_OK);
		exit(-1);
	}
	ShowCursor(TRUE); //Please Windows, show the mouse cursor for now. TO BE REMOVED?
}

MouseListener::~MouseListener()
{
	SaveReleaseDevice(); //Cleanup the mouse
}

bool MouseListener::InitMouse()
{
	HRESULT result = dInput->CreateDevice( GUID_SysMouse, &dDeviceMouse, NULL );
	if( FAILED( result ) )
	{
		SaveReleaseDevice() ;
		return false;
	}

	result = dDeviceMouse->SetDataFormat( &c_dfDIMouse );
	if( FAILED( result ) )
	{
		SaveReleaseDevice() ;
		return false;
	}

	result = dDeviceMouse->SetCooperativeLevel( window->getHWND(), DISCL_EXCLUSIVE | DISCL_FOREGROUND );
	if( FAILED( result ) )
	{
		SaveReleaseDevice() ;
		return false;
	}

	result = dDeviceMouse->SetProperty( DIPROP_BUFFERSIZE, &dipdw.diph );
	if( FAILED( result ) )
	{
		SaveReleaseDevice() ;
		return false;
	}
	ShowCursor(TRUE); //Please Windows, show the mouse cursor for now.

	return true; //We made it here so everything must've gone right
}

void MouseListener::setMouseAcceleration(float newAcceleration)
{
	mouseAcceleration = newAcceleration;
}

bool MouseListener::getAction(EACTION action, float& value)
{
	MouseStruct newMouseState = GetMouseInput();
	bool answer = false;

	if (action == ACTION_ROTATECAMERA_X && !answer)
	{
		long diff = newMouseState.positionX - oldMouseState.positionX;

		if (diff < 0)
		{
			float factor = abs((float)(diff / mouseAcceleration));
			value = (-0.1f * factor);
			answer = true;
		}
		else if (diff > 0)
		{
			float factor = abs((float)(diff / mouseAcceleration));
			value = (0.1f * factor);
			answer =  true;
		}
		answer = false;
	}

	oldMouseState = newMouseState;

	return answer;
}


long MouseListener::getMousewheel()
{
	MouseStruct temp = GetMouseInput();
	return temp.z;
}

bool MouseListener::isButtonDown(int button)
{
	MouseStruct temp = GetMouseInput();
	switch (button)
	{
		case 0:
			return temp.button0;
		case 1:
			return temp.button1;
		case 2:
			return temp.button2;
		case 3:
			return temp.button3;
		case 4:
			return temp.button4;
		case 5:
			return temp.button5;
		case 6:
			return temp.button6;
		case 7:
			return temp.button7;
	}
	return temp.button0; //Als argument button niet 0-7 is.
}

/**
 * Function:	Mouse::GetMouseInput()
 * Description:	Method to see if the mousebuffer can be read or that an acquire is needed
 */
MouseStruct MouseListener::GetMouseInput()
{
	if(!SUCCEEDED( dDeviceMouse->Poll()))
	{
		//We don't have the mouse yet
		if(!SUCCEEDED( dDeviceMouse->Acquire() ) )
		{
			//We can't get the mouse :(
			//LOG DIE SHIT
		}
	}
	SetTheMouseBuffer();
	return bufferedMouse;
}

/**
 * Function:	Mouse::SetTheMouseBuffer()
 * Description:	Setting the buffer for the mouse and getting the device-data
 */
void MouseListener::SetTheMouseBuffer()
{
	DIDEVICEOBJECTDATA od;
	DWORD elements = 1;

	HRESULT hr = dDeviceMouse->GetDeviceData( sizeof(DIDEVICEOBJECTDATA), &od, &elements, 0 );
	//&elements = number of elements in deviceData. 

	// Switch case to get the data from the mouse
	switch (od.dwOfs) 
	{
		// Mouse horizontal motion
		case DIMOFS_X:
			bufferedMouse.positionX += static_cast<long>(od.dwData);
			break;

		// Mouse vertical motion
		case DIMOFS_Y:
			bufferedMouse.positionY += static_cast<long>(od.dwData);
			break;

		// Mouse left button
		case DIMOFS_BUTTON0:
			if ( (long)od.dwData == 0 )
			{
				bufferedMouse.button0 = false;
			}
			else
			{
				bufferedMouse.button0 = true;
			}
			break;

		// Mouse left button
		case DIMOFS_BUTTON1:
			if ( static_cast<long>(od.dwData) == 0 )
			{
				bufferedMouse.button1 = false;
			}
			else
			{
				bufferedMouse.button1 = true;
			}
			break;

		// Mousewheel button
		case DIMOFS_BUTTON2:
			if ( static_cast<long>(od.dwData) == 0 )
			{
				bufferedMouse.button2 = false;
			}
			else
			{
				bufferedMouse.button2 = true;
			}
			break;
		
		// Button 3
		case DIMOFS_BUTTON3:
			if ( static_cast<long>(od.dwData) == 0 )
			{
				bufferedMouse.button3 = false;
			}
			else
			{
				bufferedMouse.button3 = true;
			}
			break;

		// Button 4
		case DIMOFS_BUTTON4:
			if ( static_cast<long>(od.dwData) == 0 )
			{
				bufferedMouse.button4 = false;
			}
			else
			{
				bufferedMouse.button4 = true;
			}
			break;

		// Button 5
		case DIMOFS_BUTTON5:
			if ( static_cast<long>(od.dwData) == 0 )
			{
				bufferedMouse.button5 = false;
			}
			else
			{
				bufferedMouse.button5 = true;
			}
			break;

		// Button 6
		case DIMOFS_BUTTON6:
			if ( static_cast<long>(od.dwData) == 0 )
			{
				bufferedMouse.button6 = false;
			}
			else
			{
				bufferedMouse.button6 = true;
			}
			break;

		// Button 7
		case DIMOFS_BUTTON7:
			if ( static_cast<long>(od.dwData) == 0 )
			{
				bufferedMouse.button7 = false;
			}
			else
			{
				bufferedMouse.button7 = true;
			}
			break;

		// Mouse wheel
		case DIMOFS_Z:
			bufferedMouse.z += static_cast<long>(od.dwData);
			break;
	}
}

void MouseListener::SaveReleaseDevice() 
{
	if( dDeviceMouse ) //If the mouse object exists, let go of it completely and finally nullify just to be safe
	{
		dDeviceMouse->Unacquire();
		dDeviceMouse->Release();
		dDeviceMouse = NULL;
	}
} 

void MouseListener::ResetMouseStruct() //Reset every mouse value
{
	bufferedMouse.positionX = 0;
	bufferedMouse.positionY = 0;
	bufferedMouse.z = 0;
	bufferedMouse.button0 = false;
	bufferedMouse.button1 = false;
	bufferedMouse.button2 = false;
	bufferedMouse.button3 = false;
	bufferedMouse.button4 = false;
	bufferedMouse.button5 = false;
	bufferedMouse.button6 = false;
	bufferedMouse.button7 = false;
	oldMouseState = bufferedMouse;
}