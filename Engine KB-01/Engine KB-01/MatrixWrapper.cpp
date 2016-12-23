#include "MatrixWrapper.h"



	/**
	* Function: MatrixWrapper::MatrixWrapper()
	* Description: constructor
	*/
    MatrixWrapper::MatrixWrapper()
	{
		D3DXMATRIX newMatrix;
		D3DXMatrixIdentity(&newMatrix);
		matrix = newMatrix;
	}

	/**
	* Function: MatrixWrapper::~MatrixWrapper()
	* Description: Destructor
	*/
	MatrixWrapper::~MatrixWrapper()
	{

	}

	/**
	* Function: MatrixWrapper::SetMatrix(D3DXMATRIX newMatrix)
	* Description: Sets the matrix that's contained within this class
	*/
	void MatrixWrapper::SetMatrix(D3DXMATRIX newMatrix)
	{
		matrix = newMatrix;
	}

	/**
	* Function: MatrixWrapper::GetMatrix()
	* Description: Gets the matrix that's contained within this class
	*/
	D3DXMATRIX MatrixWrapper::GetMatrix()
	{
		return matrix;
	}

	/**
	* Function: MatrixWrapper::MatrixRotationX(float x)
	* Description: Rotates the matrix using an X coordinate
	*/
	void MatrixWrapper::MatrixRotationX(float x)
	{
		D3DXMatrixRotationX(&matrix, x);
	}

	/**
	* Function: MatrixWrapper::MatrixRotationY(float y)
	* Description: Rotates the matrix using a Y coordinate
	*/
	void MatrixWrapper::MatrixRotationY(float y)
	{
		D3DXMatrixRotationY(&matrix, y);
	}

	/**
	* Function: MatrixWrapper::MatrixRotationZ(float z)
	* Description: Rotates the matrix using a Z coordinate
	*/
	void MatrixWrapper::MatrixRotationZ(float z)
	{
		D3DXMatrixRotationZ(&matrix, z);
	}

	/**
	* Function: MatrixWrapper::MatrixTranslation(float x, float y, float z)
	* Description: Translates the matrix using the coordinates given
	*/
	void MatrixWrapper::MatrixTranslation(float x, float y, float z)
	{
		D3DXMatrixTranslation(&matrix, x, y, z);
	}

	/**
	* Function: MatrixWrapper::MatrixScaling(float x, float y, float z)
	* Description: Scales the matrix using the coordinates given
	*/
	void MatrixWrapper::MatrixScaling(float x, float y, float z)
	{
		D3DXMatrixScaling(&matrix, x, y, z);
	}

	/**
	* Function: MatrixWrapper::MatrixLookAtLH(VectorWrapper* eyepoint, VectorWrapper* lookatpoint, VectorWrapper* upvector)
	* Description: The required function to make a look at matrix, builds it left handed (LH)
	*/
	void MatrixWrapper::MatrixLookAtLH(VectorWrapper* eyepoint, VectorWrapper* lookatpoint, VectorWrapper* upvector)
	{
		D3DXMatrixLookAtLH(&matrix, &eyepoint->GetVector(), &lookatpoint->GetVector(), &upvector->GetVector());
	}

	/**
	* Function: MatrixWrapper::MatrixPerspectiveFovLH(float fovy, float aspect, float zn, float zf)
	* Description: The required function to make a perspectiv matrix, builds a left handed (LH) perspective Matrix
	*/
	void MatrixWrapper::MatrixPerspectiveFovLH(float fovy, float aspect, float zn, float zf)
	{
		D3DXMatrixPerspectiveFovLH(&matrix, fovy, aspect, zn, zf);
	}

