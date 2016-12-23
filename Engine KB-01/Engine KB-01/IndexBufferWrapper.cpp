#include "IndexBufferWrapper.h"

	/**
	* Function: IndexBufferWrapper::IndexBufferWrapper(IDirect3DIndexBuffer9** _IndexBuffer)
	* Description: Constructor
	*/
	IndexBufferWrapper::IndexBufferWrapper(IDirect3DIndexBuffer9** _IndexBuffer)
	{
		IndexBuffer = _IndexBuffer;
	};


	/**
	* Function: IndexBufferWrapper::~IndexBufferWrapper()
	* Description: Destructor
	*/
	IndexBufferWrapper::~IndexBufferWrapper()
	{
		if (IndexBuffer != NULL) {
			delete IndexBuffer;
		}
	};


	/**
	* Function: IndexBufferWrapper::SetIndexBuffer(IDirect3DIndexBuffer9** _IndexBuffer)
	* Description: Sets the indexbuffer that's contained within this class
	*/
	void IndexBufferWrapper::SetIndexBuffer(IDirect3DIndexBuffer9** _IndexBuffer)
	{
		IndexBuffer = _IndexBuffer;
	};



	/**
	* Function: IDirect3DIndexBuffer9** IndexBufferWrapper::GetIndexBuffer()
	* Description: Gets the indexbuffer that's contained within this class
	*/
	IDirect3DIndexBuffer9** IndexBufferWrapper::GetIndexBuffer()
	{
		return IndexBuffer;
	};


