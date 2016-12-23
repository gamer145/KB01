#ifndef Renderer_H
#define Renderer_H


#include <string>
#include <map>
#include "Model.h"
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
#include "OVR.h"

class Entity;
class Renderer
{
public:
	//constructor
	Renderer();

	//destructor
	~Renderer();

	//Cleans up the renderer's assets and destroys them
	virtual void CleanUp()=0;	

	

	//Sets the texture to draw with, texture has to be loaded using the Resourceloader before calling this function.
	virtual HRESULT SetTexture(std::string)=0; 

	//Loads a mesh from a local file into the resourceloader's list of meshes.
	virtual HRESULT LoadMeshFromFile(std::string filename, EDWORD options, MeshWrapper* destination) = 0; 

	//Loads a texture from a local file into the resourceloader's list of textures.
	virtual HRESULT LoadTextureFromFile(std::string filename, EDWORD options, TextureWrapper* destination) = 0; 

	//Draw the specified mesh's subsets.
	virtual void DrawSubSet(std::string meshname) = 0; 

	//Initializes the world, camera and projection
	virtual void SetUpWorld(MatrixWrapper* CameraMatrix, MatrixWrapper* ProjectionMatrix) = 0; 

	//Initializes the specified Graphics Device
	virtual HRESULT InitGraphics(Window* window) = 0; 

	//Adds a texture to the Renderer-specific list of textures, which is managed by the resourcemanager
	virtual void addTexture(std::string textname, TextureWrapper* Text) = 0; 

	//Adds a mesh to the Renderer-specific list of meshes, which is managed by the resourcemanager
	virtual void addMesh(std::string meshname, MeshWrapper* Mesh) = 0; 

	//Set the current window to draw our scene to
	virtual void setDrawWindow(Window* windowtodrawin) = 0; 

	//Creates a vertexbuffer
	virtual HRESULT CreateVertexBuffer(int heightmapvertex, EDWORD usage, EDWORD fvf, EPOOL pool, std::string vertexbuffername, HANDLE handle) = 0; 

	//Creates an indexbuffer
	virtual HRESULT CreateIndexBuffer(int length, EDWORD usage, EFORMAT format, EPOOL pool, std::string indexbuffername, HANDLE* handle) = 0; 

	//Locks an existing unlocked vertexbuffer
	virtual HRESULT LockVertexBuffer(std::string vertexbuffername, int offsettolock, int sizetolock, void** pbdata, EDWORD flags) = 0; 

	//Unlocks an existing lockedvertex buffer
	virtual HRESULT UnlockVertexBuffer(std::string vertexbuffername) = 0; 

	//Locks an existing unlocked indexbuffer
	virtual HRESULT LockIndexBuffer(std::string indexbuffername, int offsettolock, int sizetolock, void** pbdata, EDWORD flags) = 0; 

	//Unlocks an existing locked indexbuffer
	virtual HRESULT UnlockIndexBuffer(std::string indexbuffername) = 0;

	//Checks if a vertexbuffer exists and returns true if it already exists, if it does not exist it initalizes a new empty vertexbuffer with the given name and returns false.
	virtual bool VertexBufferExists(std::string vertexbuffername) = 0; 

	//Checks if a indexbuffer exists and returns true if it already exists, if it does not exist it initalizes a new empty indexbuffer with the given name and returns false.
	virtual bool IndexBufferExists(std::string indexbuffername) = 0; 

	//Sets the transform of given matrix
	virtual HRESULT setTransform(ETRANSFORMSTATETYPE transform, MatrixWrapper* matrix) = 0; 

	//Sets the stream source for a vertexbuffer that has been loaded
	virtual HRESULT SetStreamSource(int streamnumber, std::string vertexbuffername, int offset, int stride) = 0; 

	//Set the FVF
	virtual HRESULT SetFVF(EDWORD FVF) = 0; 

	//Set the indices to draw with, loaded from a indexbuffer that has been created and filled.
	virtual HRESULT SetIndices(std::string indexbuffername) = 0; 

	//Draws a primitive
	virtual HRESULT DrawIndexedPrimitive(EPRIMITIVETYPE type, int basevertexindex, int minvertexindex, int numvertices, int startindex, int primcount) = 0; 



