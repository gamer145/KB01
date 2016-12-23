#include "VectorWrapper.h"


/**
* Function: VectorWrapper::VectorWrapper()
* Description:Constructor
*/
VectorWrapper::VectorWrapper()
{

}

/**
* Function: VectorWrapper::VectorWrapper(float x, float y, float z)
* Description: Constructor with arguments which auto sets
*/
VectorWrapper::VectorWrapper(float x, float y, float z)
{
	vector = D3DXVECTOR3(x, y, z);
}

/**
* Function: VectorWrapper::~VectorWrapper()
* Description: Destructor
*/
VectorWrapper::~VectorWrapper()
{
	
}

/**
* Function: VectorWrapper::SetVector(D3DXVECTOR3 newVector)
* Description: Sets a new Vector
*/
void VectorWrapper::SetVector(D3DXVECTOR3 newVector)
{
	vector = newVector;
}

/**
* Function: VectorWrapper::Normalize()
* Description: Normalizes the Vector that calls this function to Unit Length.
*/
void VectorWrapper::Normalize()
{
	D3DXVec3Normalize(&vector, &vector);
}

/**
* Function: VectorWrapper::GetVector()
* Description: Gets the Vector itself
*/
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

//Changes the X value of the vector to the provided value
void VectorWrapper::SetX(float newX)
{
	vector.x = newX;
}

//Changes the Y value of the vector to the provided value
void VectorWrapper::SetY(float newY)
{
	vector.y = newY;
}

//Changes the Z value of the vector to the provided value
void VectorWrapper::SetZ(float newZ)
{
	vector.z = newZ;
}

//Gets the X value of the vector
float VectorWrapper::GetX()
{
	return vector.x;
}

//Gets the Y value of the vector
float VectorWrapper::GetY()
{
	return vector.y;
}

//Gets the Z value of the vector
float VectorWrapper::GetZ()
{
	return vector.z;
}



