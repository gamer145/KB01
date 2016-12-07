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


/**
* Function:	Renderer::setDrawWindow(Window* windowtodrawin)
* Description:	Set the current window to draw our scene to
*/
void DirectXRenderer::setDrawWindow(Window* windowtodrawin)
{
	myWindow = windowtodrawin;
	InitGraphics(myWindow->getHWND());
}


/**
* Function:	Renderer::InitGraphics( HWND hWnd )
* Description:	Initializes the specified Graphics Device
*/
HRESULT DirectXRenderer::InitGraphics( HWND hWnd )
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


	/* *OCU*
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
	*/

		
	//create the quad we will draw the scene on
	//pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	//*OCU* createScreenQuadOculus(backBufferWidth / 2, backBufferHeight / 2);

	SetFVF(ECUSTOMFVF);


	g_pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );
	g_pd3dDevice->SetRenderState( D3DRS_LIGHTING, TRUE );
	g_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW);
	g_pd3dDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID);

	//ugly testing code
	std::string filename = "banana.jpg";
	std::string textLocation = "..\\Models\\" + filename;
	LPSTR textureLPSTR = const_cast<CHAR*>(textLocation.c_str());

	HRESULT result = D3DXCreateTextureFromFileA(g_pd3dDevice,
		textureLPSTR,
		&tiger);

	g_pd3dDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(133, 133, 133));
	init_light();

    return S_OK;
};

/**
* Function:	Renderer::CleanUp()
* Description:	Clean up this mess of a renderer by clearing out the graphics devices.
*/
VOID DirectXRenderer::CleanUp()
{
    if( g_pd3dDevice != NULL )
        g_pd3dDevice->Release();

    if( g_pD3D != NULL )
        g_pD3D->Release();

	if (myWindow != NULL) {
		delete myWindow;
	}
	if (WorldMatrix != NULL) {
		delete WorldMatrix;
	}
	

	for each(std::pair<std::string, MeshWrapper*> M in Meshes)
	{
		delete M.second;
	}

	for each(std::pair<std::string, TextureWrapper*> T in Textures)
	{
		delete T.second;
	}

	for each(std::pair<std::string, LPDIRECT3DVERTEXBUFFER9> V in VertexBuffers)
	{
		delete V.second;
	}

	for each(std::pair<std::string, LPDIRECT3DINDEXBUFFER9> I in IndexBuffers)
	{
		delete I.second;
	}
};

/**
* Function:	Renderer::init_light()
* Description:	Initializes our light functionality
*/
void DirectXRenderer::init_light()
{
	D3DLIGHT9 light;    // create the light struct
	D3DMATERIAL9 material;    // create the material struct

	ZeroMemory(&light, sizeof(light));    // clear out the light struct for use
	light.Type = D3DLIGHT_DIRECTIONAL;    // make the light type 'directional light'
	light.Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);    // set the light's color
	light.Direction = D3DXVECTOR3(1.0f, -0.3f, -1.0f);

	g_pd3dDevice->SetLight(0, &light);    // send the light struct properties to light #0
	g_pd3dDevice->LightEnable(0, TRUE);    // turn on light #0

	ZeroMemory(&material, sizeof(material));    // clear out the struct for use
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);    // set diffuse color to white
	material.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);    // set ambient color to white

	g_pd3dDevice->SetMaterial(&material);    // set the globably-used material to &material
}

/**
* Function:	Renderer::SetTexture(std::string textname)
* Description:	Sets the texture to draw with, texture has to be loaded using the Resourceloader before calling this function.
*/
HRESULT DirectXRenderer::SetTexture(std::string textname)
{
	
	LPDIRECT3DTEXTURE9 texture = Textures.find(textname)->second->GetTexture();
	
	g_pd3dDevice->SetTexture(0, texture);
	
	return S_OK;
}

/**
* Function: Renderer::LoadMeshFromFile(std::string filename, EDWORD options, MeshWrapper* destination)
* Description: Loads a mesh from a local file into the resourceloader's list of meshes.
*/
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

