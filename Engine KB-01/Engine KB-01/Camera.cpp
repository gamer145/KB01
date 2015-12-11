#include "Camera.h"

Camera::Camera()
{
	EyePoint = &VectorWrapper(0, 0, 0);
	LookatPoint = &VectorWrapper(0, 0, 0);
	UpVector = &VectorWrapper(0, 0, 0);

	Position = new MatrixWrapper();
	ProjectionMatrix = new MatrixWrapper();
}

Camera::~Camera()
{

}

void Camera::CalculateAngles()
{
	horizontalAngle = 90;
	verticalAngle = 90;
}


void Camera::Initialize()
{
	radius = (abs(LookatPoint->GetZ()) + abs(EyePoint->GetZ()));
	Position->MatrixLookAtLH( EyePoint, LookatPoint, UpVector );
	ProjectionMatrix->MatrixPerspectiveFovLH(M_PI / 4, 1.0f, 1.0f, 100000.0f);
	CalculateAngles();
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
	int angleMod = round((abs(modifier) * 10));
	if (modifier != 0)
	{
		float EPZ = EyePoint->GetZ();
		float EPX = EyePoint->GetX();

		if (modifier < 0)
			if (360 > horizontalAngle + angleMod)
			{
					horizontalAngle += angleMod;
			}
			else
			{
				horizontalAngle = -1 + angleMod;
			}
		else if (modifier > 0)
			if (horizontalAngle - angleMod >= 0)
			{
					horizontalAngle -= angleMod;
			}
			else
			{
				horizontalAngle = 360 - angleMod;
			}

		float calc = sin(horizontalAngle * M_PI / 180);			
		float newLPZ = ((calc * radius) + EPZ);

		float newLPX;
		float calc2;

		if (horizontalAngle == 180)
		{
			newLPX = -radius + EPX;
		}
		else if (horizontalAngle == 0)
		{
			newLPX = radius + EPX;
		}
		else
		{
			calc2 = (newLPZ - EPZ) / tan(horizontalAngle * M_PI / 180);
			newLPX = calc2 + EPX;
		}

		LookatPoint->SetZ(newLPZ);
		LookatPoint->SetX(newLPX);

	}
} 

void Camera::ModifyCameraYRotation(float modifier)
{
	int angleMod = round((abs(modifier) * 10));
	if (modifier != 0)
	{
		float EPZ = EyePoint->GetZ();
		float EPY = EyePoint->GetY();

		if (modifier < 0)
			if (360 > verticalAngle + angleMod)
			{
				verticalAngle += angleMod;
			}
			else
			{
				verticalAngle = -1 + angleMod;
			}
		else if (modifier > 0)
			if (verticalAngle - angleMod >= 0)
			{
				verticalAngle -= angleMod;
			}
			else
			{
				verticalAngle = 360 - angleMod;
			}

		float calc = sin(verticalAngle * M_PI / 180);
		float newLPZ = ((calc * radius) + EPZ);

		float newLPY;
		float calc2;

		if (verticalAngle == 180)
		{
			newLPY = -radius + EPY;
		}
		else if (verticalAngle == 0)
		{
			newLPY = radius + EPY;
		}
		else
		{
			calc2 = (newLPZ - EPZ) / tan(verticalAngle * M_PI / 180);
			newLPY = calc2 + EPY;
		}

		LookatPoint->SetZ(newLPZ);
		LookatPoint->SetY(newLPY);
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

void Camera::Update(ERUNSTATE& sceneState)
{

		ModifyCameraXRotation(myInputHandler->getAction(ACTION_ROTATECAMERA_X));
		ModifyCameraYRotation(myInputHandler->getAction(ACTION_ROTATECAMERA_Y));

		ModifyCameraForward(myInputHandler->getAction(ACTION_ZAXISMOVE));
		ModifyCameraHeight(myInputHandler->getAction(ACTION_YAXISMOVE));
		ModifyCameraSide(myInputHandler->getAction(ACTION_XAXISMOVE));

		if (myInputHandler->getAction(ACTION_EXIT) < 0)
		{
			sceneState = EXIT;		//Checks wether the a inputdevice returns the exit action.
								//Switches state to exit, which cancels the update loop.
								//Which in turn exits the program.
		}

		else if (myInputHandler->getAction(ACTION_TOGGLEDEBUG) < 0)
		{
			if (sceneState == RUNNING)
			{
				ShowCursor(TRUE);	
				sceneState = DEBUG;
			}

			else if (sceneState == DEBUG)
			{
				ShowCursor(FALSE);
				sceneState = RUNNING;
			}

			/*	To fix, atm multiple update loops are done in a single mouse poll. Meaning the debug will always be toggled off after being turned on.
				Potential fixes: Poll less (involve a counter?)
				Lock state for X amount of time
				Praise satan			
			*/
		}

		UpdateCameraMatrix();

}

void Camera::UpdateOculus(Renderer* renderer, const OVR::Util::Render::StereoEyeParams& params, OVR::Util::Render::StereoConfig SConfig, ERUNSTATE& sceneState)
{
	renderer->setViewMatrixOculus(params, SConfig);
	renderer->setProjectionMatrixOculus(params, SConfig);

	ModifyCameraXRotation(myInputHandler->getAction(ACTION_ROTATECAMERA_X));
	ModifyCameraYRotation(myInputHandler->getAction(ACTION_ROTATECAMERA_Y));
	
	ModifyCameraForward(myInputHandler->getAction(ACTION_ZAXISMOVE));
	ModifyCameraHeight(myInputHandler->getAction(ACTION_YAXISMOVE));
	ModifyCameraSide(myInputHandler->getAction(ACTION_XAXISMOVE));

	if (myInputHandler->getAction(ACTION_EXIT) < 0)
	{
		sceneState = EXIT;
	}

	else if (myInputHandler->getAction(ACTION_TOGGLEDEBUG) < 0)
	{
		if (sceneState == RUNNING)
		{
			ShowCursor(TRUE);	//To be expanded on, switch to debug run mode instead.
								//So that further logic can be applied based on this.
			sceneState = DEBUG;
		}
		else if (sceneState == DEBUG)
		{
			ShowCursor(FALSE);
			sceneState = RUNNING;
		}
	}

	UpdateCameraMatrix();
}

void Camera::UpdateCameraMatrix()
{
	Position->MatrixLookAtLH(EyePoint, LookatPoint, UpVector);
}
