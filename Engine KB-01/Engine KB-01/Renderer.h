#ifndef RENDERER_H
#define RENDERER_H

#include <d3d9.h>
#include <d3dx9.h>
#include <dxerr.h>
#include "RendererInterface.h"
#include <mmsystem.h>
#include <strsafe.h>
#include <vector>



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
	HRESULT LoadMeshFromFile(std::string filename, EDWORD options, MeshWrapper* destination);
	HRESULT LoadTextureFromFile(std::string filename, EDWORD options, TextureWrapper* destination);
	void DrawSubSet(std::string meshname);
	//void DrawPrimitive();
	//void SetVertexFormat();
	void SetUpWorld(MatrixWrapper* WorldMatrix, MatrixWrapper* CameraMatrix, MatrixWrapper* ProjectionMatrix);
	//void* get3DDevice();
	HRESULT InitD3D( HWND hWnd );
	void addTexture(std::string textname, TextureWrapper* Text);
	void addMesh(std::string meshname, MeshWrapper* Mesh);
	void setDrawWindow(Window* windowtodrawin);
	//void setStreamSource(VertexBufferWrapper *pStreamData, UINT OffsetInBytes);
	void CreateVertexBuffer(int heightmapvertex, EDWORD usage, EDWORD fvf, EPOOL pool, std::string vertexbuffername, HANDLE handle);
	HRESULT CreateIndexBuffer(int length, EDWORD usage, EFORMAT format, EPOOL pool, std::string indexbuffername, HANDLE* handle);
	HRESULT LockVertexBuffer(std::string vertexbuffername, int offsettolock, int sizetolock, void* pbdata, EDWORD flags);
	HRESULT UnlockVertexBuffer(std::string vertexbuffername);
	HRESULT LockIndexBuffer(std::string indexbuffername, int offsettolock, int sizetolock, void* pbdata, EDWORD flags);
	HRESULT UnlockIndexBuffer(std::string indexbuffername);
	bool VertexBufferExists(std::string vertexbuffername);
	bool IndexBufferExists(std::string indexbuffername);
	HRESULT setTransform(ETRANSFORMSTATETYPE transform, MatrixWrapper* matrix);
	HRESULT SetStreamSource(int streamnumber, std::string vertexbuffername, int offset, int stride);
	HRESULT SetFVF(EDWORD FVF);
	HRESULT SetIndices(std::string indexbuffername);
	HRESULT DrawIndexedPrimitive(EPRIMITIVETYPE type, int basevertexindex, int minvertexindex, int numvertices, int startindex, int primcount);
	void Clear(EDWORD count, EDWORD flags, ECOLOR color, float z, EDWORD stencil);
	void BeginS();
	void EndS();
	void Present();
	std::map<std::string, MeshWrapper*> getMeshes();
	std::map<std::string, TextureWrapper*> getTextures();


private:

	LPDIRECT3D9         g_pD3D; 
    LPDIRECT3DDEVICE9   g_pd3dDevice; 
	Window* myWindow;
	bool keepRendering;
	
	std::map<std::string, MeshWrapper*> Meshes;
	std::map<std::string, TextureWrapper*> Textures;

	std::map<std::string, IDirect3DVertexBuffer9**> VertexBuffers;
	std::map<std::string, IDirect3DIndexBuffer9**> IndexBuffers;
	
};

#endif
