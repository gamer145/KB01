#include "Camera.h"

Camera::Camera()
{
	EyePoint = &VectorWrapper(0, 0, 0);
	LookatPoint = &VectorWrapper(0, 0, 0);
	UpVector = &VectorWrapper(0, 0, 0);

	Position = new MatrixWrapper();
	ProjectionMatrix = new MatrixWrapper();

	horizontalAngle = 90;
}

Camera::~Camera()
{

}


void Camera::Initialize()
{
	sinFactor = (abs(LookatPoint->GetZ()) + abs(EyePoint->GetZ()));
	Position->MatrixLookAtLH( EyePoint, LookatPoint, UpVector );
	ProjectionMatrix->MatrixPerspectiveFovLH(M_PI / 4, 1.0f, 1.0f, 100000.0f);
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

//Logic for Forward and Backward Movement. The movement is done in a 2DPlane.
//Logic is based on the position of the camera, and where it's looking at.
void Camera::ModifyCameraForward(float modifier)
{
	float LPX = LookatPoint->GetX();
	float EPX = EyePoint->GetX();
	float LPZ = LookatPoint->GetZ();
	float EPZ = EyePoint->GetZ();

	float XMov = (LPX - EPX);
	float ZMov = (LPZ - EPZ);

	float TotalMov = (abs(XMov) + abs(ZMov));
	float XRatio = (XMov / TotalMov);
	float ZRatio = (ZMov / TotalMov);

	float XModifier = XRatio * modifier;
	float ZModifier = ZRatio * modifier;

	EyePoint->ModX(XModifier);
	LookatPoint->ModX(XModifier);

	EyePoint->ModZ(ZModifier);
	LookatPoint->ModZ(ZModifier);
}

void Camera::ModifyCameraHeight(float modifier)
{
	EyePoint->ModY(modifier);
	LookatPoint->ModY(modifier);
}

//Logic for sideways Movement. The movement is done in a 2DPlane. 
//Logic is based on the position of the camera, and where it's looking at.
void Camera::ModifyCameraSide(float modifier)
{
	float LPX = LookatPoint->GetX();
	float EPX = EyePoint->GetX();
	float LPZ = LookatPoint->GetZ();
	float EPZ = EyePoint->GetZ();

	float XMov = (LPX - EPX);
	float ZMov = (LPZ - EPZ);

	float TotalMov = (abs(XMov) + abs(ZMov));
	float ZRatio = (XMov / TotalMov);
	float XRatio = (ZMov / TotalMov);


	float XModifier = XRatio * modifier;
	float ZModifier = ZRatio * -modifier;


	EyePoint->ModX(XModifier);
	LookatPoint->ModX(XModifier);

	EyePoint->ModZ(ZModifier);
	LookatPoint->ModZ(ZModifier);
}



void Camera::ModifyCameraXRotation(float modifier)
{
	if (modifier != 0)
	{
		float EPZ = EyePoint->GetZ();
		float EPX = EyePoint->GetX();

		if (modifier > 0)
			if (360 > horizontalAngle + 1)
			{
				if (horizontalAngle + 1 == 180)
				{
					horizontalAngle += 1;
				}
				horizontalAngle += 1;
			}
			else
			{
				horizontalAngle = 1;
			}
		else if (modifier < 0)
			if(horizontalAngle - 1 > 0)
			{
				if (horizontalAngle - 1 == 180)
				{
					horizontalAngle -= 1;
				}
				horizontalAngle -= 1;
			}
			else
			{
				horizontalAngle = 359;
			}

		float calc = sin(horizontalAngle * M_PI / 180);			
		float newLPZ = ((calc * sinFactor) + EPZ);
		LookatPoint->SetZ(newLPZ);

		float calc2 = (newLPZ - EPZ) / tan(horizontalAngle * M_PI / 180);
		float newLPX = (calc2) + EPX;

		LookatPoint->SetX(newLPX);
		std::ostringstream ss;
		std::string a;

		ss << horizontalAngle;
		a = ss.str();

		Logger* myLogger;
		myLogger = Logger::GetLogger();
		myLogger->WriteToFile(Error, a, 0);
			

	}
} 

void Camera::ModifyCameraYRotation(float modifier)
{
	float LPZ = LookatPoint->GetZ();
	float EPZ = EyePoint->GetZ();

	if (LPZ > EPZ)
	{
		LookatPoint->ModY(modifier);
		LookatPoint->ModZ(modifier);
	}
}

void Camera::ModifyCameraZRotation(float modifier)
{
	//ZAngle += modifier;
}

MatrixWrapper* Camera::getProjectionMatrix()
{
	return ProjectionMatrix;
}

ERUNSTATE Camera::Update()
{
		ERUNSTATE state = RUNNING;

		ModifyCameraXRotation(myInputHandler->getAction(ACTION_ROTATECAMERA_X));
		ModifyCameraYRotation(myInputHandler->getAction(ACTION_ROTATECAMERA_Y));

		ModifyCameraForward(myInputHandler->getAction(ACTION_ZAXISMOVE));
		ModifyCameraHeight(myInputHandler->getAction(ACTION_YAXISMOVE));
		ModifyCameraSide(myInputHandler->getAction(ACTION_XAXISMOVE));

		if (myInputHandler->getAction(ACTION_EXIT) < 0)
		{
			state = EXIT;
		}

		UpdateCameraMatrix();
		return state;

}

ERUNSTATE Camera::UpdateOculus(Renderer* renderer, const OVR::Util::Render::StereoEyeParams& params, OVR::Util::Render::StereoConfig SConfig)
{
	renderer->setViewMatrixOculus(params, SConfig);
	renderer->setProjectionMatrixOculus(params, SConfig);

	ERUNSTATE state = RUNNING;
	
	ModifyCameraXRotation(myInputHandler->getAction(ACTION_ROTATECAMERA_X));
	ModifyCameraYRotation(myInputHandler->getAction(ACTION_ROTATECAMERA_Y));

	ModifyCameraForward(myInputHandler->getAction(ACTION_ZAXISMOVE));
	ModifyCameraHeight(myInputHandler->getAction(ACTION_YAXISMOVE));
	ModifyCameraSide(myInputHandler->getAction(ACTION_XAXISMOVE));

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

void Camera::UpdateCameraMatrix()
{
	Position->MatrixLookAtLH(EyePoint, LookatPoint, UpVector);
}
