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

