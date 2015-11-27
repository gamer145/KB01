#include "Ground.h"
#include "EngineMath.h"


Ground::Ground()
{
	v_buffer = "HeightMapVertexBuffer";
	i_buffer = "HeightMapIndexBuffer";

	Position = new MatrixWrapper();
}

Ground::~Ground()
{
}

void Ground::SetupGroundMatrix(float x, float y, float z)
{
	MatrixWrapper* PositionalMatrix = new MatrixWrapper();
	MatrixWrapper* ScalingMatrix = new MatrixWrapper();

	PositionalMatrix->MatrixTranslation(x, y, z);
	ScalingMatrix->MatrixScaling(1000.0f, 1000.0f, 1000.0f);

	Position->SetMatrix(PositionalMatrix->GetMatrix() * ScalingMatrix->GetMatrix());
}

void Ground::CreateGround(Renderer* render, LPCWSTR argFileName)
{
	render->VertexBufferExists(v_buffer);
	render->IndexBufferExists(i_buffer);

	byte* heightmap = LoadBMP(argFileName);
	const int vertexcount = heightBMP * widthBMP;
	VERTEX* vertices;
	vertices = new VERTEX[vertexcount];
	int loopcount = 0;

	for(int x = 0; x < heightBMP; ++x)
	{
		for(int z = 0; z < widthBMP; ++z)
		{
			vertices[loopcount].x = -0.2f + (x * 0.02f);
			vertices[loopcount].y = -0.010f + (float)heightmap[loopcount]/15000;
			vertices[loopcount].z = -0.2f + (z * 0.02f);

			vertices[loopcount].tu = (1.0f / widthBMP) * x;
			vertices[loopcount].tv = (1.0f / heightBMP) * z;

			loopcount++;
		}	
	}


    // create the indices using an int array
	const int amountIndices = (heightBMP -1) * (widthBMP -1) * 6;
	int indexcount = 0;
	int ifindexcount =0;
	int ifcount = heightBMP -1;
	int* indices;
	int i1, i2, i3, i4, i5, i6;

	VECTOR* sideA;
	VECTOR* sideB;
	VERTEX* CrossProduct = new VERTEX();

	indices = new int[amountIndices];
	for(int i = 0; i < amountIndices; i+=6)
	{
		if(ifcount == ifindexcount )
		{
			indexcount++;
			ifcount+=(heightBMP-1);
		}

		i1 = 0 + 1 * indexcount;
		i2 = (heightBMP + 1) + 1 * indexcount;
		i3 = heightBMP + 1 * indexcount;
		i4 = 0 + 1 * indexcount;
		i5 = 1 + 1 * indexcount;
		i6 = (heightBMP + 1) + 1 * indexcount;

		indices[i] = i1;	//0
		indices[i + 1] = i2;	//height + 1
		indices[i + 2] = i3;	//height
		indices[i + 3] = i4;    //0
		indices[i + 4] = i5;  //1
		indices[i + 5] = i6;  //height + 1

		//Normal Vector Calculations
		//Required for implementing Light

		sideA = new VECTOR(vertices[i2].x - vertices[i1].x, vertices[i2].y - vertices[i1].y, vertices[i2].z - vertices[i1].z);
		sideB = new VECTOR(vertices[i3].x - vertices[i1].x, vertices[i3].y - vertices[i1].y, vertices[i3].z - vertices[i1].z);

		EngineMath::CrossProductVector(CrossProduct, sideA, sideB);		

		EngineMath::AddNormals(CrossProduct, &vertices[i1]);
		EngineMath::AddNormals(CrossProduct, &vertices[i2]);
		EngineMath::AddNormals(CrossProduct, &vertices[i3]);

		sideA = new VECTOR(vertices[i2].x - vertices[i1].x, vertices[i2].y - vertices[i1].y, vertices[i2].z - vertices[i1].z);
		sideB = new VECTOR(vertices[i3].x - vertices[i1].x, vertices[i3].y - vertices[i1].y, vertices[i3].z - vertices[i1].z);

		EngineMath::CrossProductVector(CrossProduct, sideA, sideB);

		EngineMath::AddNormals(CrossProduct, &vertices[i4]);
		EngineMath::AddNormals(CrossProduct, &vertices[i5]);
		EngineMath::AddNormals(CrossProduct, &vertices[i6]);
		

		indexcount++;
		ifindexcount++;
	}

	for (int a = vertexcount; a > 0; a--)
	{
		EngineMath::Normalize(&vertices[a]);
	}


	render->CreateVertexBuffer(vertexcount*sizeof(VERTEX),
		0, ECUSTOMFVF, EPOOL_MANAGED, v_buffer, NULL);


	VOID* pVoid;
	VOID* pVoid2; // a void pointer

	// lock v_buffer and load the vertices into it
	if (FAILED(render->LockVertexBuffer(v_buffer, 0, sizeof(VERTEX) * vertexcount, (void**)&pVoid, 0)))
	{
		l->WriteToFile(Error, "VBLockFailed", 0);
	}
	memcpy(pVoid, vertices, sizeof(VERTEX) * vertexcount);

	if (FAILED(render->UnlockVertexBuffer(v_buffer)))
	{
		l->WriteToFile(Error, "VBUnLockFailed", 0);
	}

	render->CreateIndexBuffer((amountIndices)*sizeof(int),
		0, FMT_INDEX32, EPOOL_MANAGED, i_buffer, NULL);

    // create an index buffer interface called i_buffer
	

    // lock i_buffer and load the indices into it

	if( FAILED( render->LockIndexBuffer(i_buffer, 0, sizeof(int) * amountIndices, (void**)&pVoid2, 0)))
	{
		l->WriteToFile(Error, "IBLockFailed", 0);
	}

	memcpy(pVoid2, indices, sizeof(int) * amountIndices);
  	
	if (FAILED(render->UnlockIndexBuffer(i_buffer)))
	{
		l->WriteToFile(Error, "IBUnLockFailed", 0);
	}
}

byte* Ground::LoadBMP(LPCWSTR argFileName)
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

void Ground::RenderGround(Renderer* render)
{
	

	if( FAILED(render->setTransform(E_WORLD, Position)))
	{
		l->WriteToFile(Error, "SetTransformFailed", 0);
	}
	if( FAILED(render->SetStreamSource(0, v_buffer, 0, sizeof(VERTEX))))
	{
		l->WriteToFile(Error, "SetStreamSourceFailed", 0);
	}
	if( FAILED(render->SetFVF(ECUSTOMFVF)))
	{
		l->WriteToFile(Error, "SetFVFFailed", 0);
	}
	if( FAILED(render->SetIndices(i_buffer)))
	{
		l->WriteToFile(Error, "SetIndicesFailed", 0);
	}
	if( FAILED(render->SetTexture("grass.jpg")))
	{
		l->WriteToFile(Error, "SetTextureHMFailed", 0);
	}
	if( FAILED(render->DrawIndexedPrimitive(EPT_TRIANGLELIST, 0, 0, (heightBMP * widthBMP), 0, (heightBMP-1) * (widthBMP-1) * 2)))
	{
		l->WriteToFile(Error, "IndexDrawFailed", 0);
	}
}

int Ground::GetHeight()
{
	return heightBMP;
}

int Ground::GetWidth()
{
	return widthBMP;
}