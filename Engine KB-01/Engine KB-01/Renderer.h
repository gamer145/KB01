#ifndef RENDERER_H
#define RENDERER_H

#include <d3d9.h>
#include <d3dx9.h>
#include <dxerr.h>
#include "RendererInterface.h"
#include <mmsystem.h>
#include <strsafe.h>
#include <vector>
#include <string>
#include <map>
#include "Window.h"
#include "Model.h"
#include "Entity.h"

class Entity;
class Renderer : public RendererInterface
{
public:
	Renderer();
	~Renderer();
	void CleanUp();
	
	/*

	*****************************************************
	-------------- initiate new renderer ----------------
	*****************************************************

	*/

	
	HRESULT SetTexture(std::string);
	void DrawSubSet(std::string meshname);
	void DrawPrimitive();
	void SetVertexFormat();
	void SetUpWorld(D3DXMATRIX WorldMatrix, D3DXMATRIX CameraMatrix, D3DXMATRIX ProjectionMatrix);
	void* get3DDevice();
	HRESULT InitD3D( HWND hWnd );
	void addTexture(std::string textname, void* Text);
	void addMesh(std::string meshname, void* Mesh);
	void setDrawWindow(Window* windowtodrawin);
	void setStreamSource(IDirect3DVertexBuffer9 *pStreamData, UINT OffsetInBytes);
	void CreateVertexBuffer(int heightmapvertex, DWORD usage, DWORD fvf, D3DPOOL pool, void* vertexbuffer, HANDLE handle);
	HRESULT CreateIndexBuffer(int length, DWORD usage, D3DFORMAT format, D3DPOOL pool, void* Indexbuffer, HANDLE* handle);
	HRESULT setTransform(D3DTRANSFORMSTATETYPE transform, D3DMATRIX* matrix);
	HRESULT SetStreamSource(int streamnumber, IDirect3DVertexBuffer9* vertexbuffer, int offset, int stride);
	HRESULT SetFVF(DWORD FVF);
	HRESULT SetIndices(IDirect3DIndexBuffer9* indexbuffer);
	HRESULT DrawIndexedPrimitive(D3DPRIMITIVETYPE type, int basevertexindex, int minvertexindex, int numvertices, int startindex, int primcount);
	void Clear(DWORD count, DWORD flags, D3DCOLOR color, float z, DWORD stencil);
	void BeginS();
	void EndS();
	void Present();
	std::map<std::string, LPD3DXMESH> getMeshes();
	std::map<std::string, LPDIRECT3DTEXTURE9> getTextures();


private:

	LPDIRECT3D9         g_pD3D; 
    LPDIRECT3DDEVICE9   g_pd3dDevice; 
	Window* myWindow;
	bool keepRendering;
	
	std::map<std::string, LPD3DXMESH> Meshes;
    std::map<std::string, LPDIRECT3DTEXTURE9> Textures;
	
};

#endif
