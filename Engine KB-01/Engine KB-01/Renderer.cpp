#include "Renderer.h"

Renderer::Renderer()
{
	g_pD3D = NULL; 
    g_pd3dDevice = NULL;
	worldMatrix = new D3DXMATRIX;
	
};

Renderer::~Renderer()
{
	CleanUp();
};

LPD3DXMESH          g_pMesh = NULL; // Our mesh object in sysmem
D3DMATERIAL9*       g_pMeshMaterials = NULL; // Materials for our mesh
LPDIRECT3DTEXTURE9* g_pMeshTextures = NULL; // Textures for our mesh
DWORD               g_dwNumMaterials = 0L;   // Number of mesh materials

void Renderer::setDrawWindow(Window* windowtodrawin)
{
	myWindow = windowtodrawin;
	InitD3D(myWindow->getHWND());
}

HRESULT Renderer::InitD3D( HWND hWnd )
{
	
    if( NULL == ( g_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
        return E_FAIL;

 
    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory( &d3dpp, sizeof( d3dpp ) );
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.EnableAutoDepthStencil = TRUE; // clear in scene
    d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

    if( FAILED( g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                      &d3dpp, &g_pd3dDevice ) ) )
    {
        return E_FAIL;
    }

	g_pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );
	g_pd3dDevice->SetRenderState( D3DRS_LIGHTING, false);
	g_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE);

    return S_OK;
};

VOID Renderer::CleanUp()
{
    if( g_pd3dDevice != NULL )
        g_pd3dDevice->Release();

    if( g_pD3D != NULL )
        g_pD3D->Release();
};


HRESULT Renderer::SetTexture(std::string textname)
{
	
	LPDIRECT3DTEXTURE9 texture = Textures.find(textname)->second->GetTexture();
	
	g_pd3dDevice->SetTexture(0, texture);
	
	return S_OK;
}

HRESULT Renderer::LoadMeshFromFile(std::string filename, EDWORD options, MeshWrapper* destination)
{

	std::string modLocation = "..\\Models\\" + filename;
	std::wstring stemp = std::wstring(modLocation.begin(), modLocation.end());
	LPCWSTR modelLPCWSTR = stemp.c_str();
	
	LPD3DXMESH mesh = destination->GetMesh();

	HRESULT result = D3DXLoadMeshFromX(modelLPCWSTR, options,
		g_pd3dDevice, NULL,
		NULL, NULL, NULL,
		&mesh);

	destination->SetMesh(mesh);

	addMesh(filename, destination);

	return result;

}

HRESULT Renderer::LoadTextureFromFile(std::string filename, EDWORD options, TextureWrapper* destination)
{
	std::string textLocation = "..\\Models\\" + filename;
	LPSTR textureLPSTR = const_cast<CHAR*>(textLocation.c_str());
	LPDIRECT3DTEXTURE9 TheTexture = destination->GetTexture();

	HRESULT result = D3DXCreateTextureFromFileA(g_pd3dDevice,
		textureLPSTR,
		&TheTexture);

	destination->SetTexture(TheTexture);

	addTexture(filename, destination);

	return result;

}

void Renderer::SetUpWorld(MatrixWrapper* CameraMatrix, MatrixWrapper* ProjectionMatrix)
{
	g_pd3dDevice->SetTransform(D3DTS_WORLD, worldMatrix);
	g_pd3dDevice->SetTransform(D3DTS_VIEW, &CameraMatrix->GetMatrix());
	g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &ProjectionMatrix->GetMatrix());
}

void Renderer::DrawSubSet(std::string meshname)
{
	
	LPD3DXMESH mesh = Meshes.find(meshname)->second->GetMesh();
			
	mesh->DrawSubset(0);		
		
	
}



void Renderer::addTexture(std::string textname, TextureWrapper* Text)
{
	Textures.insert(std::pair<std::string, TextureWrapper*>(textname, Text));
}

void Renderer::addMesh(std::string meshname, MeshWrapper* Mesh)
{
	Meshes.insert(std::pair<std::string, MeshWrapper*>(meshname, Mesh));
}

/*
void Renderer::setStreamSource(IDirect3DVertexBuffer9 *pStreamData, UINT OffsetInBytes)
{
	g_pd3dDevice->SetStreamSource(0, pStreamData, OffsetInBytes, 0);
}
*/

void Renderer::CreateVertexBuffer(int heightmapvertex, EDWORD usage, EDWORD fvf, EPOOL pool, std::string vertexbuffername, HANDLE handle)
{
	VertexBufferExists(vertexbuffername);

	LPDIRECT3DVERTEXBUFFER9 vertexbuffer = VertexBuffers.find(vertexbuffername)->second;

	g_pd3dDevice->CreateVertexBuffer(heightmapvertex, usage, fvf, static_cast<D3DPOOL>(pool), &vertexbuffer, NULL);

	VertexBuffers.find(vertexbuffername)->second = vertexbuffer;
}

