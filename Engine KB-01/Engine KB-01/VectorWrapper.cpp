#include "VectorWrapper.h"



VectorWrapper::VectorWrapper()
{

}

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

void VectorWrapper::Normalize()
{
	D3DXVec3Normalize(&vector, &vector);
}

D3DXVECTOR3 VectorWrapper::GetVector()
{
	return vector;
}


//Adds an increment to the existing X value
void VectorWrapper::ModX(float modifier)
{
	vector.x += modifier;
}


//Adds an increment to the existing Y value
void VectorWrapper::ModY(float modifier)
{
	vector.y += modifier;
}

//Adds an increment to the existing Z value
void VectorWrapper::ModZ(float modifier)
{
	vector.z += modifier;
}

void VectorWrapper::SetX(float newX)
{
	vector.x = newX;
}

void VectorWrapper::SetY(float newY)
{
	vector.y = newY;
}

void VectorWrapper::SetZ(float newZ)
{
	vector.z = newZ;
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