/**
* Function: Renderer::LoadTextureFromFile(std::string filename, EDWORD options, TextureWrapper* destination)
* Description: Loads a texture from a local file into the resourceloader's list of textures.
*/
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

/**
* Function: Renderer::SetUpWorld(MatrixWrapper* CameraMatrix, MatrixWrapper* ProjectionMatrix)
* Description: Initializes the world, camera and projection
*/
void DirectXRenderer::SetUpWorld(MatrixWrapper* CameraMatrix, MatrixWrapper* ProjectionMatrix)
{
	g_pd3dDevice->SetTransform(D3DTS_WORLD, &WorldMatrix);
	g_pd3dDevice->SetTransform(D3DTS_VIEW, &CameraMatrix->GetMatrix());
	g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &ProjectionMatrix->GetMatrix());
}

/**
* Function: Renderer::DrawSubSet(std::string meshname)
* Description: Draw the specified mesh's subsets.
*/
void DirectXRenderer::DrawSubSet(std::string meshname)
{
	
	LPD3DXMESH mesh = Meshes.find(meshname)->second->GetMesh();
			
	mesh->DrawSubset(NULL);		
		
	
}


/**
* Function: Renderer::addTexture(std::string textname, TextureWrapper* Text)
* Description: Adds a texture to the Renderer-specific list of textures, which is managed by the resourcemanager
*/
void DirectXRenderer::addTexture(std::string textname, TextureWrapper* Text)
{
	Textures.insert(std::pair<std::string, TextureWrapper*>(textname, Text));
}

/**
* Function: Renderer::addMesh(std::string meshname, MeshWrapper* Mesh)
* Description: Adds a mesh to the Renderer-specific list of meshes, which is managed by the resourcemanager
*/
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

/**
* Function: Renderer::CreateVertexBuffer(int heightmapvertex, EDWORD usage, EDWORD fvf, EPOOL pool, std::string vertexbuffername, HANDLE handle)
* Description: Creates a vertexbuffer
*/
HRESULT DirectXRenderer::CreateVertexBuffer(int heightmapvertex, EDWORD usage, EDWORD fvf, EPOOL pool, std::string vertexbuffername, HANDLE handle)
{
	VertexBufferExists(vertexbuffername);

	LPDIRECT3DVERTEXBUFFER9 vertexbuffer = VertexBuffers.find(vertexbuffername)->second;

	HRESULT result = g_pd3dDevice->CreateVertexBuffer(heightmapvertex, usage, fvf, static_cast<D3DPOOL>(pool), &vertexbuffer, NULL);

	VertexBuffers.find(vertexbuffername)->second = vertexbuffer;

	return result;
}

/**
* Function: Renderer::CreateIndexBuffer(int length, EDWORD usage, EFORMAT format, EPOOL pool, std::string indexbuffername, HANDLE* handle)
* Description: Creates an indexbuffer
*/
HRESULT DirectXRenderer::CreateIndexBuffer(int length, EDWORD usage, EFORMAT format, EPOOL pool, std::string indexbuffername, HANDLE* handle)
{
	IndexBufferExists(indexbuffername);

	LPDIRECT3DINDEXBUFFER9 indexbuffer = IndexBuffers.find(indexbuffername)->second;

	HRESULT result = g_pd3dDevice->CreateIndexBuffer(length, usage, static_cast<D3DFORMAT>(format), static_cast<D3DPOOL>(pool), &indexbuffer, NULL);

	IndexBuffers.find(indexbuffername)->second = indexbuffer;

	return result;
}

/**
* Function: Renderer::LockVertexBuffer(std::string vertexbuffername, int offsettolock, int sizetolock, void** pbdata, EDWORD flags)
* Description: Locks an existing unlocked vertexbuffer
*/
HRESULT DirectXRenderer::LockVertexBuffer(std::string vertexbuffername, int offsettolock, int sizetolock, void** pbdata, EDWORD flags)
{
	LPDIRECT3DVERTEXBUFFER9 vertexbuffer = VertexBuffers.find(vertexbuffername)->second;

	return (vertexbuffer)->Lock(offsettolock, sizetolock, pbdata, flags);
}

