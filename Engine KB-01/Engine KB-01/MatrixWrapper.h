#ifndef _MATRIXWRAPPER_H_
#define _MATRIXWRAPPER_H_

#include <d3dx9.h>
#include "VectorWrapper.h"

//Wrappers are used to make the rest of the engine not dependant on a specific framework, in this case directX.

	class MatrixWrapper
	{
	public:
		//Constructor
		MatrixWrapper();

		//Destructor
		~MatrixWrapper();

		//Sets the matrix that's contained within this class
		void SetMatrix(D3DXMATRIX newMatrix);

		//Gets the matrix that's contained within this class
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

		//The required function to make a look at matrix, builds it left handed (LH)
		void MatrixLookAtLH(VectorWrapper* x, VectorWrapper* y, VectorWrapper* z);

		//The required function to make a perspectiv matrix, builds a left handed (LH) perspective Matrix
		void MatrixPerspectiveFovLH(float fovy, float aspect, float zn, float zf);

	private:
		//The D3DMATRIX itself
		D3DXMATRIX matrix;

	};



#endif