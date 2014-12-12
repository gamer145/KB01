#ifndef LIGHT_H
#define LIGHT_H

#include "Entity.h"
#include "EngineKB01Definitions.h"

class Light : public Entity
{
public:
	Light();
	~Light();
	void Initialize();

	LIGHTTYPE getLightType();
	void setLightType(LIGHTTYPE newLightType);

	float getIntensity();
	void setIntensity(float newIntensity);

	VectorWrapper* getDirection();
	void setDirection(VectorWrapper* newDirection);

private:
	LIGHTTYPE myLightType;
	float myIntensity;
	VectorWrapper* myDirection;
};

#endif

