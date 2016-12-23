#ifndef _VERTEXBUFFERWRAPPER_H_
#define _VERTEXBUFFERWRAPPER_H_

#include <d3dx9.h>

//Wrappers are used to make the rest of the engine not dependant on a specific framework, in this case directX.

	class VertexBufferWrapper
	{
	public:
		//Constructor
		VertexBufferWrapper();

		//Destructor
		~VertexBufferWrapper();

		//Sets the vertexbuffer that's contained within this class
		void SetVertexBuffer(LPDIRECT3DVERTEXBUFFER9 _VertexBuffer);

		//Gets the vertexbuffer that's contained within this class
		LPDIRECT3DVERTEXBUFFER9 GetVertexBuffer();
	private:
		//The directX vertexBuffer itself
		LPDIRECT3DVERTEXBUFFER9 VertexBuffer;
	};



#endif