#ifndef _INDEXBUFFERWRAPPER_H_
#define _INDEXBUFFERWRAPPER_H_

#include <d3dx9.h>

//Wrappers are used to make the rest of the engine not dependant on a specific framework, in this case directX.

	class IndexBufferWrapper
	{
	public:
		//Constructor
		IndexBufferWrapper(IDirect3DIndexBuffer9** _IndexBuffer);

		//Destructor
		~IndexBufferWrapper();

		//Sets the indexbuffer that's contained within this class
		void SetIndexBuffer(IDirect3DIndexBuffer9** _IndexBuffer);

		//Gets the indexbuffer that's contained within this class
		IDirect3DIndexBuffer9** GetIndexBuffer();

	private:
		//The directX indexbuffer itself
		IDirect3DIndexBuffer9** IndexBuffer;
	};


#endif