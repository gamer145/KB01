#ifndef _VECTORWRAPPER_H_
#define _VECTORWRAPPER_H_

#include <d3dx9.h>

//Wrappers are used to make the rest of the engine not dependant on a specific framework, in this case directX.

class VectorWrapper
{
public:
	//Constructor without arguments, values need to be set at a later time
	VectorWrapper();

	//Constructor with arguments which auto sets
	VectorWrapper(float x, float y, float z);

	//Destructor
	~VectorWrapper();

	//Sets a new Vector
	void SetVector(D3DXVECTOR3 newVector);

	//Gets the Vector itself
	D3DXVECTOR3 GetVector();

	//Normalizes the Vector that calls this function to Unit Length.
	void Normalize();

	//Changes the X value of the vector to the provided value
	void SetX(float newX);

	//Changes the Y value of the vector to the provided value
	void SetY(float newY);

	//Changes the Z value of the vector to the provided value
	void SetZ(float newZ);

	//Modifies the X value of the vector with the provided value
	void ModX(float modifier);

	//Modifies the Y value of the vector with the provided value
	void ModY(float modifier);

	//Modifies the Z value of the vector with the provided value
	void ModZ(float modifier);

	//Gets the X value of the vector
	float GetX();

	//Gets the Y value of the vector
	float GetY();

	//Gets the Z value of the vector
	float GetZ();

private:
	//The DirectX Vector itself
	D3DXVECTOR3 vector;

};



#endif