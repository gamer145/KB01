#ifndef _MATRIXWRAPPER_H_
#define _MATRIXWRAPPER_H_

#include <d3dx9.h>



	class MatrixWrapper
	{
	public:
		MatrixWrapper(D3DXMATRIX newMatrix);
		~MatrixWrapper();
		void SetMatrix(D3DXMATRIX newMatrix);
		D3DXMATRIX GetMatrix();
	private:
		D3DXMATRIX matrix;

	};



#endif