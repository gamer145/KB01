#include "VertexBufferWrapper.h"

	/**
	* Function: VertexBufferWrapper::VertexBufferWrapper()
	* Description: Constructor
	*/
	VertexBufferWrapper::VertexBufferWrapper()
	{
		LPDIRECT3DVERTEXBUFFER9 v_buffer = NULL;

		VertexBuffer = v_buffer;
				
	};

	/**
	* Function: VertexBufferWrapper::~VertexBufferWrapper()
	* Description: Destructor
	*/
	VertexBufferWrapper::~VertexBufferWrapper()
	{
		delete VertexBuffer;
	};

	/**
	* Function: VertexBufferWrapper::SetVertexBuffer(LPDIRECT3DVERTEXBUFFER9 _VertexBuffer)
	* Description: Sets the vertexbuffer that's contained within this class
	*/
	void VertexBufferWrapper::SetVertexBuffer(LPDIRECT3DVERTEXBUFFER9 _VertexBuffer)

	{
		VertexBuffer = _VertexBuffer;
	};

	/**
	* Function: VertexBufferWrapper::GetVertexBuffer()
	* Description: Gets the vertexbuffer that's contained within this class
	*/
	LPDIRECT3DVERTEXBUFFER9 VertexBufferWrapper::GetVertexBuffer()
	{
		if (VertexBuffer != NULL) {
			return VertexBuffer;
		}
		
	};