	//WARNING: INCOMPLETE/BROKEN FUNCTION. DO NOT USE. Loads a shader from a local file into the resource manager's list.
	virtual HRESULT LoadShaderFromFile(std::string shadername, std::string shaderfilepath, std::string vertexshaderfunctionname, std::string pixelshadername) = 0; 

	//WARNING: INCOMPLETE/BROKEN FUNCTION. DO NOT USE. Set a shader to draw with
	virtual void SetShader(std::string shadername) = 0;  

	//WARNING: INCOMPLETE/BROKEN FUNCTION. DO NOT USE. Stop drawing with any shaders
	virtual void StopRenderingWithShaders() = 0; 



	//Turn the zbuffer on or off
	virtual void SetZBuffer(bool state) = 0; 

	//Clear the scene
	virtual void Clear(EDWORD count, EDWORD flags, ECOLOR color, float z, EDWORD stencil) = 0; 

	//Begins the current Scene
	virtual void BeginS() = 0; 

	//Ends the current Scene
	virtual void EndS() = 0; 

	//Presents the current Scene to the current window
	virtual void Present() = 0; 

	//Presents the current scene to the given window
	virtual void PresentWithWindow(HWND hwnd) = 0; 

	//Initializes the light
	virtual void init_light() = 0; 



	//Returns a list of all loaded meshes, managed by the resource manager
	virtual std::map<std::string, MeshWrapper*> getMeshes() = 0; 

	//Returns a list of all loaded textures, managed by the resource manager
	virtual std::map<std::string, TextureWrapper*> getTextures() = 0; 


	//********************************************************************************************************************************//
	//EVERYTHING FROM HERE IS EXPERIMENTAL OCULUS CODE AND SHOULD NOT BE USED AS IT IS NOT FINISHED AND WILL CRASH THE ENGINE IF USED.//
	//********************************************************************************************************************************//


	//WARNING: INCOMPLETE/BROKEN FUNCTION. DO NOT USE.
	virtual void RenderToTexture() = 0; 

	//WARNING: INCOMPLETE/BROKEN FUNCTION. DO NOT USE.
	virtual void setViewportOculus(const OVR::Util::Render::StereoEyeParams& params) = 0; 

	//WARNING: INCOMPLETE/BROKEN FUNCTION. DO NOT USE.
	virtual void setPixelShaderConstantsOculus(const OVR::Util::Render::StereoEyeParams& params, OVR::Util::Render::StereoConfig SConfig) = 0; 

	//WARNING: INCOMPLETE/BROKEN FUNCTION. DO NOT USE.
	virtual void setupRenderToTextureOculus() = 0; 

	//WARNING: INCOMPLETE/BROKEN FUNCTION. DO NOT USE.
	virtual void endRenderToTextureOculus() = 0; 

	//WARNING: INCOMPLETE/BROKEN FUNCTION. DO NOT USE.
	virtual void renderSceneOculus(const OVR::Util::Render::StereoEyeParams& params, OVR::Util::Render::StereoConfig SConfig) = 0; 

	//WARNING: INCOMPLETE/BROKEN FUNCTION. DO NOT USE.
	virtual void fillVertexBufferOculus(std::string key, VERTEX vertices[], int size) = 0; 

	//WARNING: INCOMPLETE/BROKEN FUNCTION. DO NOT USE.
	virtual void createScreenQuadOculus(float width, float height) = 0; 

	//WARNING: INCOMPLETE/BROKEN FUNCTION. DO NOT USE.
	virtual void renderEyeOculus(const OVR::Util::Render::StereoEyeParams& params, OVR::Util::Render::StereoConfig SConfig) = 0; 

	//WARNING: INCOMPLETE/BROKEN FUNCTION. DO NOT USE.
	virtual void setViewMatrixOculus( const OVR::Util::Render::StereoEyeParams& params, OVR::Util::Render::StereoConfig SConfig) = 0; 

	//WARNING: INCOMPLETE/BROKEN FUNCTION. DO NOT USE.
	virtual void setProjectionMatrixOculus(const OVR::Util::Render::StereoEyeParams& params, OVR::Util::Render::StereoConfig SConfig) = 0; 

	//WARNING: INCOMPLETE/BROKEN FUNCTION. DO NOT USE.
	virtual bool OculusOrNah() = 0; 

	//WARNING: INCOMPLETE/BROKEN FUNCTION. DO NOT USE.
	virtual void OculusNowYah(bool newOculus) = 0; 
};

#endif
