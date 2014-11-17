#include "MatrixWrapper.h"



    MatrixWrapper::MatrixWrapper(D3DXMATRIX newMatrix)
	{
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



