#include "DirectXRenderer.h"

DirectXRenderer::DirectXRenderer()
{
	g_pD3D = NULL; 
    g_pd3dDevice = NULL;
	
	screenQuad = new VERTEX[4];
	eyeLeftQuad = new VERTEX[4];
	eyeRightQuad = new VERTEX[4];

};

DirectXRenderer::~DirectXRenderer()
{
	CleanUp();
};

LPD3DXMESH          g_pMesh = NULL; // Our mesh object in sysmem
D3DMATERIAL9*       g_pMeshMaterials = NULL; // Materials for our mesh
//D3DMATERIAL9        Material; // Materials for our mesh
LPDIRECT3DTEXTURE9* g_pMeshTextures = NULL; // Textures for our mesh
DWORD               g_dwNumMaterials = 0L;   // Number of mesh materials

void DirectXRenderer::setDrawWindow(Window* windowtodrawin)
{
	myWindow = windowtodrawin;
	InitD3D(myWindow->getHWND());
}

HRESULT DirectXRenderer::InitD3D( HWND hWnd )
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
	//
	this->backBufferWidth = d3dpp.BackBufferWidth;
	this->backBufferHeight = d3dpp.BackBufferHeight;

	// fixme r   this be ugly mon

	//Initialize the texture where the barrel distortion effect is drawn to
	//See http://www.two-kings.de/tutorials/dxgraphics/dxgraphics16.html for sample code
	g_pd3dDevice->CreateTexture(backBufferWidth,
		backBufferHeight,
		1,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A16B16G16R16,
		D3DPOOL_DEFAULT,
		&fullSceneTexture,
		NULL);
	fullSceneTexture->GetSurfaceLevel(0, &fullSceneSurface);

	g_pd3dDevice->CreateTexture(backBufferWidth,
		backBufferHeight,
		1,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A16B16G16R16,
		D3DPOOL_DEFAULT,
		&leftEyeTexture,
		NULL);
	leftEyeTexture->GetSurfaceLevel(0, &leftEyeSurface);

	g_pd3dDevice->CreateTexture(backBufferWidth,
		backBufferHeight,
		1,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A16B16G16R16,
		D3DPOOL_DEFAULT,
		&rightEyeTexture,
		NULL);
	rightEyeTexture->GetSurfaceLevel(0, &rightEyeSurface);

	g_pd3dDevice->GetRenderTarget(0, &backBuffer);

	
	//set the shader	
	D3DXCompileShaderFromFile(L"../Shaders/PixelShader.hlsl",
		NULL,
		NULL,
		"main",
		"ps_2_0",
		NULL,
		&pCode,
		NULL,
		NULL);

	g_pd3dDevice->CreatePixelShader((DWORD*)pCode->GetBufferPointer(),
		&lpPixelShader);

		

	//create the quad we will draw the scene on
	//pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	createScreenQuadOculus(backBufferWidth / 2, backBufferHeight / 2);

	//

	SetFVF(ECUSTOMVERTEX);

	g_pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );
	g_pd3dDevice->SetRenderState( D3DRS_LIGHTING, false);
	g_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE);
	g_pd3dDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID);

    return S_OK;
};

VOID DirectXRenderer::CleanUp()
{
    if( g_pd3dDevice != NULL )
        g_pd3dDevice->Release();

    if( g_pD3D != NULL )
        g_pD3D->Release();
};


HRESULT DirectXRenderer::SetTexture(std::string textname)
{
	
	LPDIRECT3DTEXTURE9 texture = Textures.find(textname)->second->GetTexture();
	
	g_pd3dDevice->SetTexture(0, texture);
	
	return S_OK;
}

HRESULT DirectXRenderer::LoadMeshFromFile(std::string filename, EDWORD options, MeshWrapper* destination)
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

HRESULT DirectXRenderer::LoadTextureFromFile(std::string filename, EDWORD options, TextureWrapper* destination)
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

void DirectXRenderer::SetUpWorld(MatrixWrapper* CameraMatrix, MatrixWrapper* ProjectionMatrix)
{
	g_pd3dDevice->SetTransform(D3DTS_WORLD, &WorldMatrix);
	g_pd3dDevice->SetTransform(D3DTS_VIEW, &CameraMatrix->GetMatrix());
	g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &ProjectionMatrix->GetMatrix());
}

