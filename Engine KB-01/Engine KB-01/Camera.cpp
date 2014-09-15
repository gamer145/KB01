#include "Camera.h"

Camera::Camera()
{
	EyePoint = D3DXVECTOR3(0, 0, 0);
	LookatPoint = D3DXVECTOR3(0, 0, 0);
	UpVector = D3DXVECTOR3(0, 0, 0);
	x = 0;
	y = 0;
	z = 0;
	XAngle = 0;
	YAngle = 0;
	ZAngle = 0;

}

Camera::~Camera()
{
}


void Camera::Initialize()
{
	D3DXMatrixLookAtLH( &Position, &EyePoint, &LookatPoint, &UpVector );
	D3DXMatrixPerspectiveFovLH(&ProjectionMatrix, D3DX_PI / 4, 1.0f, 1.0f, 100000.0f );
	mousewheel = 0;
	xpos = 0;
	ypos = 0;
}

void Camera::SetInputHandler(InputHandler* IH)
{
	myInputHandler = IH;
}

void Camera::SetEyePoint(D3DXVECTOR3 newVector)
{
	EyePoint = newVector;
}

void Camera::SetLookAtPoint(D3DXVECTOR3 newVector)
{
	LookatPoint = newVector;
}

void Camera::SetUpVector(D3DXVECTOR3 newVector)
{
	UpVector = newVector;
}

void Camera::ModifyWorldX(float modifier)
{
	x += modifier;
}

void Camera::ModifyWorldY(float modifier)
{
	y += modifier;
}

void Camera::ModifyWorldZ(float modifier)
{
	z += modifier;
}

void Camera::ModifyWorldXAngle(float modifier)
{
	XAngle += modifier;
}

void Camera::ModifyWorldYAngle(float modifier)
{
	YAngle += modifier;
}

void Camera::ModifyWorldZAngle(float modifier)
{
	ZAngle += modifier;
}

D3DXMATRIX Camera::getProjectionMatrix()
{
	return ProjectionMatrix;
}

D3DXMATRIX Camera::getOffSetMatrix()
{
	return OffSetMatrix;
}

void Camera::Update()
{

		if (myInputHandler->keyboardwhisperer->ProcessKBInput((byte)DIKEYBOARD_W))
		{
			ModifyWorldZ(-0.1f);
		}

		if (myInputHandler->keyboardwhisperer->ProcessKBInput((byte)DIKEYBOARD_Q))
		{
			ModifyWorldX(0.1f);
		}

		if (myInputHandler->keyboardwhisperer->ProcessKBInput((byte)DIKEYBOARD_A))
		{
			ModifyWorldX(0.2f);
			ModifyWorldXAngle(0.05f);
		}

		if (myInputHandler->keyboardwhisperer->ProcessKBInput((byte)DIKEYBOARD_D))
		{
			ModifyWorldX(-0.2f);
			ModifyWorldXAngle(-0.05f);
		}

		if (myInputHandler->keyboardwhisperer->ProcessKBInput((byte)DIKEYBOARD_S))
		{
			ModifyWorldZ(0.1f);
		}

		if (myInputHandler->keyboardwhisperer->ProcessKBInput((byte)DIKEYBOARD_E))
		{
			ModifyWorldX(-0.1f);
		}

		if (myInputHandler->keyboardwhisperer->ProcessKBInput((byte)DIKEYBOARD_SPACE))
		{
			ModifyWorldY(-0.1f);
		}

		if (myInputHandler->keyboardwhisperer->ProcessKBInput((byte)DIKEYBOARD_LCONTROL))
		{
			ModifyWorldY(0.1f);
		}

		//-----

		if (myInputHandler->mousewhisperer->getMousewheel() > mousewheel) {
			ModifyWorldZ(-0.1f);
			mousewheel = myInputHandler->mousewhisperer->getMousewheel();
		} else if (myInputHandler->mousewhisperer->getMousewheel() < mousewheel) {
			ModifyWorldZ(0.1f);
			mousewheel = myInputHandler->mousewhisperer->getMousewheel();
		}
		
		if (myInputHandler->mousewhisperer->getXPos() < xpos)
		{
			ModifyWorldXAngle(0.02f);
			xpos = myInputHandler->mousewhisperer->getXPos();
		}

		if (myInputHandler->mousewhisperer->getXPos() > xpos)
		{
			ModifyWorldXAngle(-0.02f);
			xpos = myInputHandler->mousewhisperer->getXPos();
		}

	    if (myInputHandler->mousewhisperer->getYPos() < ypos)
		{
			ModifyWorldYAngle(0.01f);
			ypos = myInputHandler->mousewhisperer->getYPos();
		}

		if (myInputHandler->mousewhisperer->getYPos() > ypos)
		{
			ModifyWorldYAngle(-0.01f);
			ypos = myInputHandler->mousewhisperer->getYPos();
		}

		UpdateOffSetMatrix();
}

void Camera::UpdateOffSetMatrix()
{
    D3DXMatrixRotationY( &WorldYRotation, XAngle);
	D3DXMatrixRotationX( &WorldXRotation, YAngle);
	D3DXMatrixRotationZ( &WorldZRotation, ZAngle);
	D3DXMatrixTranslation(&WorldPosition, x, y, z);

	WorldRotation = WorldXRotation * WorldYRotation * WorldZRotation;
	OffSetMatrix = WorldRotation * WorldPosition;
}
