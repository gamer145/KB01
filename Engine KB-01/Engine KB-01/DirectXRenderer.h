#ifndef DirectXRenderer_H
#define DirectXRenderer_H

#include <d3d9.h>
#include <d3dx9.h>
//#include <dxerr.h>
#include "Renderer.h"
#include <mmsystem.h>
#include <strsafe.h>
#include <vector>
#include "Shader.h"


class Entity;
class DirectXRenderer : public Renderer
{
public:
	//constructor
	DirectXRenderer();

	//destructor
	~DirectXRenderer();

	//Cleans up the renderer's assets and destroys them
	void CleanUp();
	


	//Sets the texture to draw with, texture has to be loaded using the Resourceloader before calling this function.
	HRESULT SetTexture(std::string); 

	//Loads a mesh from a local file into the resourceloader's list of meshes.
	HRESULT LoadMeshFromFile(std::string filename, EDWORD options, MeshWrapper* destination); 

	//Loads a texture from a local file into the resourceloader's list of textures.
	HRESULT LoadTextureFromFile(std::string filename, EDWORD options, TextureWrapper* destination); 

	//Draw the specified mesh's subsets.
	void DrawSubSet(std::string meshname); 

	//Initializes the world, camera and projection
	void SetUpWorld(MatrixWrapper* CameraMatrix, MatrixWrapper* ProjectionMatrix); 

	//Initializes the specified Graphics Device
	HRESULT InitGraphics( Window* window ); 

	//Adds a texture to the Renderer-specific list of textures, which is managed by the resourcemanager
	void addTexture(std::string textname, TextureWrapper* Text); 

	//Adds a mesh to the Renderer-specific list of meshes, which is managed by the resourcemanager
	void addMesh(std::string meshname, MeshWrapper* Mesh); 

	//Set the current window to draw our scene to
	void setDrawWindow(Window* windowtodrawin); 

	//Creates a vertexbuffer
	HRESULT CreateVertexBuffer(int heightmapvertex, EDWORD usage, EDWORD fvf, EPOOL pool, std::string vertexbuffername, HANDLE handle); 

	//Creates an indexbuffer
	HRESULT CreateIndexBuffer(int length, EDWORD usage, EFORMAT format, EPOOL pool, std::string indexbuffername, HANDLE* handle); 

	//Locks an existing unlocked vertexbuffer
	HRESULT LockVertexBuffer(std::string vertexbuffername, int offsettolock, int sizetolock, void** pbdata, EDWORD flags); 

	//Unlocks an existing lockedvertex buffer
	HRESULT UnlockVertexBuffer(std::string vertexbuffername); 

	//Locks an existing unlocked indexbuffer
	HRESULT LockIndexBuffer(std::string indexbuffername, int offsettolock, int sizetolock, void** pbdata, EDWORD flags); 

	//Unlocks an existing locked indexbuffer
	HRESULT UnlockIndexBuffer(std::string indexbuffername); 

	//Checks if a indexbuffer exists and returns true if it already exists, if it does not exist it initalizes a new empty indexbuffer with the given name and returns false.
	bool VertexBufferExists(std::string vertexbuffername); 

	//Checks if a indexbuffer exists and returns true if it already exists, if it does not exist it initalizes a new empty indexbuffer with the given name and returns false.
	bool IndexBufferExists(std::string indexbuffername);

	//Sets the transform of given matrix
	HRESULT setTransform(ETRANSFORMSTATETYPE transform, MatrixWrapper* matrix); 

	//Sets the stream source for a vertexbuffer that has been loaded
	HRESULT SetStreamSource(int streamnumber, std::string vertexbuffername, int offset, int stride); 

	//Set the FVF
	HRESULT SetFVF(EDWORD FVF); 

	//Set the indices to draw with, loaded from a indexbuffer that has been created and filled.
	HRESULT SetIndices(std::string indexbuffername); 