void DirectXRenderer::DrawSubSet(std::string meshname)
{
	
	LPD3DXMESH mesh = Meshes.find(meshname)->second->GetMesh();
			
	mesh->DrawSubset(0);		
		
	
}



void DirectXRenderer::addTexture(std::string textname, TextureWrapper* Text)
{
	Textures.insert(std::pair<std::string, TextureWrapper*>(textname, Text));
}

void DirectXRenderer::addMesh(std::string meshname, MeshWrapper* Mesh)
{
	Meshes.insert(std::pair<std::string, MeshWrapper*>(meshname, Mesh));
}

/*
void DirectXRenderer::setStreamSource(IDirect3DVertexBuffer9 *pStreamData, UINT OffsetInBytes)
{
	g_pd3dDevice->SetStreamSource(0, pStreamData, OffsetInBytes, 0);
}
*/

void DirectXRenderer::CreateVertexBuffer(int heightmapvertex, EDWORD usage, EDWORD fvf, EPOOL pool, std::string vertexbuffername, HANDLE handle)
{
	VertexBufferExists(vertexbuffername);

	LPDIRECT3DVERTEXBUFFER9 vertexbuffer = VertexBuffers.find(vertexbuffername)->second;

	g_pd3dDevice->CreateVertexBuffer(heightmapvertex, usage, fvf, static_cast<D3DPOOL>(pool), &vertexbuffer, NULL);

	VertexBuffers.find(vertexbuffername)->second = vertexbuffer;
}

HRESULT DirectXRenderer::CreateIndexBuffer(int length, EDWORD usage, EFORMAT format, EPOOL pool, std::string indexbuffername, HANDLE* handle)
{
	IndexBufferExists(indexbuffername);

	LPDIRECT3DINDEXBUFFER9 indexbuffer = IndexBuffers.find(indexbuffername)->second;

	HRESULT result = g_pd3dDevice->CreateIndexBuffer(length, usage, static_cast<D3DFORMAT>(format), static_cast<D3DPOOL>(pool), &indexbuffer, NULL);

	IndexBuffers.find(indexbuffername)->second = indexbuffer;

	return result;
}

HRESULT DirectXRenderer::LockVertexBuffer(std::string vertexbuffername, int offsettolock, int sizetolock, void** pbdata, EDWORD flags)
{
	LPDIRECT3DVERTEXBUFFER9 vertexbuffer = VertexBuffers.find(vertexbuffername)->second;

	return (vertexbuffer)->Lock(offsettolock, sizetolock, pbdata, flags);
}

HRESULT DirectXRenderer::LockIndexBuffer(std::string indexbuffername, int offsettolock, int sizetolock, void** pbdata, EDWORD flags)
{
	LPDIRECT3DINDEXBUFFER9 indexbuffer = IndexBuffers.find(indexbuffername)->second;

	return (indexbuffer)->Lock(offsettolock, sizetolock, pbdata, flags);
}

HRESULT DirectXRenderer::UnlockVertexBuffer(std::string vertexbuffername)
{
	LPDIRECT3DVERTEXBUFFER9 vertexbuffer = VertexBuffers.find(vertexbuffername)->second;

	return (vertexbuffer)->Unlock();
}

HRESULT DirectXRenderer::UnlockIndexBuffer(std::string indexbuffername)
{
	LPDIRECT3DINDEXBUFFER9 indexbuffer = IndexBuffers.find(indexbuffername)->second;

	return (indexbuffer)->Unlock();
}

bool DirectXRenderer::VertexBufferExists(std::string vertexbuffername)
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

bool DirectXRenderer::IndexBufferExists(std::string indexbuffername)
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

HRESULT DirectXRenderer::setTransform(ETRANSFORMSTATETYPE transform, MatrixWrapper* matrix)
{
	return g_pd3dDevice->SetTransform(static_cast<D3DTRANSFORMSTATETYPE>(transform), &matrix->GetMatrix());
}

