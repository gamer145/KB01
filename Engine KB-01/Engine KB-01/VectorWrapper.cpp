#include "VectorWrapper.h"



VectorWrapper::VectorWrapper(float x, float y, float z)
{
	vector = D3DXVECTOR3(x, y, z);
}

VectorWrapper::~VectorWrapper()
{

}

void VectorWrapper::SetVector(D3DXVECTOR3 newVector)
{
	vector = newVector;
}

D3DXVECTOR3 VectorWrapper::GetVector()
{
	return vector;
}


//Adds an increment to the existing X value
void VectorWrapper::SetX(float newX)
{
	vector.x += newX;
}


//Adds an increment to the existing Y value
void VectorWrapper::SetY(float newY)
{
	vector.y += newY;
}

//Adds an increment to the existing Z value
void VectorWrapper::SetZ(float newZ)
{
	vector.z += newZ;
}


float VectorWrapper::GetX()
{
	return vector.x;
}

float VectorWrapper::GetY()
{
	return vector.y;
}

float VectorWrapper::GetZ()
{
	return vector.z;
}