/**
* Function: Renderer::LockIndexBuffer(std::string indexbuffername, int offsettolock, int sizetolock, void** pbdata, EDWORD flags)
* Description: Locks an existing unlocked indexbuffer
*/
HRESULT DirectXRenderer::LockIndexBuffer(std::string indexbuffername, int offsettolock, int sizetolock, void** pbdata, EDWORD flags)
{
	LPDIRECT3DINDEXBUFFER9 indexbuffer = IndexBuffers.find(indexbuffername)->second;

	return (indexbuffer)->Lock(offsettolock, sizetolock, pbdata, flags);
}

/**
* Function: Renderer::UnlockVertexBuffer(std::string vertexbuffername)
* Description: Unlocks an existing locked vertexbuffer
*/
HRESULT DirectXRenderer::UnlockVertexBuffer(std::string vertexbuffername)
{
	LPDIRECT3DVERTEXBUFFER9 vertexbuffer = VertexBuffers.find(vertexbuffername)->second;

	return (vertexbuffer)->Unlock();
}

/**
* Function: Renderer::UnlockIndexBuffer(std::string indexbuffername)
* Description: Unlocks an existing locked indexbuffer
*/
HRESULT DirectXRenderer::UnlockIndexBuffer(std::string indexbuffername)
{
	LPDIRECT3DINDEXBUFFER9 indexbuffer = IndexBuffers.find(indexbuffername)->second;

	return (indexbuffer)->Unlock();
}

/**
* Function: Renderer::VertexBufferExists(std::string vertexbuffername)
* Description: Checks if a vertexbuffer exists and returns true if it already exists, if it does not exist it initalizes a new empty vertexbuffer with the given name and returns false.
*/
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

/**
* Function: Renderer::IndexBufferExists(std::string indexbuffername)
* Description: Checks if a indexbuffer exists and returns true if it already exists, if it does not exist it initalizes a new empty indexbuffer with the given name and returns false.
*/
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

/**
* Function: Renderer::setTransform(ETRANSFORMSTATETYPE transform, MatrixWrapper* matrix)
* Description: Sets the transform of given matrix
*/
HRESULT DirectXRenderer::setTransform(ETRANSFORMSTATETYPE transform, MatrixWrapper* matrix)
{
	return g_pd3dDevice->SetTransform(static_cast<D3DTRANSFORMSTATETYPE>(transform), &matrix->GetMatrix());
}

/**
* Function: Renderer::SetStreamSource(int streamnumber, std::string vertexbuffername, int offset, int stride)
* Description: Sets the stream source for a vertexbuffer that has been loaded
*/
HRESULT DirectXRenderer::SetStreamSource(int streamnumber, std::string vertexbuffername, int offset, int stride)
{
	LPDIRECT3DVERTEXBUFFER9 vertexbuffer = VertexBuffers.find(vertexbuffername)->second;

	SetFVF(ECUSTOMFVF);

	return g_pd3dDevice->SetStreamSource(streamnumber, vertexbuffer, offset, stride);
}

/**
* Function: Renderer::SetFVF(EDWORD FVF)
* Description: Set the FVF
*/
HRESULT DirectXRenderer::SetFVF(EDWORD FVF)
{
	return g_pd3dDevice->SetFVF(FVF);
}

/**
* Function: Renderer::SetIndices(std::string indexbuffername)
* Description: Set the indices to draw with, loaded from a indexbuffer that has been created and filled.
*/
HRESULT DirectXRenderer::SetIndices(std::string indexbuffername)
{
	LPDIRECT3DINDEXBUFFER9 indexbuffer = IndexBuffers.find(indexbuffername)->second;

	return g_pd3dDevice->SetIndices(indexbuffer);
}

