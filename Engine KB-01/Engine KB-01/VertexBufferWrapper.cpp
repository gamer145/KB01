#include "VertexBufferWrapper.h"

	VertexBufferWrapper::VertexBufferWrapper()
	{
		VertexBuffer = new IDirect3DVertexBuffer9*;
				
	};

	VertexBufferWrapper::~VertexBufferWrapper()
	{

	};


	void VertexBufferWrapper::SetVertexBuffer(IDirect3DVertexBuffer9** _VertexBuffer)

	{
		VertexBuffer = _VertexBuffer;
	};


	IDirect3DVertexBuffer9** VertexBufferWrapper::GetVertexBuffer()
	{
		
		return VertexBuffer;
	};

