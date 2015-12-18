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
	Camera();
	~Camera();	
	void Initialize();
	void SetEyePoint(VectorWrapper* newVector);
	void SetLookAtPoint(VectorWrapper* newVector);
	void SetUpVector(VectorWrapper* newVector);
	void SetInputHandler(InputHandlerInterface* IH);
	void CalculateAngles();

	void Update(ERUNSTATE& sceneState);
	void UpdateOculus(Renderer* renderer, const OVR::Util::Render::StereoEyeParams& params, OVR::Util::Render::StereoConfig SConfig, ERUNSTATE& sceneState);

	MatrixWrapper* getProjectionMatrix();

private:
	VectorWrapper* EyePoint;
	VectorWrapper* LookatPoint;
	VectorWrapper* UpVector;

	MatrixWrapper* ProjectionMatrix;
	InputHandlerInterface* myInputHandler;
	Logger* CameraLogger;

	float horizontalAngle;
	float verticalAngle;
	float radius;

	void UpdateCameraMatrix();

	void ModifyCameraForward(float modifier);
	void ModifyCameraHeight(float modifier);
	void ModifyCameraSide(float modifier);
	void ModifyCameraXRotation(float modifier);
	void ModifyCameraYRotation(float modifier);
	void ModifyCameraZRotation(float modifier);
};

#endif