#ifndef _INDEXBUFFERWRAPPER_H_
#define _INDEXBUFFERWRAPPER_H_

#include <d3dx9.h>


	class IndexBufferWrapper
	{
	public:
		IndexBufferWrapper(IDirect3DIndexBuffer9** _IndexBuffer);
		~IndexBufferWrapper();
		//sets the indexbuffer that's contained within this class
		void SetIndexBuffer(IDirect3DIndexBuffer9** _IndexBuffer);
		//gets the indexbuffer that's contained within this class
		IDirect3DIndexBuffer9** GetIndexBuffer();


	private:
		IDirect3DIndexBuffer9** IndexBuffer;
	};


#endif