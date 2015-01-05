#ifndef _VECTORWRAPPER_H_
#define _VECTORWRAPPER_H_

#include <d3dx9.h>

class VectorWrapper
{
public:
	VectorWrapper(float x, float y, float z);
	~VectorWrapper();
	void SetVector(D3DXVECTOR3 newVector);
	D3DXVECTOR3 GetVector();

	void SetX(float newX);
	void SetY(float newY);
	void SetZ(float newZ);


	void ModX(float modifier);
	void ModY(float modifier);
	void ModZ(float modifier);

	float GetX();
	float GetY();
	float GetZ();

private:
	D3DXVECTOR3 vector;

};



#endif