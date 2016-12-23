#ifndef CAMERA_H
#define CAMERA_H

#include "Entity.h"
#include "InputHandlerInterface.h"
#include "MatrixWrapper.h"
#include "VectorWrapper.h"
#include "Renderer.h"

class Camera : public Entity
{
public:
	//Constructor
	Camera();

	//Destructor
	~Camera();	

	//Starts up the Camera, needs to be called after Eye, LookAt and Up are set
	void Initialize();

	//Sets the Eye point, the position of the Camera within the world
	void SetEyePoint(VectorWrapper* newVector);

	//Sets the look at Point, what the Eye is looking at
	void SetLookAtPoint(VectorWrapper* newVector);

	//Sets what's up doc
	void SetUpVector(VectorWrapper* newVector);

	//Sets the InputHandler attached to the camera
	void SetInputHandler(InputHandlerInterface* IH);

	//Calculates angles, to be used in rotations. Not worked out yet
	void CalculateAngles();

	//Update loop where input is checked and handled, if RUNSTATE changes due to input, the argument provided will be changed
	void Update(ERUNSTATE& sceneState);

	//Seperate update loop for the Oculus
	void UpdateOculus(Renderer* renderer, const OVR::Util::Render::StereoEyeParams& params, OVR::Util::Render::StereoConfig SConfig, ERUNSTATE& sceneState);

	//Returns the projection Matrix, used within the renderer to draw a 3D field on a 2D plane (the computer screen)
	MatrixWrapper* getProjectionMatrix();

private:
	//A vector of the EyePoint component of the camera. Basically, where is the 'eye'
	VectorWrapper* EyePoint;

	//A vector of the LookAtPoint component of the camera. Basically, where is the camera looking at
	VectorWrapper* LookatPoint;

	//A vector of the UpVector component of the camera. Basically, what direction is up
	VectorWrapper* UpVector;

	//A matrix to be used in 3 dimensional drawing, creates the effect of depth on the 2D screen that is the computer. Used internally by directX
	MatrixWrapper* ProjectionMatrix;

	//The attached InputHandler
	InputHandlerInterface* myInputHandler;

	//The attached Logger
	Logger* CameraLogger;

	//The angle, of the horizontal variant. What do you expect?
	float horizontalAngle;

	//The angle, of the vertical variant. What do you expect?
	float verticalAngle;

	//The radius
	float radius;

	//Updates the Camera based on what the modify functions below have done
	void UpdateCameraMatrix();

	//All these functions are based on input, and they modify a single component. 
	//After all modifications are done the actual matrix is updated in the method mentioned above

	//Modify the camera to move forward or backward
	void ModifyCameraForward(float modifier);

	//Modify the camera to go up or down
	void ModifyCameraHeight(float modifier);

	//Modify the camera to move left or right
	void ModifyCameraSide(float modifier);

	//Modify the camera to turn left or right
	void ModifyCameraXRotation(float modifier);

	//Modify the camera to turn up or down
	void ModifyCameraYRotation(float modifier);

	//Modify the camera to rotate around itself
	void ModifyCameraZRotation(float modifier);
};

#endif