	//Draws a primitive
	HRESULT DrawIndexedPrimitive(EPRIMITIVETYPE type, int basevertexindex, int minvertexindex, int numvertices, int startindex, int primcount); 



	//WARNING: INCOMPLETE/BROKEN FUNCTION. DO NOT USE. Loads a shader from a local file into the resource manager's list.
	HRESULT LoadShaderFromFile(std::string shadername, std::string shaderfilepath, std::string vertexshaderfunctionname, std::string pixelshadername); 

	//WARNING: INCOMPLETE/BROKEN FUNCTION. DO NOT USE. Set a shader to draw with
	void SetShader(std::string shadername); 

	//WARNING: INCOMPLETE/BROKEN FUNCTION. DO NOT USE. Stop drawing with any shaders
	void StopRenderingWithShaders(); 



	//Turn the zbuffer on or off
	void SetZBuffer(bool state); 

	//Clear the scene
	void Clear(EDWORD count, EDWORD flags, ECOLOR color, float z, EDWORD stencil); 

	//Begins the current Scene
	void BeginS(); 

	//Ends the current Scene
	void EndS(); 

	//Presents the current Scene to the current window
	void Present(); 

	//Initializes the light
	void init_light(); 



	//Returns a list of all loaded meshes, managed by the resource manager
	std::map<std::string, MeshWrapper*> getMeshes(); 

	//Returns a list of all loaded textures, managed by the resource manager
	std::map<std::string, TextureWrapper*> getTextures(); 


	//********************************************************************************************************************************//
	//EVERYTHING FROM HERE IS EXPERIMENTAL OCULUS CODE AND SHOULD NOT BE USED AS IT IS NOT FINISHED AND WILL CRASH THE ENGINE IF USED.//
	//********************************************************************************************************************************//

	//WARNING: INCOMPLETE/BROKEN FUNCTION. DO NOT USE.
	void RenderToTexture(); 

	//WARNING: INCOMPLETE/BROKEN FUNCTION. DO NOT USE.
	void PresentWithWindow(HWND hwnd); 

	//WARNING: INCOMPLETE/BROKEN FUNCTION. DO NOT USE.
	void setViewportOculus(const OVR::Util::Render::StereoEyeParams& params); 

	//WARNING: INCOMPLETE/BROKEN FUNCTION. DO NOT USE.
	void setPixelShaderConstantsOculus(const OVR::Util::Render::StereoEyeParams& params, OVR::Util::Render::StereoConfig SConfig); 

	//WARNING: INCOMPLETE/BROKEN FUNCTION. DO NOT USE.
	void setupRenderToTextureOculus(); 

	//WARNING: INCOMPLETE/BROKEN FUNCTION. DO NOT USE.
	void endRenderToTextureOculus(); 

	//WARNING: INCOMPLETE/BROKEN FUNCTION. DO NOT USE.
	void renderSceneOculus(const OVR::Util::Render::StereoEyeParams& params, OVR::Util::Render::StereoConfig SConfig); 

	//WARNING: INCOMPLETE/BROKEN FUNCTION. DO NOT USE.
	void fillVertexBufferOculus(std::string key, VERTEX vertices[], int size); 

	//WARNING: INCOMPLETE/BROKEN FUNCTION. DO NOT USE.
	void createScreenQuadOculus(float width, float height); 

	//WARNING: INCOMPLETE/BROKEN FUNCTION. DO NOT USE.
	void renderEyeOculus(const OVR::Util::Render::StereoEyeParams& params, OVR::Util::Render::StereoConfig SConfig); 

	//WARNING: INCOMPLETE/BROKEN FUNCTION. DO NOT USE.
	void setViewMatrixOculus(const OVR::Util::Render::StereoEyeParams& params, OVR::Util::Render::StereoConfig SConfig); 

	//WARNING: INCOMPLETE/BROKEN FUNCTION. DO NOT USE.
	void setProjectionMatrixOculus(const OVR::Util::Render::StereoEyeParams& params, OVR::Util::Render::StereoConfig SConfig); 