HRESULT DirectXRenderer::SetStreamSource(int streamnumber, std::string vertexbuffername, int offset, int stride)
{
	LPDIRECT3DVERTEXBUFFER9 vertexbuffer = VertexBuffers.find(vertexbuffername)->second;

	return g_pd3dDevice->SetStreamSource(streamnumber, vertexbuffer, offset, stride);
}

HRESULT DirectXRenderer::SetFVF(DWORD FVF)
{
	return g_pd3dDevice->SetFVF(FVF);
}

HRESULT DirectXRenderer::SetIndices(std::string indexbuffername)
{
	LPDIRECT3DINDEXBUFFER9 indexbuffer = IndexBuffers.find(indexbuffername)->second;

	return g_pd3dDevice->SetIndices(indexbuffer);
}

HRESULT DirectXRenderer::DrawIndexedPrimitive(EPRIMITIVETYPE type, int basevertexindex, int minvertexindex, int numvertices, int startindex, int primcount)
{
	return g_pd3dDevice->DrawIndexedPrimitive(static_cast<D3DPRIMITIVETYPE>(type), basevertexindex, minvertexindex, numvertices, startindex, primcount);
}

HRESULT DirectXRenderer::LoadShaderFromFile(std::string shadername, std::string shaderfilepath, std::string vertexshaderfunctionname, std::string pixelshaderfunctionname)
{
	HRESULT result;

	Shader* newshader = new Shader();

	LPD3DXBUFFER pCode = NULL;
	LPD3DXBUFFER compileerrors = NULL;
	LPDIRECT3DVERTEXDECLARATION9    g_pVertexDeclaration = NULL;

	LPDIRECT3DVERTEXSHADER9         g_pVertexShader = NULL;

	LPDIRECT3DPIXELSHADER9         g_pPixelShader = NULL;

	D3DVERTEXELEMENT9 decl[] =
	{
		{ 0, 0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 0, 0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },
		D3DDECL_END()
	};

	

	g_pd3dDevice->CreateVertexDeclaration(decl, &g_pVertexDeclaration);



	LPD3DXCONSTANTTABLE constanttable = NULL;

	std::wstring stemp = std::wstring(shaderfilepath.begin(), shaderfilepath.end());

	LPCWSTR strpath = stemp.c_str();

	if (!vertexshaderfunctionname.empty())
	{
		DWORD error = 0;

		std::string errorstring;

		if (HRESULT hr = FAILED(D3DXCompileShaderFromFile(strpath, NULL, NULL, vertexshaderfunctionname.c_str(), "vs_2_0", 1, &pCode, &compileerrors, &constanttable)))
		{
			// insert logger here, log that the compiling failed

			std::cout << hr;

			error = GetLastError();

			errorstring = DXGetErrorDescriptionA(error);

		}

		//errorstring = DXGetErrorDescriptionA((HRESULT)compileerrors->GetBufferPointer());

		result = g_pd3dDevice->CreateVertexShader((DWORD*)pCode->GetBufferPointer(),
			&g_pVertexShader);

		newshader->SetVertexShader(g_pVertexShader);

	}

	if (!pixelshaderfunctionname.empty())
	{

		if (HRESULT hr = FAILED(D3DXCompileShaderFromFile(strpath, NULL, NULL, pixelshaderfunctionname.c_str(), "ps_2_0", 0, &pCode, NULL, &constanttable)))
		{
			// insert logger here, log that the compiling failed
			std::cout << hr;

		}

		result = g_pd3dDevice->CreatePixelShader((DWORD*)pCode->GetBufferPointer(),
			&g_pPixelShader);

		newshader->SetPixelShader(g_pPixelShader);

	}

	pCode->Release();

	newshader->SetVertexDeclaration(g_pVertexDeclaration);

	newshader->SetConstantTable(constanttable);

	Shaders.insert(std::pair<std::string, Shader*>(shadername, newshader));

	return result;
}

void DirectXRenderer::SetShader(std::string shadername)
{
	Shader* shader = Shaders[shadername];

	if (shader->GetVertexShader() != NULL && shader->GetVertexDeclaration() != NULL)
	{
		g_pd3dDevice->SetVertexDeclaration(shader->GetVertexDeclaration());
		g_pd3dDevice->SetVertexShader(shader->GetVertexShader());
	}

	if (shader->GetPixelShader() != NULL)
	{
		g_pd3dDevice->SetPixelShader(shader->GetPixelShader());
	}

}