/**
* Function: Renderer::DrawIndexedPrimitive(EPRIMITIVETYPE type, int basevertexindex, int minvertexindex, int numvertices, int startindex, int primcount)
* Description: Draws a primitive
*/
HRESULT DirectXRenderer::DrawIndexedPrimitive(EPRIMITIVETYPE type, int basevertexindex, int minvertexindex, int numvertices, int startindex, int primcount)
{
	return g_pd3dDevice->DrawIndexedPrimitive(static_cast<D3DPRIMITIVETYPE>(type), basevertexindex, minvertexindex, numvertices, startindex, primcount);
}

/**
* Function: Renderer::LoadShaderFromFile(std::string shadername, std::string shaderfilepath, std::string vertexshaderfunctionname, std::string pixelshaderfunctionname)
* Description: WARNING: INCOMPLETE/BROKEN FUNCTION. DO NOT USE. Loads a shader from a local file into the resource manager's list.
*/
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

			//errorstring = DXGetErrorDescriptionA(error);

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

/**
* Function: Renderer::SetShader(std::string shadername)
* Description: WARNING: INCOMPLETE/BROKEN FUNCTION. DO NOT USE. Set a shader to draw with
*/
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

/**
* Function: Renderer::StopRenderingWithShaders()
* Description: WARNING: INCOMPLETE/BROKEN FUNCTION. DO NOT USE. Stop drawing with any shaders
*/
void DirectXRenderer::StopRenderingWithShaders()
{
	g_pd3dDevice->SetVertexShader(NULL);
	g_pd3dDevice->SetPixelShader(NULL);
}

/**
* Function: Renderer::SetZBuffer(bool state)
* Description: Turn the zbuffer on or off
*/
void DirectXRenderer::SetZBuffer(bool state)
{
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, state);
}

/**
* Function: Renderer::Clear(EDWORD count, EDWORD flags, ECOLOR color, float z, EDWORD stencil
* Description: Clear the scene
*/
void DirectXRenderer::Clear(EDWORD count, EDWORD flags, ECOLOR color, float z, EDWORD stencil)
{
	g_pd3dDevice->Clear(count, NULL, flags, color, z, stencil);
}

/**
* Function: Renderer::BeginS()
* Description: Begin the Scene
*/
void DirectXRenderer::BeginS()
{
	g_pd3dDevice->BeginScene();
}

/**
* Function: Renderer::EndS()
* Description: End the Scene
*/
void DirectXRenderer::EndS()
{
	g_pd3dDevice->EndScene();
}

/**
* Function: Renderer::Present()
* Description: Present the Scene to the current window
*/
void DirectXRenderer::Present()
{
	g_pd3dDevice->Present( NULL, NULL, NULL, NULL );
}

/**
* Function: Renderer::getTextures()
* Description: Returns a list of all loaded textures, managed by the resource manager
*/
std::map<std::string, TextureWrapper*> DirectXRenderer::getTextures()
{
	return Textures;
}

/**
* Function: Renderer::getMeshes()
* Description: Returns a list of all loaded meshes, managed by the resource manager
*/
std::map<std::string, MeshWrapper*> DirectXRenderer::getMeshes()
{
	return Meshes;
}



// oculus test code from here on

/**
* Function: Renderer::OculusOrNah()
* Description: WARNING: INCOMPLETE/BROKEN FUNCTION. DO NOT USE. ALSO HAS A STUPID NAME.
*/
bool DirectXRenderer::OculusOrNah()
{
	return oculus;
}

/**
* Function: Renderer::OculusNowYah(bool newOculus)
* Description: WARNING: INCOMPLETE/BROKEN FUNCTION. DO NOT USE. ALSO HAS A STUPID NAME.
*/
void DirectXRenderer::OculusNowYah(bool newOculus)
{
	oculus = newOculus;
}

