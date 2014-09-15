#include "Heightmap.h"

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_TEX1)

Heightmap::Heightmap()
{

}

Heightmap::~Heightmap()
{
}

void Heightmap::SetupHeightmapMatrix(float x, float y, float z, D3DXMATRIX OffSet)
{
	D3DXMATRIX PositionalMatrix;
	D3DXMATRIX ScalingMatrix;

	D3DXMatrixTranslation(&PositionalMatrix, x, y, z);	
	D3DXMatrixScaling(&ScalingMatrix, 1000.0f, 1000.0f, 1000.0f);  

	Position = PositionalMatrix * ScalingMatrix * OffSet;
}

/*void Heightmap::CreateHeightmap(Renderer* render, LPCWSTR argFileName)
{

	HEIGHTMAPVERTEX vertices[] = 
	{ 		
		{ -0.06f, -0.003f, 0.03f, 0xffffffff }, //0
        { -0.02f, -0.007f, 0.03f, 0xff00ffff }, //1
        { 0.02f, 0.006f, 0.03f, 0xff00ffff }, //2
		{ 0.06f, 0.004f, 0.03f, 0xffffffff }, //3

		{ -0.06f, -0.007f, 0.0f, 0xff00ffff }, //4
        { -0.02f, 0.007f, 0.0f, 0xffffff00 }, //5
        { 0.02f, 0.002f, 0.0f, 0xffffff00 }, //6
		{ 0.06f, -0.0001f, 0.0f, 0xff00ffff }, //7

		{ -0.06f, 0.003f, -0.03f, 0xffffffff }, //8
        { -0.02f, 0.005f, -0.03f, 0xff00ffff }, //9
        { 0.02f, 0.002f, -0.03f, 0xff00ffff }, //10
		{ 0.06f, 0.002f, -0.03f, 0xffffffff }, //11
	};

    HRESULT failure = render->CreateVertexBuffer(12 * sizeof(HEIGHTMAPVERTEX),
                               0, D3DFVF_CUSTOMVERTEX, D3DPOOL_MANAGED, &v_buffer, NULL);
	if (FAILED(failure))
	{
		std::string test = DXGetErrorStringA(failure);
		test = DXGetErrorDescriptionA(failure);
		l->WriteToFile(Error, "CreateVBFailed", 0);
	}
	

	VOID* pVoid;
	VOID* pVoid2; // a void pointer

    // lock v_buffer and load the vertices into it
    if( FAILED( v_buffer->Lock(0, sizeof(HEIGHTMAPVERTEX) * 12, (void**)&pVoid, 0)))
	{
		l->WriteToFile(Error, "VBLockFailed", 0);
	}
	memcpy(pVoid, vertices, sizeof(vertices));

	if ( FAILED( v_buffer->Unlock()))
	{
		l->WriteToFile(Error, "VBUnLockFailed", 0);
	}

	int indices[] = {0, 1, 4, 1, 4, 5, 1, 2, 5, 2, 5, 6, 2, 3, 6, 3, 6, 7, 4, 5, 8, 5, 8, 9, 5, 6, 9, 6, 9, 10, 6, 7, 10, 7, 10, 11};

    // create an index buffer interface called i_buffer
    if( FAILED(render->get3DDevice()->CreateIndexBuffer(36*sizeof(int),
                              0,
                              D3DFMT_INDEX32,
                              D3DPOOL_MANAGED,
                              &i_buffer,
                              NULL)))
	{
		l->WriteToFile(Error, "CreateIBFailed", 0);
	}

    // lock i_buffer and load the indices into it

	if( FAILED( i_buffer->Lock(0, sizeof(int) * 36, (void**)&pVoid2, 0)))
	{
		l->WriteToFile(Error, "IBLockFailed", 0);
	}

	memcpy(pVoid2, indices, sizeof(indices));
  	
	if ( FAILED( i_buffer->Unlock()))
	{
		l->WriteToFile(Error, "IBUnLockFailed", 0);
	}
}*/

