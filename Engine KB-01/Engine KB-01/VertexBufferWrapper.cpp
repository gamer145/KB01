#include "VertexBufferWrapper.h"

	VertexBufferWrapper::VertexBufferWrapper()
	{
		LPDIRECT3DVERTEXBUFFER9 v_buffer = NULL;

		VertexBuffer = v_buffer;
				
	};

	VertexBufferWrapper::~VertexBufferWrapper()
	{
		delete VertexBuffer;
	};


	void VertexBufferWrapper::SetVertexBuffer(LPDIRECT3DVERTEXBUFFER9 _VertexBuffer)

	{
		VertexBuffer = _VertexBuffer;
	};


	LPDIRECT3DVERTEXBUFFER9 VertexBufferWrapper::GetVertexBuffer()
	{
		if (VertexBuffer != NULL) {
			return VertexBuffer;
		}
		
	};