/**
* Function: Renderer::setViewportOculus(const OVR::Util::Render::StereoEyeParams& params)
* Description: WARNING: INCOMPLETE/BROKEN FUNCTION. DO NOT USE.
*/
void DirectXRenderer::setViewportOculus(const OVR::Util::Render::StereoEyeParams& params)
{
	D3DVIEWPORT9 dxViewport;
	ZeroMemory(&dxViewport, sizeof(D3DVIEWPORT9));
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

/**
* Function: Renderer::setupRenderToTextureOculus()
* Description: WARNING: INCOMPLETE/BROKEN FUNCTION. DO NOT USE.
*/
void DirectXRenderer::setupRenderToTextureOculus()
{
	g_pd3dDevice->SetRenderTarget(0, fullSceneSurface);
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	g_pd3dDevice->BeginScene();

};

/**
* Function: Renderer::RenderToTexture()
* Description: WARNING: INCOMPLETE/BROKEN FUNCTION. DO NOT USE.
*/
void DirectXRenderer::RenderToTexture()
{
	
	fillVertexBufferOculus("screenVertex", screenQuad, sizeof(VERTEX) * 4);
	//SetZBuffer(false);


	SetStreamSource(0, "screenVertex", 0, sizeof(VERTEX));

	g_pd3dDevice->SetTexture(0, fullSceneTexture);
	//g_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

/**
* Function: Renderer::endRenderToTextureOculus()
* Description: WARNING: INCOMPLETE/BROKEN FUNCTION. DO NOT USE.
*/
void DirectXRenderer::endRenderToTextureOculus()
{
	g_pd3dDevice->EndScene();
};

/**
* Function:Renderer::PresentWithWindow(HWND hwnd)
* Description: WARNING: INCOMPLETE/BROKEN FUNCTION. DO NOT USE.
*/
void DirectXRenderer::PresentWithWindow(HWND hwnd)
{
	g_pd3dDevice->Present(NULL, NULL, hwnd, NULL);
}

/**
* Function: Renderer::renderSceneOculus(const OVR::Util::Render::StereoEyeParams& params, OVR::Util::Render::StereoConfig SConfig)
* Description: WARNING: INCOMPLETE/BROKEN FUNCTION. DO NOT USE.
*/
void DirectXRenderer::renderSceneOculus(const OVR::Util::Render::StereoEyeParams& params, OVR::Util::Render::StereoConfig SConfig)
{
	g_pd3dDevice->SetRenderTarget(0, backBuffer);
	setViewportOculus(params);
	g_pd3dDevice->BeginScene();

	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER , D3DCOLOR_ARGB(255, 0, 0, 255), 1.0f, 0);
	//apply shader
	//render to aligned quad
	fillVertexBufferOculus("screenVertex", screenQuad, sizeof(VERTEX) * 4);
	SetZBuffer(false);
	SetStreamSource(0, "screenVertex", 0, sizeof(VERTEX));
	if (params.Eye == OVR::Util::Render::StereoEye_Right){
		//g_pd3dDevice->SetTexture(0, rightEyeTexture);
		g_pd3dDevice->SetTexture(0, tiger);
	}
	else{
		//g_pd3dDevice->SetTexture(0, leftEyeTexture);
		g_pd3dDevice->SetTexture(0, tiger);
	}

	//reset matrixes
	//MatrixWrapper* mat = new MatrixWrapper();
	//setTransform(E_WORLD, mat);
	g_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	SetZBuffer(true);

	g_pd3dDevice->EndScene();
}

/**
* Function: Renderer::fillVertexBufferOculus(std::string key, VERTEX vertices[], int size)
* Description: WARNING: INCOMPLETE/BROKEN FUNCTION. DO NOT USE.
*/
void DirectXRenderer::fillVertexBufferOculus(std::string key, VERTEX vertices[], int size)
{
	//Since this method is called repeatedly, we need to check if the requested buffer already exists or not.
	if (VertexBuffers.find(key) == VertexBuffers.end())
	{
		LPDIRECT3DVERTEXBUFFER9 vBuffer;
		g_pd3dDevice->CreateVertexBuffer(size, 0, ECUSTOMFVF, D3DPOOL_MANAGED, &vBuffer, NULL);

		void* pVertices;
		vBuffer->Lock(0, size, (void**)&pVertices, 0);
		memcpy(pVertices, vertices, size);
		vBuffer->Unlock();

		VertexBuffers.insert(std::pair<std::string, LPDIRECT3DVERTEXBUFFER9>(key, vBuffer));
	}
};

/**
* Function: Renderer::createScreenQuadOculus(float width, float height)
* Description: WARNING: INCOMPLETE/BROKEN FUNCTION. DO NOT USE.
*/
void DirectXRenderer::createScreenQuadOculus(float width, float height)
{
	VERTEX vertices[4] = {
			{ -width - 0.5f, height + 0.5f, 0.0f, 0.0f, 0.0f, 0, 0, 0 }, //top left
			{ width - 0.5f, height + 0.5f, 0.0f, 1.0f, 0.0f, 0, 0, 0 }, // top right
			{ -width - 0.5f, -height + 0.5f, 0.0f, 0.0f, 1.0f, 0, 0, 0 }, //bottom left
			{ width - 0.5f, -height + 0.5f, 0.0f, 1.0f, 1.0f, 0, 0, 0 } // bottom right
	};

	for (int i = 0; i < 4; ++i)
	{
		screenQuad[i] = vertices[i];
	}

	VERTEX verticesLeftEye[4] = {
			{ -width - 0.5f, height + 0.5f, 0.0f, 0.0f, 0.0f, 0, 0, 0 }, //top left
			{ width - 0.5f, height + 0.5f, 0.0f, 0.5f, 0.0f, 0, 0, 0 }, // top right
			{ -width - 0.5f, -height + 0.5f, 0.0f, 0.0f, 1.0f, 0, 0, 0 }, //bottom left
			{ width - 0.5f, -height + 0.5f, 0.0f, 0.5f, 1.0f, 0, 0, 0 } // bottom right
	};

	for (int i = 0; i < 4; ++i)
	{
		eyeLeftQuad[i] = verticesLeftEye[i];
	}

	VERTEX verticesRightEye[4] = {
			{ -width - 0.5f, height + 0.5f, 0.0f, 0.5f, 0.0f, 0, 0, 0 }, //top left
			{ width - 0.5f, height + 0.5f, 0.0f, 1.0f, 0.0f, 0, 0, 0 }, // top right
			{ -width - 0.5f, -height + 0.5f, 0.0f, 0.5f, 1.0f, 0, 0, 0 }, //bottom left
			{ width - 0.5f, -height + 0.5f, 0.0f, 1.0f, 1.0f, 0, 0, 0 } // bottom right
	};

	for (int i = 0; i < 4; ++i)
	{
		eyeRightQuad[i] = verticesRightEye[i];
	}
}

/**
* Function: Renderer::renderEyeOculus(const OVR::Util::Render::StereoEyeParams& params, OVR::Util::Render::StereoConfig SConfig)
* Description: WARNING: INCOMPLETE/BROKEN FUNCTION. DO NOT USE.
*/
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
	//setPixelShaderConstantsOculus(params, SConfig);

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

/**
* Function: Renderer::setViewMatrixOculus(const OVR::Util::Render::StereoEyeParams& params, OVR::Util::Render::StereoConfig SConfig)
* Description: WARNING: INCOMPLETE/BROKEN FUNCTION. DO NOT USE.
*/
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

/**
* Function: Renderer::scalarMultiply(D3DXMATRIX* matrix, float multiplyFactor)
* Description: WARNING: INCOMPLETE/BROKEN FUNCTION. DO NOT USE.
*/
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

/**
* Function: Renderer::setProjectionMatrixOculus(const OVR::Util::Render::StereoEyeParams& params, OVR::Util::Render::StereoConfig SConfig)
* Description: WARNING: INCOMPLETE/BROKEN FUNCTION. DO NOT USE.
*/
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

/**
* Function: Renderer::setPixelShaderConstantsOculus(const OVR::Util::Render::StereoEyeParams& params, OVR::Util::Render::StereoConfig SConfig)
* Description: WARNING: INCOMPLETE/BROKEN FUNCTION. DO NOT USE.
*/
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
