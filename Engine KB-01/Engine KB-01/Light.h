#ifndef LIGHT_H
#define LIGHT_H

#include "Entity.h"
#include "EngineKB01Definitions.h"

class Light : public Entity
{
public:
	//Constructor
	Light();

	//Destructor
	~Light();

	//Intializes the Light Object
	void Initialize();

	//Returns the LightType
	LIGHTTYPE getLightType();

	//Sets a new lightType for this specific object
	void setLightType(LIGHTTYPE newLightType);

	//Returns the light intensity
	float getIntensity();

	//Sets a new light intensity
	void setIntensity(float newIntensity);

	//Returns the direction the light is in
	VectorWrapper* getDirection();

	//Sets a new direction the light is in
	void setDirection(VectorWrapper* newDirection);

	//The light handling code, work in progress. Not implemented yet. Trial runs were done with dummy code
	void Project();

private:
	//The light type of the Light
	LIGHTTYPE myLightType;

	//The intensity of the Light
	float myIntensity;

	//The direction the light is in
	VectorWrapper* myDirection;
};

#endif

