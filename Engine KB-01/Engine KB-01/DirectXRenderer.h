#ifndef DirectXRenderer_H
#define DirectXRenderer_H

#include <d3d9.h>
#include <d3dx9.h>
#include <dxerr.h>
#include "Renderer.h"
#include <mmsystem.h>
#include <strsafe.h>
#include <vector>
#include "Shader.h"


class Entity;
class DirectXRenderer : public Renderer
{
public:
	DirectXRenderer();
	~DirectXRenderer();
	void CleanUp();
	
	/*

	*****************************************************
	-------------- initiate new DirectXRenderer ----------------
	*****************************************************

	*/

	
	HRESULT SetTexture(std::string);
	HRESULT LoadMeshFromFile(std::string filename, EDWORD options, MeshWrapper* destination);
	HRESULT LoadTextureFromFile(std::string filename, EDWORD options, TextureWrapper* destination);
	void DrawSubSet(std::string meshname);
	//void DrawPrimitive();
	//void SetVertexFormat();
	void SetUpWorld(MatrixWrapper* CameraMatrix, MatrixWrapper* ProjectionMatrix);
	//void* get3DDevice();
	HRESULT InitD3D( HWND hWnd );
	void addTexture(std::string textname, TextureWrapper* Text);
	void addMesh(std::string meshname, MeshWrapper* Mesh);
	void setDrawWindow(Window* windowtodrawin);
	//void setStreamSource(VertexBufferWrapper *pStreamData, UINT OffsetInBytes);
	void CreateVertexBuffer(int heightmapvertex, EDWORD usage, EDWORD fvf, EPOOL pool, std::string vertexbuffername, HANDLE handle);
	HRESULT CreateIndexBuffer(int length, EDWORD usage, EFORMAT format, EPOOL pool, std::string indexbuffername, HANDLE* handle);
	HRESULT LockVertexBuffer(std::string vertexbuffername, int offsettolock, int sizetolock, void** pbdata, EDWORD flags);
	HRESULT UnlockVertexBuffer(std::string vertexbuffername);
	HRESULT LockIndexBuffer(std::string indexbuffername, int offsettolock, int sizetolock, void** pbdata, EDWORD flags);
	HRESULT UnlockIndexBuffer(std::string indexbuffername);
	bool VertexBufferExists(std::string vertexbuffername);
	bool IndexBufferExists(std::string indexbuffername);
	HRESULT setTransform(ETRANSFORMSTATETYPE transform, MatrixWrapper* matrix);
	HRESULT SetStreamSource(int streamnumber, std::string vertexbuffername, int offset, int stride);
	HRESULT SetFVF(EDWORD FVF);
	HRESULT SetIndices(std::string indexbuffername);
	HRESULT DrawIndexedPrimitive(EPRIMITIVETYPE type, int basevertexindex, int minvertexindex, int numvertices, int startindex, int primcount);
	HRESULT LoadShaderFromFile(std::string shadername, std::string shaderfilepath, std::string vertexshaderfunctionname, std::string pixelshadername);
	void SetShader(std::string shadername);
	void StopRenderingWithShaders();
	void SetZBuffer(bool state);
	void Clear(EDWORD count, EDWORD flags, ECOLOR color, float z, EDWORD stencil);
	void BeginS();
	void EndS();
	void Present();
	std::map<std::string, MeshWrapper*> getMeshes();
	std::map<std::string, TextureWrapper*> getTextures();



	//oculus test code from here on
	void RenderToTexture();
	void PresentWithWindow(HWND hwnd);
	void setViewportOculus(const OVR::Util::Render::StereoEyeParams& params);
	void setPixelShaderConstantsOculus(const OVR::Util::Render::StereoEyeParams& params, OVR::Util::Render::StereoConfig SConfig);
	void setupRenderToTextureOculus();
	void endRenderToTextureOculus();
	void renderSceneOculus(const OVR::Util::Render::StereoEyeParams& params, OVR::Util::Render::StereoConfig SConfig);
	void fillVertexBufferOculus(std::string key, VERTEX vertices[], int size);
	void createScreenQuadOculus(float width, float height);
	void renderEyeOculus(const OVR::Util::Render::StereoEyeParams& params, OVR::Util::Render::StereoConfig SConfig);
	void setViewMatrixOculus(const OVR::Util::Render::StereoEyeParams& params, OVR::Util::Render::StereoConfig SConfig);
	void setProjectionMatrixOculus(const OVR::Util::Render::StereoEyeParams& params, OVR::Util::Render::StereoConfig SConfig);
	bool OculusOrNah();
	void OculusNowYah(bool newOculus);

private:

	LPDIRECT3D9         g_pD3D; 
    LPDIRECT3DDEVICE9   g_pd3dDevice; 
	Window* myWindow;
	bool keepRendering;
	D3DXMATRIX WorldMatrix;
	
	

	std::map<std::string, MeshWrapper*> Meshes;
	std::map<std::string, TextureWrapper*> Textures;
	std::map<std::string, Shader*> Shaders;

	std::map<std::string, LPDIRECT3DVERTEXBUFFER9> VertexBuffers;
	std::map<std::string, LPDIRECT3DINDEXBUFFER9> IndexBuffers;
	
	//oculus code

	D3DXMATRIX scalarMultiply(D3DXMATRIX* matrix, float multiplyFactor);

	float backBufferWidth;
	float backBufferHeight;

	LPDIRECT3DTEXTURE9 fullSceneTexture = NULL, leftEyeTexture = NULL, rightEyeTexture = NULL;
	LPDIRECT3DSURFACE9 fullSceneSurface = NULL, leftEyeSurface = NULL, rightEyeSurface = NULL, backBuffer = NULL;
	LPDIRECT3DTEXTURE9 tiger = NULL;
	VERTEX* screenQuad;
	VERTEX* eyeLeftQuad;
	VERTEX* eyeRightQuad;

	LPDIRECT3DTEXTURE9 quadTex = NULL;
	IDirect3DPixelShader9* lpPixelShader = NULL;
	LPD3DXBUFFER pCode = NULL;

	bool oculus;
};

#endif
