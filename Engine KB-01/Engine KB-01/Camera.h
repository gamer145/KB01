#ifndef CAMERA_H
#define CAMERA_H

#include "Entity.h"
#include "InputHandler.h"

class Camera : public Entity
{
public:
	Camera();
	~Camera();	
	void Initialize();
	void SetEyePoint(D3DXVECTOR3 newVector);
	void SetLookAtPoint(D3DXVECTOR3 newVector);
	void SetUpVector(D3DXVECTOR3 newVector);
	void SetInputHandler(InputHandler* IH);

	void ModifyWorldX(float modifier);
	void ModifyWorldY(float modifier);
	void ModifyWorldZ(float modifier);
	void ModifyWorldXAngle(float modifier);
	void ModifyWorldYAngle(float modifier);
	void ModifyWorldZAngle(float modifier);

	void Update();

	D3DXMATRIX getProjectionMatrix();
	D3DXMATRIX getOffSetMatrix();

private:
	D3DXVECTOR3 EyePoint;
    D3DXVECTOR3 LookatPoint;
    D3DXVECTOR3 UpVector;
	D3DXMATRIX ProjectionMatrix;
	InputHandler* myInputHandler;
	void UpdateOffSetMatrix();
	float x,y,z, XAngle, YAngle, ZAngle;
	int mousewheel, xpos, ypos;
	D3DXMATRIX OffSetMatrix, WorldXRotation, WorldYRotation, WorldZRotation, WorldRotation, WorldPosition;
	
};

#endif