void DirectXRenderer::StopRenderingWithShaders()
{
	g_pd3dDevice->SetVertexShader(NULL);
	g_pd3dDevice->SetPixelShader(NULL);
}

void DirectXRenderer::SetZBuffer(bool state)
{
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, state);
}

void DirectXRenderer::Clear(DWORD count, DWORD flags, D3DCOLOR color, float z, DWORD stencil)
{
	g_pd3dDevice->Clear(count, NULL, flags, color, z, stencil);
}

void DirectXRenderer::BeginS()
{
	g_pd3dDevice->BeginScene();
}

void DirectXRenderer::EndS()
{
	g_pd3dDevice->EndScene();
}

void DirectXRenderer::Present()
{
	g_pd3dDevice->Present( NULL, NULL, NULL, NULL );
}

std::map<std::string, TextureWrapper*> DirectXRenderer::getTextures()
{
	return Textures;
}

std::map<std::string, MeshWrapper*> DirectXRenderer::getMeshes()
{
	return Meshes;
}

// oculus test code from here on

bool DirectXRenderer::OculusOrNah()
{
	return oculus;
}

void DirectXRenderer::OculusNowYah(bool newOculus)
{
	oculus = newOculus;
}

void DirectXRenderer::setViewportOculus(const OVR::Util::Render::StereoEyeParams& params)
{
	D3DVIEWPORT9 dxViewport;
	dxViewport.Width = this->backBufferWidth / 2;
	dxViewport.Height = this->backBufferHeight;
	dxViewport.Y = params.VP.y;
	if (params.Eye == OVR::Util::Render::StereoEye_Right){
		dxViewport.X = this->backBufferWidth / 2;
	}
	else{
		dxViewport.X = 0.0f;
	}

	dxViewport.MinZ = 0.0f;
	dxViewport.MaxZ = 1.0f;
	g_pd3dDevice->SetViewport(&dxViewport);

}

void DirectXRenderer::setupRenderToTextureOculus()
{
	g_pd3dDevice->SetRenderTarget(0, fullSceneSurface);
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	g_pd3dDevice->BeginScene();

};