	//WARNING: INCOMPLETE/BROKEN FUNCTION. DO NOT USE.
	bool OculusOrNah(); 

	//WARNING: INCOMPLETE/BROKEN FUNCTION. DO NOT USE.
	void OculusNowYah(bool newOculus); 

private:

	//Your Directx9 3D, this thing is basically god
	LPDIRECT3D9         g_pD3D; 

	//Your Directx93D Device, This is the tool that the Directx-specific renderer uses to draw almost everything in the scene
    LPDIRECT3DDEVICE9   g_pd3dDevice; 

	//Your current window
	Window* myWindow; 

	//Determines whether we're rendering right now
	bool keepRendering; 

	//The world matrix
	D3DXMATRIX WorldMatrix; 
	


	//A list of meshes, managed by the resource manager
	std::map<std::string, MeshWrapper*> Meshes; 

	//A list of textures, managed by the resource manager
	std::map<std::string, TextureWrapper*> Textures; 

	//WARNING: INCOMPLETE/BROKEN VARIABLE. DO NOT USE. A list of directx-specific meshes, managed by the resource manager
	std::map<std::string, Shader*> Shaders; 



	//A list of directx-specific meshes, managed by the resource manager
	std::map<std::string, LPDIRECT3DVERTEXBUFFER9> VertexBuffers; 

	//A list of directx-specific meshes, managed by the resource manager
	std::map<std::string, LPDIRECT3DINDEXBUFFER9> IndexBuffers; 
	


	//********************************************************************************************************************************//
	//EVERYTHING FROM HERE IS EXPERIMENTAL OCULUS CODE AND SHOULD NOT BE USED AS IT IS NOT FINISHED AND WILL CRASH THE ENGINE IF USED.//
	//********************************************************************************************************************************//



	//WARNING: INCOMPLETE/BROKEN FUNCTION. DO NOT USE.
	D3DXMATRIX scalarMultiply(D3DXMATRIX* matrix, float multiplyFactor); 
	

	//WARNING: INCOMPLETE/BROKEN FUNCTION. DO NOT USE.
	float backBufferWidth; 

	//WARNING: INCOMPLETE/BROKEN FUNCTION. DO NOT USE.
	float backBufferHeight; 



	//WARNING: INCOMPLETE/BROKEN FUNCTION. DO NOT USE.
	LPDIRECT3DTEXTURE9 fullSceneTexture = NULL, leftEyeTexture = NULL, rightEyeTexture = NULL; 

	//WARNING: INCOMPLETE/BROKEN FUNCTION. DO NOT USE.
	LPDIRECT3DSURFACE9 fullSceneSurface = NULL, leftEyeSurface = NULL, rightEyeSurface = NULL, backBuffer = NULL; 

	//WARNING: INCOMPLETE/BROKEN FUNCTION. DO NOT USE.
	LPDIRECT3DTEXTURE9 tiger = NULL; 

	//WARNING: INCOMPLETE/BROKEN FUNCTION. DO NOT USE.
	VERTEX* screenQuad; 

	//WARNING: INCOMPLETE/BROKEN FUNCTION. DO NOT USE.
	VERTEX* eyeLeftQuad; 

	//WARNING: INCOMPLETE/BROKEN FUNCTION. DO NOT USE.
	VERTEX* eyeRightQuad; 



	//WARNING: INCOMPLETE/BROKEN FUNCTION. DO NOT USE.
	LPDIRECT3DTEXTURE9 quadTex = NULL; 

	//WARNING: INCOMPLETE/BROKEN FUNCTION. DO NOT USE.
	IDirect3DPixelShader9* lpPixelShader = NULL; 

	//WARNING: INCOMPLETE/BROKEN FUNCTION. DO NOT USE.
	LPD3DXBUFFER pCode = NULL; 



	//WARNING: INCOMPLETE/BROKEN FUNCTION. DO NOT USE.
	bool oculus; 
};

#endif
