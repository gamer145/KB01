#include "MatrixWrapper.h"



    MatrixWrapper::MatrixWrapper()
	{
		D3DXMATRIX newMatrix;
		D3DXMatrixIdentity(&newMatrix);
		matrix = newMatrix;
	}

	MatrixWrapper::~MatrixWrapper()
	{

	}

	void MatrixWrapper::SetMatrix(D3DXMATRIX newMatrix)
	{
		matrix = newMatrix;
	}

	D3DXMATRIX MatrixWrapper::GetMatrix()
	{
		return matrix;
	}

	void MatrixWrapper::MatrixRotationX(float x)
	{
		D3DXMatrixRotationX(&matrix, x);
	}

	void MatrixWrapper::MatrixRotationY(float y)
	{
		D3DXMatrixRotationY(&matrix, y);
	}

	void MatrixWrapper::MatrixRotationZ(float z)
	{
		D3DXMatrixRotationZ(&matrix, z);
	}
	void MatrixWrapper::MatrixTranslation(float x, float y, float z)
	{
		D3DXMatrixTranslation(&matrix, x, y, z);
	}

	void MatrixWrapper::MatrixScaling(float x, float y, float z)
	{
		D3DXMatrixScaling(&matrix, x, y, z);
	}

	void MatrixWrapper::MatrixLookAtLH(VectorWrapper* eyepoint, VectorWrapper* lookatpoint, VectorWrapper* upvector)
	{
		D3DXMatrixLookAtLH(&matrix, &eyepoint->GetVector(), &lookatpoint->GetVector(), &upvector->GetVector());
	}

	void MatrixWrapper::MatrixPerspectiveFovLH(float fovy, float aspect, float zn, float zf)
	{
		D3DXMatrixPerspectiveFovLH(&matrix, fovy, aspect, zn, zf);
	}