void DirectXRenderer::RenderToTexture()
{
	
	fillVertexBufferOculus("screenVertex", screenQuad, sizeof(VERTEX) * 4);
	//SetZBuffer(false);


	SetStreamSource(0, "screenVertex", 0, sizeof(VERTEX));

	g_pd3dDevice->SetTexture(0, fullSceneTexture);
	g_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

void DirectXRenderer::endRenderToTextureOculus()
{
	g_pd3dDevice->EndScene();
};

void DirectXRenderer::PresentWithWindow(HWND hwnd)
{
	g_pd3dDevice->Present(NULL, NULL, hwnd, NULL);
}

void DirectXRenderer::renderSceneOculus(const OVR::Util::Render::StereoEyeParams& params, OVR::Util::Render::StereoConfig SConfig)
{
	g_pd3dDevice->SetRenderTarget(0, backBuffer);
	setViewportOculus(params);
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	g_pd3dDevice->BeginScene();
	//apply shader
	//render to aligned quad
	fillVertexBufferOculus("screenVertex", screenQuad, sizeof(VERTEX) * 4);
	SetZBuffer(false);
	SetStreamSource(0, "screenVertex", 0, sizeof(VERTEX));
	if (params.Eye == OVR::Util::Render::StereoEye_Right){
		g_pd3dDevice->SetTexture(0, rightEyeTexture);
	}
	else{
		g_pd3dDevice->SetTexture(0, leftEyeTexture);
	}

	//reset matrixes
	g_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	SetZBuffer(true);

	g_pd3dDevice->EndScene();
}

void DirectXRenderer::fillVertexBufferOculus(std::string key, VERTEX vertices[], int size)
{
	//Since this method is called repeatedly, we need to check if the requested buffer already exists or not.
	if (VertexBuffers.find(key) == VertexBuffers.end())
	{
		LPDIRECT3DVERTEXBUFFER9 vBuffer;
		g_pd3dDevice->CreateVertexBuffer(size, 0, ECUSTOMVERTEX, D3DPOOL_MANAGED, &vBuffer, NULL);

		void* pVertices;
		vBuffer->Lock(0, size, (void**)&pVertices, 0);
		memcpy(pVertices, vertices, size);
		vBuffer->Unlock();

		VertexBuffers.insert(std::pair<std::string, LPDIRECT3DVERTEXBUFFER9>(key, vBuffer));
	}
};

void DirectXRenderer::createScreenQuadOculus(float width, float height)
{
	VERTEX vertices[4] = {
			{ -width - 0.5f, height + 0.5f, 0.0f, 0.0f, 0.0f }, //top left
			{ width - 0.5f, height + 0.5f, 0.0f, 1.0f, 0.0f }, // top right
			{ -width - 0.5f, -height + 0.5f, 0.0f, 0.0f, 1.0f }, //bottom left
			{ width - 0.5f, -height + 0.5f, 0.0f, 1.0f, 1.0f } // bottom right
	};

	for (int i = 0; i < 4; ++i)
	{
		screenQuad[i] = vertices[i];
	}

	VERTEX verticesLeftEye[4] = {
			{ -width - 0.5f, height + 0.5f, 0.0f, 0.0f, 0.0f }, //top left
			{ width - 0.5f, height + 0.5f, 0.0f, 0.5f, 0.0f }, // top right
			{ -width - 0.5f, -height + 0.5f, 0.0f, 0.0f, 1.0f }, //bottom left
			{ width - 0.5f, -height + 0.5f, 0.0f, 0.5f, 1.0f } // bottom right
	};

	for (int i = 0; i < 4; ++i)
	{
		eyeLeftQuad[i] = verticesLeftEye[i];
	}

	VERTEX verticesRightEye[4] = {
			{ -width - 0.5f, height + 0.5f, 0.0f, 0.5f, 0.0f }, //top left
			{ width - 0.5f, height + 0.5f, 0.0f, 1.0f, 0.0f }, // top right
			{ -width - 0.5f, -height + 0.5f, 0.0f, 0.5f, 1.0f }, //bottom left
			{ width - 0.5f, -height + 0.5f, 0.0f, 1.0f, 1.0f } // bottom right
	};

	for (int i = 0; i < 4; ++i)
	{
		eyeRightQuad[i] = verticesRightEye[i];
	}
}

void DirectXRenderer::renderEyeOculus(const OVR::Util::Render::StereoEyeParams& params, OVR::Util::Render::StereoConfig SConfig)
{
	std::string quadname;
	if (params.Eye == OVR::Util::Render::StereoEye_Right){
		g_pd3dDevice->SetRenderTarget(0, rightEyeSurface);
		quadname = "rightQuad";
	}
	else{
		g_pd3dDevice->SetRenderTarget(0, leftEyeSurface);
		quadname = "leftQuad";
	}

	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	g_pd3dDevice->BeginScene();

	//g_pd3dDevice->SetPixelShader(lpPixelShader);
	setPixelShaderConstantsOculus(params, SConfig);

	if (params.Eye == OVR::Util::Render::StereoEye_Right){
		fillVertexBufferOculus(quadname, eyeRightQuad, sizeof(VERTEX) * 4);
	}
	else{
		fillVertexBufferOculus(quadname, eyeLeftQuad, sizeof(VERTEX) * 4);
	}
	//dooásd
	SetZBuffer(false);
	SetStreamSource(0, quadname, 0,  sizeof(VERTEX));
	g_pd3dDevice->SetTexture(0, fullSceneTexture);
	
	g_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	//g_pd3dDevice->SetPixelShader(NULL);

	g_pd3dDevice->EndScene();

};

void DirectXRenderer::setViewMatrixOculus(const OVR::Util::Render::StereoEyeParams& params, OVR::Util::Render::StereoConfig SConfig)
{
	float viewCenter = SConfig.GetHMDInfo().HScreenSize * 0.25f;
	float halfIPD = SConfig.GetHMDInfo().InterpupillaryDistance * 0.5f;

	D3DXMATRIX viewMatrix;
	if (params.Eye == OVR::Util::Render::StereoEye_Left){
		D3DXMatrixTranslation(&viewMatrix, halfIPD, 0, 0);
		viewMatrix = scalarMultiply(&viewMatrix, viewCenter);
	}
	else{
		D3DXMatrixTranslation(&viewMatrix, -halfIPD, 0, 0);
		viewMatrix = scalarMultiply(&viewMatrix, viewCenter);
	}

	g_pd3dDevice->SetTransform(D3DTS_VIEW, &viewMatrix);
};

D3DXMATRIX  DirectXRenderer::scalarMultiply(D3DXMATRIX* matrix, float multiplyFactor)
{
	D3DXMATRIX multipliedMatrix;
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			multipliedMatrix.m[i][j] = matrix->m[i][j] * multiplyFactor;
		};
	}
	return multipliedMatrix;
};

