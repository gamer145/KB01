#ifndef _VERTEXBUFFERWRAPPER_H_
#define _VERTEXBUFFERWRAPPER_H_

#include <d3dx9.h>


	class VertexBufferWrapper
	{
	public:
		VertexBufferWrapper();
		~VertexBufferWrapper();
		//sets the vertexbuffer that's contained within this class
		void SetVertexBuffer(LPDIRECT3DVERTEXBUFFER9 _VertexBuffer);
		//gets the vertexbuffer that's contained within this class
		LPDIRECT3DVERTEXBUFFER9 GetVertexBuffer();
	private:
		LPDIRECT3DVERTEXBUFFER9 VertexBuffer;
	};



#endif