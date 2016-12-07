#include "Light.h"


Light::Light()
{

}


Light::~Light()
{
	if (myDirection != NULL) {
		delete myDirection;
	}
}

void Light::Initialize()
{

}

LIGHTTYPE Light::getLightType()
{
	return myLightType;
}

void Light::setLightType(LIGHTTYPE newLightType)
{
	myLightType = newLightType;
}

float Light::getIntensity()
{
	return myIntensity;
}

void Light::setIntensity(float newIntensity)
{
	myIntensity = newIntensity;
}

VectorWrapper* Light::getDirection()
{
	return myDirection;
}

void Light::setDirection(VectorWrapper* newDirection)
{
	myDirection = newDirection;
}

void Light::Project()
{
	
}