void DirectXRenderer::setProjectionMatrixOculus(const OVR::Util::Render::StereoEyeParams& params, OVR::Util::Render::StereoConfig SConfig)
{
	float projectionCenterOffset = SConfig.GetProjectionCenterOffset();
	//float projectionCenterOffset = 0.05;
	D3DXMATRIXA16 projectionCenterMatrix;
	D3DXMatrixPerspectiveFovLH(&projectionCenterMatrix,
		SConfig.GetYFOVRadians(),    // the horizontal field of view
		SConfig.GetAspect(),    // aspect ratio
		0.3f,    // the near view-plane
		1000.0f);    // the far view-plane

	D3DXMATRIXA16 projectionMatrix;
	if (params.Eye == OVR::Util::Render::StereoEye_Left){
		D3DXMatrixTranslation(&projectionMatrix, projectionCenterOffset, 0, 0);
		projectionMatrix = projectionCenterMatrix * projectionMatrix;
	}
	else{
		D3DXMatrixTranslation(&projectionMatrix, -projectionCenterOffset, 0, 0);
		projectionMatrix = projectionCenterMatrix * projectionMatrix;
	}

	g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &projectionMatrix);    // set the projection transform	
};

void DirectXRenderer::setPixelShaderConstantsOculus(const OVR::Util::Render::StereoEyeParams& params, OVR::Util::Render::StereoConfig SConfig)
{
	float w = float(params.VP.w) / float(SConfig.GetHMDInfo().HResolution);
	float h = float(params.VP.h) / float(SConfig.GetHMDInfo().VResolution);
	float x = float(params.VP.x) / float(SConfig.GetHMDInfo().HResolution);
	float y = float(params.VP.y) / float(SConfig.GetHMDInfo().VResolution);
	float scaleFactor = 1.0f / SConfig.GetDistortionConfig().Scale;

	if (params.Eye == OVR::Util::Render::StereoEye_Right){

		float lensCenter[2] = { x + (w - SConfig.GetDistortionConfig().XCenterOffset * 0.5f)*0.5f, y + h*0.5f };
		g_pd3dDevice->SetPixelShaderConstantF(0, lensCenter, 1);
		float screenCenter[2] = { x + w*0.5f, y + h*0.5f };
		g_pd3dDevice->SetPixelShaderConstantF(1, screenCenter, 1);

	}
	else{

		float lensCenter[2] = { x + (w + SConfig.GetDistortionConfig().XCenterOffset * 0.5f)*0.5f, y + h*0.5f };
		g_pd3dDevice->SetPixelShaderConstantF(0, lensCenter, 1);
		float screenCenter[2] = { x + w*0.5f, y + h*0.5f };
		g_pd3dDevice->SetPixelShaderConstantF(1, screenCenter, 1);
	}

	float scale[2] = { (w / 2) * scaleFactor, (h / 2) * scaleFactor * SConfig.GetAspect() };
	g_pd3dDevice->SetPixelShaderConstantF(2, scale, 1);
	float scaleIn[2] = { (2 / w), (2 / h) / SConfig.GetAspect() };
	g_pd3dDevice->SetPixelShaderConstantF(3, scaleIn, 1);
	float HmdWarpParam[4] = { SConfig.GetDistortionK(0), SConfig.GetDistortionK(1), SConfig.GetDistortionK(2), SConfig.GetDistortionK(3) };
	g_pd3dDevice->SetPixelShaderConstantF(4, HmdWarpParam, 1);
};
