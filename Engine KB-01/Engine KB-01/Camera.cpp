#include "Camera.h"

Camera::Camera()
{
	EyePoint = &VectorWrapper(0, 0, 0);
	LookatPoint = &VectorWrapper(0, 0, 0);
	UpVector = &VectorWrapper(0, 0, 0);

	Position = new MatrixWrapper();
	ProjectionMatrix = new MatrixWrapper();
	CameraLogger = Logger::GetLogger();
}

Camera::~Camera()
{
	if (EyePoint != NULL) {
		delete EyePoint;
	}
	if (LookatPoint != NULL) {
		delete LookatPoint;
	}
	if (UpVector != NULL) {
		delete UpVector;
	}

	if (ProjectionMatrix != NULL) {
		delete ProjectionMatrix;
	}
	if (myInputHandler != NULL) {
		delete myInputHandler;
	}
	if (CameraLogger != NULL) {
		CameraLogger = NULL;
		delete CameraLogger;
	}
	

}


/**
* Function:	Camera::CalculateAngles()
* Description: Function used to aid in rotation based on current position in the world and look at point. 
* However not worked out yet
*/
void Camera::CalculateAngles()
{
	horizontalAngle = 90;
	verticalAngle = 90;
}

/**
* Function:	Camera::Initialize()
* Description: Initializes the components of the Camera, needs to be called after Eye, LookAt and Up are set
*/
void Camera::Initialize()
{
	radius = (abs(LookatPoint->GetZ()) + abs(EyePoint->GetZ()));
	Position->MatrixLookAtLH( EyePoint, LookatPoint, UpVector );
	ProjectionMatrix->MatrixPerspectiveFovLH(M_PI / 4, 1.0f, 1.0f, 100000.0f);
	CalculateAngles();
}

/**
* Function:	Camera::SetInputHandler()
* Description: Sets a new inputHandler
*/
void Camera::SetInputHandler(InputHandlerInterface* IH)
{
	myInputHandler = IH;
}


/**
* Function:	Camera::SetEyePoint()
* Description: Sets a new Eyepoint
*/
void Camera::SetEyePoint(VectorWrapper* newVector)
{
	EyePoint = newVector;
}


/**
* Function:	Camera::SetLookAtPoint()
* Description: Sets a new LookAtPoint
*/
void Camera::SetLookAtPoint(VectorWrapper* newVector)
{
	LookatPoint = newVector;
}

/**
* Function:	Camera::SetUpVector()
* Description: Sets a new UpVector
*/
void Camera::SetUpVector(VectorWrapper* newVector)
{
	UpVector = newVector;
}

/**
* Function:	Camera::ModifyCameraForward()
* Description: Logic for Forward and Backward Movement. The movement is done in a 2DPlane.
* Logic is based on the position of the camera, and where it's looking at.
*/
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

/**
* Function:	Camera::ModifyCameraHeight()
* Description: Modifies the height of the Camera and Look At point to make sure the camera doesn't rotate.
*/
void Camera::ModifyCameraHeight(float modifier)
{
	EyePoint->ModY(modifier);
	LookatPoint->ModY(modifier);
}


/**
* Function:	Camera::ModifyCameraSide()
* Description: Logic for sideways Movement. The movement is done in a 2DPlane. 
* Logic is based on the position of the camera, and where it's looking at.
*/
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

/**
* Function:	Camera::ModifyCameraXRotation()
* Description: Rotates the camera around, using ratio's to keep track of how far it has 
* rotated and how far along it has to move to ensure returning to its original point.
* Has guards to prevent dividing by 0, although this means it can ocasionally skip by a very small margin
*/
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


/**
* Function:	Camera::ModifyCameraYRotation()
* Description: Rotates the camera around, using ratio's to keep track of how far it has
* rotated and how far along it has to move to ensure returning to its original point.
* Has guards to prevent dividing by 0, although this means it can ocasionally skip by a very small margin
* Not fully working yet, needs more logic and proper angle calculations to properly rotate
*/
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

/**
* Function:	Camera::ModifyCameraZRotation()
* Description: Rotates the camera around, using ratio's to keep track of how far it has
* rotated and how far along it has to move to ensure returning to its original point.
* Not Implemented yet, also sickening to imagine
*/
void Camera::ModifyCameraZRotation(float modifier)
{
	//ZAngle += modifier;
}

/**
* Function:	Camera::getProjectionMatrix()
* Description: Returns the projectionMatrix used in renderer to get the projection plane set up, 
* allowing to draw 3D on a 2D screen
*/
MatrixWrapper* Camera::getProjectionMatrix()
{
	return ProjectionMatrix;
}

/**
* Function:	Camera::Update()
* Description: The main update loop, where it talks to its InputHandler, asking whether it knowns any Action Types. 
* The inputhandler will in turn ask it's listeners whether they know this action type. 
* All feedback eventually comes back here in camera and the argument provided will determine to what degree modifications need to be made
*/
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
				CameraLogger->WriteToFile(Error, "Debug aan, cursor zou zichtbaar moeten zijn");
			}

			else if (sceneState == DEBUG)
			{
				ShowCursor(FALSE);
				sceneState = RUNNING;
				CameraLogger->WriteToFile(Error, "Debug uit, cursor zou onzichtbaar moeten zijn");
			}
		}

		UpdateCameraMatrix();

}

/**
* Function:	Camera::UpdateOculus()
* Description: The main Oculus update loop, where it talks to its InputHandler, asking whether it knowns any Action Types.
* The inputhandler will in turn ask it's listeners whether they know this action type.
* All feedback eventually comes back here in camera and the argument provided will determine to what degree modifications need to be made
* Work in progress, not fully implemented yet. Should do mostly the same as the normal update loop, but needs more
*/
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

/**
* Function:	Camera::UpdateCameraMatrix()
* Description: Combines all modifications and updates the entirety of the camera
*/
void Camera::UpdateCameraMatrix()
{
	Position->MatrixLookAtLH(EyePoint, LookatPoint, UpVector);
}
