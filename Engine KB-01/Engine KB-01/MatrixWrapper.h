#ifndef _MATRIXWRAPPER_H_
#define _MATRIXWRAPPER_H_

#include <d3dx9.h>
#include "VectorWrapper.h"


	class MatrixWrapper
	{
	public:
		MatrixWrapper();
		~MatrixWrapper();
		//sets the matrix that's contained within this class
		void SetMatrix(D3DXMATRIX newMatrix);
		//gets the matrix that's contained within this class
		D3DXMATRIX GetMatrix();
		//Rotates the matrix using an X coordinate
		void MatrixRotationX(float x);
		//Rotates the matrix using a Y coordinate
		void MatrixRotationY(float y);
		//Rotates the matrix using a Z coordinate
		void MatrixRotationZ(float z);
		//Translates the matrix using the coordinates given
		void MatrixTranslation(float x, float y, float z);
		//Scales the matrix using the coordinates given
		void MatrixScaling(float x, float y, float z);
		void MatrixLookAtLH(VectorWrapper* x, VectorWrapper* y, VectorWrapper* z);
		void MatrixPerspectiveFovLH(float fovy, float aspect, float zn, float zf);

	private:
		D3DXMATRIX matrix;

	};



#endif