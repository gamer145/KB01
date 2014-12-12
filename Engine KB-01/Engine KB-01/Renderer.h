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
	Renderer();
	~Renderer();
	virtual void CleanUp()=0;	
	
	virtual HRESULT SetTexture(std::string)=0;
	virtual HRESULT LoadMeshFromFile(std::string filename, EDWORD options, MeshWrapper* destination) = 0;
	virtual HRESULT LoadTextureFromFile(std::string filename, EDWORD options, TextureWrapper* destination) = 0;
	virtual void DrawSubSet(std::string meshname) = 0;
	virtual void SetUpWorld(MatrixWrapper* CameraMatrix, MatrixWrapper* ProjectionMatrix) = 0;
	virtual HRESULT InitD3D(HWND hWnd) = 0;
	virtual void addTexture(std::string textname, TextureWrapper* Text) = 0;
	virtual void addMesh(std::string meshname, MeshWrapper* Mesh) = 0;
	virtual void setDrawWindow(Window* windowtodrawin) = 0;
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
	virtual HRESULT LoadShaderFromFile(std::string shadername, std::string shaderfilepath, std::string vertexshaderfunctionname, std::string pixelshadername) = 0;
	virtual void SetShader(std::string shadername) = 0;
	virtual void StopRenderingWithShaders() = 0;
	virtual void SetZBuffer(bool state) = 0;
	virtual void Clear(EDWORD count, EDWORD flags, ECOLOR color, float z, EDWORD stencil) = 0;
	virtual void BeginS() = 0;
	virtual void EndS() = 0;
	virtual void Present() = 0;
	virtual void PresentWithWindow(HWND hwnd) = 0;
	virtual std::map<std::string, MeshWrapper*> getMeshes() = 0;
	virtual std::map<std::string, TextureWrapper*> getTextures() = 0;
	virtual void RenderToTexture() = 0;
	virtual void setViewportOculus(const OVR::Util::Render::StereoEyeParams& params) = 0;
	virtual void setPixelShaderConstantsOculus(const OVR::Util::Render::StereoEyeParams& params, OVR::Util::Render::StereoConfig SConfig) = 0;
	virtual void setupRenderToTextureOculus() = 0;
	virtual void endRenderToTextureOculus() = 0;
	virtual void renderSceneOculus(const OVR::Util::Render::StereoEyeParams& params, OVR::Util::Render::StereoConfig SConfig) = 0;
	virtual void fillVertexBufferOculus(std::string key, VERTEX vertices[], int size) = 0;
	virtual void createScreenQuadOculus(float width, float height) = 0;
	virtual void renderEyeOculus(const OVR::Util::Render::StereoEyeParams& params, OVR::Util::Render::StereoConfig SConfig) = 0;
	virtual void setViewMatrixOculus( const OVR::Util::Render::StereoEyeParams& params, OVR::Util::Render::StereoConfig SConfig) = 0;
	virtual void setProjectionMatrixOculus(const OVR::Util::Render::StereoEyeParams& params, OVR::Util::Render::StereoConfig SConfig) = 0;
	virtual bool OculusOrNah() = 0;
	virtual void OculusNowYah(bool newOculus) = 0;
};

#endif
