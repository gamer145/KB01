#ifndef RENDERERINTERFACE_H
#define RENDERERINTERFACE_H

#include <d3dx9.h>
#include <string>
#include "Model.h"
//#include "VisualObject.h"
#include "Window_Manager.h"

class Entity;
class RendererInterface
{
public:
	RendererInterface();
	~RendererInterface();
	virtual void CleanUp()=0;	

	/*

	*****************************************************
	-------------- initiate new renderer ----------------
	*****************************************************

	*/
	virtual HRESULT SetTexture(std::string)=0;
	virtual void DrawSubSet(std::string meshname)=0;
	//virtual void DrawPrimitive()=0;
	//virtual void SetVertexFormat()=0;
	virtual void* get3DDevice()=0;
	virtual HRESULT InitD3D( HWND hWnd )=0;
	virtual void addTexture(std::string textname, void* Text)=0;
	virtual void addMesh(std::string meshname, void* Mesh)=0;
};

#endif