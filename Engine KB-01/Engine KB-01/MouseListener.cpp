#include "MouseListener.h"


MouseListener::MouseListener( Window* argWindow, LPDIRECTINPUT8 argDInput )
{
	loggerM = Logger::GetLogger(); //Get a pointer to the Logger object
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
		//Creation failed, we need to log the error, notify the user and not display a cursor, since there is no mouse
		loggerM->WriteToFile(FatalError, "Can´t create mouse Object");
		int result = window->ShowMessagebox("Can´t create mouse Object", "Fatal Error", MB_ICONERROR | MB_OK);
		ShowCursor(FALSE);
	}	
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
	ShowCursor(FALSE);

	return true;
}

void MouseListener::setMouseAcceleration(float newAcceleration)
{
	mouseAcceleration = newAcceleration;
}

bool MouseListener::getAction(EACTION action, float& value)
{
	GetMouseInput();
	bool answer = false;

	if (action == ACTION_ROTATECAMERA_X && !answer)
	{
		long diff = bufferedMouse.positionX - oldMouseState.positionX;

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
	}

	if (action == ACTION_TOGGLEDEBUG && !answer)
	{		
		answer = isButtonDown(2, bufferedMouse);
		if (answer && !bufferedMouse.buttonlock[2])
		{
			bufferedMouse.buttonlock[2] = true; //Locks the button
			loggerM->WriteToFile(Success, "TOGGLE TOGGLED");
			value = -1.0f;
		}
		else if (!answer && bufferedMouse.buttonlock[2])
		{
			bufferedMouse.buttonlock[2] = false;
		}
	}

	oldMouseState = bufferedMouse;

	return answer;
}


long MouseListener::getMousewheel()
{
	MouseStruct temp = GetMouseInput();
	return temp.z;
}

bool MouseListener::isButtonDown(int button, MouseStruct mouse)
{
	switch (button)
	{
		case 0:
			return mouse.button0;
		case 1:
			return mouse.button1;
		case 2:
			return mouse.button2;
		case 3:
			return mouse.button3;
		case 4:
			return mouse.button4;
		case 5:
			return mouse.button5;
		case 6:
			return mouse.button6;
		case 7:
			return mouse.button7;
	}
	return false;	//If none of the buttons are down
					//Or if button down is outside the range of 0-7, meaning button is unsupported
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
			//We can't get the mouse
			loggerM->WriteToFile(FatalError, "MouseListener: Can't get mouse");
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
	EDWORD elements = 1;

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

		// Mouse right button
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