void Heightmap::CreateHeightmap(Renderer* render, LPCWSTR argFileName)
{
	byte* heightmap = LoadBMP(argFileName);
	const int vertexcount = heightBMP * widthBMP;
	HEIGHTMAPVERTEX* vertices;
	vertices = new HEIGHTMAPVERTEX[vertexcount];
	int loopcount = 0;

	for(int x = 0; x < heightBMP; ++x)
	{
		for(int z = 0; z < widthBMP; ++z)
		{
			vertices[loopcount].x = -0.2f + (x * 0.02f);
			vertices[loopcount].y = -0.010f + (float)heightmap[loopcount]/15000;
			vertices[loopcount].z = -0.2f + (z * 0.02f);

			vertices[loopcount].tx = (1.0f / widthBMP) * x;
			vertices[loopcount].ty = (1.0f / heightBMP) * z;

			loopcount++;
		}	
	}

    // create a vertex buffer interface called v_buffer
    if( FAILED( ((LPDIRECT3DDEVICE9)render->get3DDevice())->CreateVertexBuffer(vertexcount*sizeof(HEIGHTMAPVERTEX),
                               0, D3DFVF_CUSTOMVERTEX, D3DPOOL_MANAGED, &v_buffer, NULL)))
	{
		l->WriteToFile(Error, "CreateVBFailed", 0);
	}



    VOID* pVoid;
	VOID* pVoid2; // a void pointer

    // lock v_buffer and load the vertices into it
    if( FAILED( v_buffer->Lock(0, sizeof(HEIGHTMAPVERTEX) * vertexcount, (void**)&pVoid, 0)))
	{
		l->WriteToFile(Error, "VBLockFailed", 0);
	}
	memcpy(pVoid, vertices, sizeof(HEIGHTMAPVERTEX) * vertexcount);

	if ( FAILED( v_buffer->Unlock()))
	{
		l->WriteToFile(Error, "VBUnLockFailed", 0);
	}

    // create the indices using an int array
	//(h - 1) * (b - 1) * 6, (6 vertices * vierkant)
	const int amountIndices = (heightBMP -1) * (widthBMP -1) * 6;
	int indexcount = 0;
	int ifindexcount =0;
	int ifcount = heightBMP -1;
	int* indices;
	indices = new int[amountIndices];
	for(int i = 0; i < amountIndices; i+=6)
	{
		if(ifcount == ifindexcount )
		{
			indexcount++;
			ifcount+=(heightBMP-1);
		}
		indices[i]=0 + 1*indexcount;	//0
		indices[i+1]=heightBMP + 1*indexcount;	//height
		indices[i+2]=(heightBMP+1) + 1*indexcount;	//height + 1
		indices[i+3]=0+ 1*indexcount;    //0
		indices[i+4]=1+ 1*indexcount;  //1
		indices[i+5]=(heightBMP+1) + 1*indexcount;  //height + 1
		indexcount++;
		ifindexcount++;
	}


    // create an index buffer interface called i_buffer
	if( FAILED(((LPDIRECT3DDEVICE9)render->get3DDevice())->CreateIndexBuffer((amountIndices)*sizeof(int),
                              0,
                              D3DFMT_INDEX32,
                              D3DPOOL_MANAGED,
                              &i_buffer,
                              NULL)))
	{
		l->WriteToFile(Error, "CreateIBFailed", 0);
	}

    // lock i_buffer and load the indices into it

	if( FAILED( i_buffer->Lock(0, sizeof(int) * amountIndices, (void**)&pVoid2, 0)))
	{
		l->WriteToFile(Error, "IBLockFailed", 0);
	}

	memcpy(pVoid2, indices, sizeof(int) * amountIndices);
  	
	if ( FAILED( i_buffer->Unlock()))
	{
		l->WriteToFile(Error, "IBUnLockFailed", 0);
	}
}

