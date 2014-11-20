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

private:
	D3DXVECTOR3 vector;

};



#endif