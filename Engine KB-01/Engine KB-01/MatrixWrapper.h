#ifndef _MATRIXWRAPPER_H_
#define _MATRIXWRAPPER_H_

#include <d3dx9.h>
#include "VectorWrapper.h"


	class MatrixWrapper
	{
	public:
		MatrixWrapper();
		~MatrixWrapper();
		void SetMatrix(D3DXMATRIX newMatrix);
		D3DXMATRIX GetMatrix();
		void MatrixRotationX(float x);
		void MatrixRotationY(float y);
		void MatrixRotationZ(float z);
		void MatrixTranslation(float x, float y, float z);
		void MatrixScaling(float x, float y, float z);
		void MatrixLookAtLH(VectorWrapper* x, VectorWrapper* y, VectorWrapper* z);
		void MatrixPerspectiveFovLH(float fovy, float aspect, float zn, float zf);

	private:
		D3DXMATRIX matrix;

	};



#endif