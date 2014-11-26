#ifndef CAMERA_H
#define CAMERA_H

#include "Entity.h"
#include "InputHandlerInterface.h"
#include "MatrixWrapper.h"
#include "VectorWrapper.h"

class Camera : public Entity
{
public:
	Camera();
	~Camera();	
	void Initialize();
	void SetEyePoint(VectorWrapper* newVector);
	void SetLookAtPoint(VectorWrapper* newVector);
	void SetUpVector(VectorWrapper* newVector);
	void SetInputHandler(InputHandlerInterface* IH);
	
	ERUNSTATE Update();

	MatrixWrapper* getProjectionMatrix();

private:
	VectorWrapper* EyePoint;
	VectorWrapper* LookatPoint;
	VectorWrapper* UpVector;
	MatrixWrapper* ProjectionMatrix;
	InputHandlerInterface* myInputHandler;
	void UpdateCameraMatrix();
	float x,y,z, XAngle, YAngle, ZAngle;
	int mousewheel, xpos, ypos;

	void ModifyWorldX(float modifier);
	void ModifyWorldY(float modifier);
	void ModifyWorldZ(float modifier);
	void ModifyWorldXAngle(float modifier);
	void ModifyWorldYAngle(float modifier);
	void ModifyWorldZAngle(float modifier);
};

#endif