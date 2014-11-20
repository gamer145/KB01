#ifndef CAMERA_H
#define CAMERA_H

#include "Entity.h"
#include "InputHandler.h"
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
	void SetInputHandler(InputHandler* IH);

	void ModifyWorldX(float modifier);
	void ModifyWorldY(float modifier);
	void ModifyWorldZ(float modifier);
	void ModifyWorldXAngle(float modifier);
	void ModifyWorldYAngle(float modifier);
	void ModifyWorldZAngle(float modifier);

	void Update();

	MatrixWrapper* getProjectionMatrix();
	MatrixWrapper* getOffSetMatrix();

private:
	VectorWrapper* EyePoint;
	VectorWrapper* LookatPoint;
	VectorWrapper* UpVector;
	MatrixWrapper* ProjectionMatrix;
	InputHandler* myInputHandler;
	void UpdateOffSetMatrix();
	float x,y,z, XAngle, YAngle, ZAngle;
	int mousewheel, xpos, ypos;
	MatrixWrapper* OffSetMatrix;
	MatrixWrapper* WorldXRotation;
	MatrixWrapper* WorldYRotation;
	MatrixWrapper* WorldZRotation;
	MatrixWrapper* WorldRotation;
	MatrixWrapper* WorldPosition;
	
};

#endif