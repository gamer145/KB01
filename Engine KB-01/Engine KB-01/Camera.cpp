#include "Camera.h"

Camera::Camera()
{
	EyePoint = &VectorWrapper(0, 0, 0);
	LookatPoint = &VectorWrapper(0, 0, 0);
	UpVector = &VectorWrapper(0, 0, 0);
	x = 0;
	y = 0;
	z = 0;
	XAngle = 0;
	YAngle = 0;
	ZAngle = 0;

	Position = new MatrixWrapper();
	ProjectionMatrix = new MatrixWrapper();
}

Camera::~Camera()
{

}


void Camera::Initialize()
{
	Position->MatrixLookAtLH( EyePoint, LookatPoint, UpVector );
	ProjectionMatrix->MatrixPerspectiveFovLH(D3DX_PI / 4, 1.0f, 1.0f, 100000.0f);
	mousewheel = 0;
	xpos = 0;
	ypos = 0;
}

void Camera::SetInputHandler(InputHandlerInterface* IH)
{
	myInputHandler = IH;
}

void Camera::SetEyePoint(VectorWrapper* newVector)
{
	EyePoint = newVector;
}

void Camera::SetLookAtPoint(VectorWrapper* newVector)
{
	LookatPoint = newVector;
}

void Camera::SetUpVector(VectorWrapper* newVector)
{
	UpVector = newVector;
}

void Camera::ModifyWorldX(float modifier)
{
	EyePoint->SetX(modifier);
	LookatPoint->SetX(modifier);
}

void Camera::ModifyWorldY(float modifier)
{
	EyePoint->SetY(modifier);
	LookatPoint->SetY(modifier);
}

void Camera::ModifyWorldZ(float modifier)
{
	EyePoint->SetZ(modifier);
	LookatPoint->SetZ(modifier);
}

void Camera::ModifyWorldXAngle(float modifier)
{
	
	float LPX = LookatPoint->GetX();
	float EPX = EyePoint->GetX();
	float LPZ = LookatPoint->GetZ();
	float EPZ = EyePoint->GetZ();

	if (LPX >= EPX)
	{		
		LookatPoint->SetZ(-modifier);
	}
	else if (LPX < EPX)
	{
		LookatPoint->SetZ(modifier);
	}

	if (LPZ >= EPZ)
	{
		LookatPoint->SetX(modifier);
	}
	else if (LPZ < EPZ)
	{
		LookatPoint->SetX(-modifier);
	}
}

void Camera::ModifyWorldYAngle(float modifier)
{
	float LPZ = LookatPoint->GetZ();
	float EPZ = EyePoint->GetZ();

	if (LPZ > EPZ)
	{
		LookatPoint->SetY(modifier);
		LookatPoint->SetZ(modifier);
	}
}

void Camera::ModifyWorldZAngle(float modifier)
{
	ZAngle += modifier;
}

MatrixWrapper* Camera::getProjectionMatrix()
{
	return ProjectionMatrix;
}

ERUNSTATE Camera::Update()
{
	ERUNSTATE state = RUNNING;

	ModifyWorldX(myInputHandler->getAction(ACTION_XAXISMOVE));
	ModifyWorldY(myInputHandler->getAction(ACTION_YAXISMOVE));
	ModifyWorldZ(myInputHandler->getAction(ACTION_ZAXISMOVE));
	ModifyWorldXAngle(myInputHandler->getAction(ACTION_ROTATECAMERA_X));
	ModifyWorldYAngle(myInputHandler->getAction(ACTION_ROTATECAMERA_Y));
	if (myInputHandler->getAction(ACTION_EXIT) < 0)
	{
		state = EXIT;
	}
	UpdateCameraMatrix();
	return state;
}

/*void Camera::Update()
{

		if (myInputHandler->getKeyBoardListener()->ProcessKBInput((byte)DIKEYBOARD_W))
		{
			ModifyWorldZ(-0.1f);
		}

		if (myInputHandler->getKeyBoardListener()->ProcessKBInput((byte)DIKEYBOARD_Q))
		{
			ModifyWorldX(0.1f);
		}

		if (myInputHandler->getKeyBoardListener()->ProcessKBInput((byte)DIKEYBOARD_A))
		{
			ModifyWorldX(0.2f);
			ModifyWorldXAngle(0.05f);
		}

		if (myInputHandler->getKeyBoardListener()->ProcessKBInput((byte)DIKEYBOARD_D))
		{
			ModifyWorldX(-0.2f);
			ModifyWorldXAngle(-0.05f);
		}

		if (myInputHandler->getKeyBoardListener()->ProcessKBInput((byte)DIKEYBOARD_S))
		{
			ModifyWorldZ(0.1f);
		}

		if (myInputHandler->getKeyBoardListener()->ProcessKBInput((byte)DIKEYBOARD_E))
		{
			ModifyWorldX(-0.1f);
		}

		if (myInputHandler->getKeyBoardListener()->ProcessKBInput((byte)DIKEYBOARD_SPACE))
		{
  			ModifyWorldY(-0.1f);
		}

		if (myInputHandler->getKeyBoardListener()->ProcessKBInput((byte)DIKEYBOARD_LCONTROL))
		{
			ModifyWorldY(0.1f);
		}

		//-----

		if (myInputHandler->getMouseListener()->getMousewheel() > mousewheel) {
			ModifyWorldZ(-0.1f);
			mousewheel = myInputHandler->getMouseListener()->getMousewheel();
		}
		else if (myInputHandler->getMouseListener()->getMousewheel() < mousewheel) {
			ModifyWorldZ(0.1f);
			mousewheel = myInputHandler->getMouseListener()->getMousewheel();
		}
		
		if (myInputHandler->getMouseListener()->getXPos() < xpos)
		{
			ModifyWorldXAngle(0.02f);
			xpos = myInputHandler->getMouseListener()->getXPos();
		}

		if (myInputHandler->getMouseListener()->getXPos() > xpos)
		{
			ModifyWorldXAngle(-0.02f);
			xpos = myInputHandler->getMouseListener()->getXPos();
		}

		if (myInputHandler->getMouseListener()->getYPos() < ypos)
		{
			ModifyWorldYAngle(0.01f);
			ypos = myInputHandler->getMouseListener()->getYPos();
		}

		if (myInputHandler->getMouseListener()->getYPos() > ypos)
		{
			ModifyWorldYAngle(-0.01f);
			ypos = myInputHandler->getMouseListener()->getYPos();
		}

		UpdateOffSetMatrix();
}*/

/*void Camera::UpdateOffSetMatrix()
{
	WorldYRotation->MatrixRotationY(XAngle);
	WorldXRotation->MatrixRotationX(YAngle);
	WorldZRotation->MatrixRotationZ(ZAngle);
	WorldPosition->MatrixTranslation(x, y, z);

	WorldRotation->SetMatrix(WorldXRotation->GetMatrix() * WorldYRotation->GetMatrix() * WorldZRotation->GetMatrix());
	OffSetMatrix->SetMatrix(WorldRotation->GetMatrix() * WorldPosition->GetMatrix());
}*/

void Camera::UpdateCameraMatrix()
{
	Position->MatrixLookAtLH(EyePoint, LookatPoint, UpVector);
}
