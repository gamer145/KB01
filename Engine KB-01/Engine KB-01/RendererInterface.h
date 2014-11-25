#ifndef RENDERERINTERFACE_H
#define RENDERERINTERFACE_H

//#include <d3dx9.h>
#include <string>
#include <map>
#include "Model.h"
//#include "VisualObject.h"
#include "Window_Manager.h"
#include "EngineKB01Definitions.h"
#include "Window.h"
#include "Model.h"
#include "Entity.h"
#include "IndexBufferWrapper.h"
#include "MaterialWrapper.h"
#include "MeshWrapper.h"
#include "MatrixWrapper.h"
#include "TextureWrapper.h"
#include "VertexBufferWrapper.h"

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
	virtual HRESULT LoadMeshFromFile(std::string filename, EDWORD options, MeshWrapper* destination) = 0;
	virtual HRESULT LoadTextureFromFile(std::string filename, EDWORD options, TextureWrapper* destination) = 0;
	virtual void DrawSubSet(std::string meshname) = 0;
	//virtual void DrawPrimitive() = 0;
	//virtual void SetVertexFormat() = 0;
	virtual void SetUpWorld(MatrixWrapper* WorldMatrix, MatrixWrapper* CameraMatrix, MatrixWrapper* ProjectionMatrix) = 0;
//	virtual void* get3DDevice() = 0;
	virtual HRESULT InitD3D(HWND hWnd) = 0;
	virtual void addTexture(std::string textname, TextureWrapper* Text) = 0;
	virtual void addMesh(std::string meshname, MeshWrapper* Mesh) = 0;
	virtual void setDrawWindow(Window* windowtodrawin) = 0;
	//virtual void setStreamSource(VertexBufferWrapper *pStreamData, UINT OffsetInBytes) = 0;
	virtual void CreateVertexBuffer(int heightmapvertex, EDWORD usage, EDWORD fvf, EPOOL pool, std::string vertexbuffername, HANDLE handle) = 0;
	virtual HRESULT CreateIndexBuffer(int length, EDWORD usage, EFORMAT format, EPOOL pool, std::string indexbuffername, HANDLE* handle) = 0;
	virtual HRESULT LockVertexBuffer(std::string vertexbuffername, int offsettolock, int sizetolock, void** pbdata, EDWORD flags) = 0;
	virtual HRESULT UnlockVertexBuffer(std::string vertexbuffername) = 0;
	virtual HRESULT LockIndexBuffer(std::string indexbuffername, int offsettolock, int sizetolock, void** pbdata, EDWORD flags) = 0;
	virtual HRESULT UnlockIndexBuffer(std::string indexbuffername) = 0;
	virtual bool VertexBufferExists(std::string vertexbuffername) = 0;
	virtual bool IndexBufferExists(std::string indexbuffername) = 0;
	virtual HRESULT setTransform(ETRANSFORMSTATETYPE transform, MatrixWrapper* matrix) = 0;
	virtual HRESULT SetStreamSource(int streamnumber, std::string vertexbuffername, int offset, int stride) = 0;
	virtual HRESULT SetFVF(EDWORD FVF) = 0;
	virtual HRESULT SetIndices(std::string indexbuffername) = 0;
	virtual HRESULT DrawIndexedPrimitive(EPRIMITIVETYPE type, int basevertexindex, int minvertexindex, int numvertices, int startindex, int primcount) = 0;
	virtual HRESULT LoadShaderFromFile(std::string shadername, std::string shaderfilepath, std::string shaderfunctionname) = 0;
	virtual void Clear(EDWORD count, EDWORD flags, ECOLOR color, float z, EDWORD stencil) = 0;
	virtual void BeginS() = 0;
	virtual void EndS() = 0;
	virtual void Present() = 0;
	virtual std::map<std::string, MeshWrapper*> getMeshes() = 0;
	virtual std::map<std::string, TextureWrapper*> getTextures() = 0;
};

#endif