HRESULT Renderer::CreateIndexBuffer(int length, EDWORD usage, EFORMAT format, EPOOL pool, std::string indexbuffername, HANDLE* handle)
{
	IndexBufferExists(indexbuffername);

	LPDIRECT3DINDEXBUFFER9 indexbuffer = IndexBuffers.find(indexbuffername)->second;

	HRESULT result = g_pd3dDevice->CreateIndexBuffer(length, usage, static_cast<D3DFORMAT>(format), static_cast<D3DPOOL>(pool), &indexbuffer, NULL);

	IndexBuffers.find(indexbuffername)->second = indexbuffer;

	return result;
}

HRESULT Renderer::LockVertexBuffer(std::string vertexbuffername, int offsettolock, int sizetolock, void** pbdata, EDWORD flags)
{
	LPDIRECT3DVERTEXBUFFER9 vertexbuffer = VertexBuffers.find(vertexbuffername)->second;

	return (vertexbuffer)->Lock(offsettolock, sizetolock, pbdata, flags);
}

HRESULT Renderer::LockIndexBuffer(std::string indexbuffername, int offsettolock, int sizetolock, void** pbdata, EDWORD flags)
{
	LPDIRECT3DINDEXBUFFER9 indexbuffer = IndexBuffers.find(indexbuffername)->second;

	return (indexbuffer)->Lock(offsettolock, sizetolock, pbdata, flags);
}

HRESULT Renderer::UnlockVertexBuffer(std::string vertexbuffername)
{
	LPDIRECT3DVERTEXBUFFER9 vertexbuffer = VertexBuffers.find(vertexbuffername)->second;

	return (vertexbuffer)->Unlock();
}

HRESULT Renderer::UnlockIndexBuffer(std::string indexbuffername)
{
	LPDIRECT3DINDEXBUFFER9 indexbuffer = IndexBuffers.find(indexbuffername)->second;

	return (indexbuffer)->Unlock();
}

bool Renderer::VertexBufferExists(std::string vertexbuffername)
{
	if (VertexBuffers.find(vertexbuffername) != VertexBuffers.end())
	{
		return true;
	}
	else{
		LPDIRECT3DVERTEXBUFFER9  vertexbuffer = NULL;

		VertexBuffers.insert(std::pair<std::string, LPDIRECT3DVERTEXBUFFER9>(vertexbuffername, vertexbuffer));

		return false;
	}
}

bool Renderer::IndexBufferExists(std::string indexbuffername)
{
	if (IndexBuffers.find(indexbuffername) != IndexBuffers.end())
	{
		return true;
	}
	else{
		LPDIRECT3DINDEXBUFFER9  indexbuffer;

		IndexBuffers.insert(std::pair<std::string, LPDIRECT3DINDEXBUFFER9>(indexbuffername, indexbuffer));

		return false;
	}
}

HRESULT Renderer::setTransform(ETRANSFORMSTATETYPE transform, MatrixWrapper* matrix)
{
	return g_pd3dDevice->SetTransform(static_cast<D3DTRANSFORMSTATETYPE>(transform), &matrix->GetMatrix());
}

HRESULT Renderer::SetStreamSource(int streamnumber, std::string vertexbuffername, int offset, int stride)
{
	LPDIRECT3DVERTEXBUFFER9 vertexbuffer = VertexBuffers.find(vertexbuffername)->second;

	return g_pd3dDevice->SetStreamSource(streamnumber, vertexbuffer, offset, stride);
}

HRESULT Renderer::SetFVF(DWORD FVF)
{
	return g_pd3dDevice->SetFVF(FVF);
}

HRESULT Renderer::SetIndices(std::string indexbuffername)
{
	LPDIRECT3DINDEXBUFFER9 indexbuffer = IndexBuffers.find(indexbuffername)->second;

	return g_pd3dDevice->SetIndices(indexbuffer);
}

HRESULT Renderer::DrawIndexedPrimitive(EPRIMITIVETYPE type, int basevertexindex, int minvertexindex, int numvertices, int startindex, int primcount)
{
	return g_pd3dDevice->DrawIndexedPrimitive(static_cast<D3DPRIMITIVETYPE>(type), basevertexindex, minvertexindex, numvertices, startindex, primcount);
}

void Renderer::Clear(DWORD count, DWORD flags, D3DCOLOR color, float z, DWORD stencil)
{
	g_pd3dDevice->Clear(count, NULL, flags, color, z, stencil);
}

void Renderer::BeginS()
{
	g_pd3dDevice->BeginScene();
}

void Renderer::EndS()
{
	g_pd3dDevice->EndScene();
}

void Renderer::Present()
{
	g_pd3dDevice->Present( NULL, NULL, NULL, NULL );
}

std::map<std::string, TextureWrapper*> Renderer::getTextures()
{
	return Textures;
}

std::map<std::string, MeshWrapper*> Renderer::getMeshes()
{
	return Meshes;
}