byte* Heightmap::LoadBMP(LPCWSTR argFileName)
{
	//Load image from file
	HDC lhdcDest;	//Handle to Device Context (Windows GDI)
	HANDLE hbmp;	//Handle to an object (standard handle)
	HINSTANCE hInst = GetModuleHandle(NULL);//Handle to an instance (instance of the window)

	//Create a memory device context compatible with the specified device (NULL)
	lhdcDest = CreateCompatibleDC(NULL);
	if (lhdcDest == NULL)	 
	{	 
		DeleteDC(lhdcDest);	//Delete the DC (prevents a memory leak!)
		return false;	//Jump out of the function
	}

	//Windows GDI load image of type BMP (fileformat)
	hbmp = LoadImage(hInst , argFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (hbmp == NULL)	//Give a visual warning if the loading of the image failed
	{
		//har s[100];
		//wsprintf(s, L"Can't find HeightMask %s", argFileName);
		//MessageBox(NULL, s, "ERROR ERROR ERROR", MB_OK);
		return false;	//Jump out of the function
	}
	//At this point it is sure that lhdcDest & hbmp are valid.

	//Load the bmp into the device context (memory space)
	SelectObject(lhdcDest, hbmp);

	//The BITMAP structure defines the type, width, height, color format, and bit values of a bitmap
	BITMAP bm;
	//The GetObject function retrieves information for the specified graphics object
	//bm is cast to a "void*" because GetObject function doesn't 'know' it's format 
	//(don't know what it is, but just put it in that buffer)
	GetObject(hbmp, sizeof(BITMAP), (void*)&bm);

	//Save the width and height of the heightmap
	widthBMP = bm.bmWidth;
	heightBMP = bm.bmHeight;

	//Create an array to hold all the heightdata
	byte* heightData = new BYTE[heightBMP*widthBMP];

	//Iterate through the BMP-file and fill the heightdata-array
	for (int lHeight = 0; lHeight < heightBMP; lHeight++)
	{
		for (int lWidth = 0; lWidth < widthBMP; lWidth++)
		{
			heightData[(lHeight*widthBMP)+lWidth+0] = GetRValue(GetPixel(lhdcDest, lHeight, lWidth));
		}
	}
	l->WriteToFile(Success, "The heightdata has been retrieved.", 0);
	return heightData;
}

void Heightmap::RenderHeightmap(Renderer* render)
{
	if( FAILED(render->setTransform(D3DTS_WORLD, &Position)))
	{
		l->WriteToFile(Error, "SetTransformFailed", 0);
	}
	if( FAILED(render->SetStreamSource(0, v_buffer, 0, sizeof(HEIGHTMAPVERTEX))))
	{
		l->WriteToFile(Error, "SetStreamSourceFailed", 0);
	}
	if( FAILED(render->SetFVF(D3DFVF_CUSTOMVERTEX)))
	{
		l->WriteToFile(Error, "SetFVFFailed", 0);
	}
	if( FAILED(render->SetIndices(i_buffer)))
	{
		l->WriteToFile(Error, "SetIndicesFailed", 0);
	}
	if( FAILED(render->SetTexture("dome.jpg")))
	{
		l->WriteToFile(Error, "SetTextureHMFailed", 0);
	}
	if( FAILED(render->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, (heightBMP * widthBMP), 0, (heightBMP-1) * (widthBMP-1) * 2)))
	{
		l->WriteToFile(Error, "IndexDrawFailed", 0);
	}
	/*if( FAILED(render->get3DDevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 12, 0, 12)))
	{
		l->WriteToFile(Error, "IndexDrawFailed", 0);
	}*/
	//render->get3DDevice()->DrawPrimitive(D3DPT_TRIANGLELIST, 0, (((height-1) * (width-1)) * 2));
}

int Heightmap::GetHeight()
{
	return heightBMP;
}

int Heightmap::GetWidth()
{
	return widthBMP;
}