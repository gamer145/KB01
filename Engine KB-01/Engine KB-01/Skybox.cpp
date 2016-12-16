#include "Skybox.h"

Skybox::Skybox()
{
	amountOfVertices = 24;
	amountOfIndices = 36;
		
	skyboxVertices = new LIGHTLESSVERTEX[amountOfVertices];
	
	skyboxVertices[0] = LIGHTLESSVERTEX(-2.0f, -2.0f, 2.0f, 0.25f, 0.6666f);//front
	skyboxVertices[1] = LIGHTLESSVERTEX(2.0f, -2.0f, 2.0f, 0.50f, 0.6666f);
	skyboxVertices[2] = LIGHTLESSVERTEX(2.0f, 2.0f, 2.0f, 0.50f, 0.3333f);
	skyboxVertices[3] = LIGHTLESSVERTEX(-2.0f, 2.0f, 2.0f, 0.25f, 0.3333f);
	skyboxVertices[4] = LIGHTLESSVERTEX(2.0f, -2.0f, 2.0f, 0.50f, 0.6666f);//right
	skyboxVertices[5] = LIGHTLESSVERTEX(2.0f, -2.0f, -2.0f, 0.75f, 0.6666f);
	skyboxVertices[6] = LIGHTLESSVERTEX(2.0f, 2.0f, -2.0f, 0.75f, 0.3333f);
	skyboxVertices[7] = LIGHTLESSVERTEX(2.0f, 2.0f, 2.0f, 0.50f, 0.3333f);
	skyboxVertices[8] = LIGHTLESSVERTEX(2.0f, -2.0f, -2.0f, 0.75f, 0.6666f);//back
	skyboxVertices[9] = LIGHTLESSVERTEX(-2.0f, -2.0f, -2.0f, 1.0f, 0.6666f);
	skyboxVertices[10] = LIGHTLESSVERTEX(-2.0f, 2.0f, -2.0f, 1.0f, 0.3333f);
	skyboxVertices[11] = LIGHTLESSVERTEX(2.0f, 2.0f, -2.0f, 0.75f, 0.3333f);
	skyboxVertices[12] = LIGHTLESSVERTEX(-2.0f, -2.0f, -2.0f, 0.0f, 0.6666f);//left
	skyboxVertices[13] = LIGHTLESSVERTEX(-2.0f, -2.0f, 2.0f, 0.25f, 0.6666f);
	skyboxVertices[14] = LIGHTLESSVERTEX(-2.0f, 2.0f, 2.0f, 0.25f, 0.3333f);
	skyboxVertices[15] = LIGHTLESSVERTEX(-2.0f, 2.0f, -2.0f, 0.0f, 0.3333f);
	skyboxVertices[16] = LIGHTLESSVERTEX(-2.0f, 2.0f, 2.0f, 0.25f, 0.3333f);//top
	skyboxVertices[17] = LIGHTLESSVERTEX(2.0f, 2.0f, 2.0f, 0.50f, 0.3333f);
	skyboxVertices[18] = LIGHTLESSVERTEX(2.0f, 2.0f, -2.0f, 0.50f, 0.0f);
	skyboxVertices[19] = LIGHTLESSVERTEX(-2.0f, 2.0f, -2.0f, 0.25f, 0.0f);
	skyboxVertices[20] = LIGHTLESSVERTEX(-2.0f, -2.0f, 2.0f, 0.25f, 0.6666f);//bottom
	skyboxVertices[21] = LIGHTLESSVERTEX(2.0f, -2.0f, 2.0f, 0.50f, 0.6666f);
	skyboxVertices[22] = LIGHTLESSVERTEX(2.0f, -2.0f, -2.0f, 0.50f, 1.0f);
	skyboxVertices[23] = LIGHTLESSVERTEX(-2.0f, -2.0f, -2.0f, 0.25f, 1.0f);

	skyboxIndices = new unsigned int[amountOfIndices];

	skyboxIndices[0] = 0; skyboxIndices[2] = 1; skyboxIndices[1] = 2;//front
	skyboxIndices[3] = 0; skyboxIndices[5] = 2; skyboxIndices[4] = 3;
	skyboxIndices[6] = 4; skyboxIndices[8] = 5; skyboxIndices[7] = 6;//right
	skyboxIndices[9] = 4; skyboxIndices[11] = 6; skyboxIndices[10] = 7;
	skyboxIndices[12] = 8; skyboxIndices[14] = 9; skyboxIndices[13] = 10;//back
	skyboxIndices[15] = 8; skyboxIndices[17] = 10; skyboxIndices[16] = 11;
	skyboxIndices[18] = 12; skyboxIndices[20] = 13; skyboxIndices[19] = 14;//left
	skyboxIndices[21] = 12; skyboxIndices[23] = 14; skyboxIndices[22] = 15;
	skyboxIndices[24] = 16; skyboxIndices[26] = 17; skyboxIndices[25] = 18;//top
	skyboxIndices[27] = 16; skyboxIndices[29] = 18; skyboxIndices[28] = 19;
	skyboxIndices[31] = 20; skyboxIndices[32] = 21; skyboxIndices[30] = 22;//bottom
	skyboxIndices[34] = 20; skyboxIndices[35] = 22; skyboxIndices[33] = 23;

	i_buffer = "SkyboxIndexBuffer";
	v_buffer = "SkyboxVertexBuffer";

	l = Logger::GetLogger();
}

Skybox::~Skybox()
{
	if (skyboxVertices != NULL) {
		delete skyboxVertices;
	}

	if (l != NULL) {
		l = NULL;
		delete l;
	}
	
}

/**
* Function:	Skybox::SetTexture(std::string tex)
* Description:	Sets the skybox' texture
*/
void Skybox::SetTexture(std::string tex)
{
	texture = tex;
}

/**
* Function:	Skybox::InitializeSkybox(Renderer* renderer, Resource_Manager* resourcemanager)
* Description:	initializes the skybox, creating the index and vertexbuffer used for drawing the skybox.
*/
void Skybox::InitializeSkybox(Renderer* renderer, Resource_Manager* resourcemanager)
{

	resourcemanager->loadManualTexture(texture);

	renderer->VertexBufferExists(v_buffer); 
	renderer->IndexBufferExists(i_buffer); 

	if ((!i_buffer.empty()) && (!v_buffer.empty()))
	{
		VOID* pVoid;
		VOID* pVoid2;

		if (FAILED(renderer->CreateVertexBuffer(amountOfVertices * sizeof(LIGHTLESSVERTEX), 0, ECUSTOMLIGHTLESSFVF, EPOOL_DEFAULT, v_buffer, NULL)))
		{
			l->WriteToFile(Error, "Skybox CreateVertexBuffer failed");
		}
		else
		{

			// lock v_buffer and load the vertices into it
			if (FAILED(renderer->LockVertexBuffer(v_buffer, 0, sizeof(LIGHTLESSVERTEX) * amountOfVertices, (void**)&pVoid, 0)))
			{
				l->WriteToFile(Error, "Skybox VBLock failed");
			}
			memcpy(pVoid, skyboxVertices, sizeof(LIGHTLESSVERTEX) * amountOfVertices);

			if (FAILED(renderer->UnlockVertexBuffer(v_buffer)))
			{
				l->WriteToFile(Error, "Skybox VBUnLock failed");
			}
		}

		if (FAILED(renderer->CreateIndexBuffer(amountOfIndices * sizeof(int), 0, FMT_INDEX32, EPOOL_DEFAULT, i_buffer, NULL)))
		{
			l->WriteToFile(Error, "Skybox CreateIndexBuffer failed");
		}		
		else
		{
			// lock i_buffer and load the indices into it

			if (FAILED(renderer->LockIndexBuffer(i_buffer, 0, sizeof(int) * amountOfIndices, (void**)&pVoid2, 0)))
			{
				l->WriteToFile(Error, "Skybox IBLock failed");
			}

			memcpy(pVoid2, skyboxIndices, sizeof(int) * amountOfIndices);

			if (FAILED(renderer->UnlockIndexBuffer(i_buffer)))
			{
				l->WriteToFile(Error, "Skybox IBUnLock failed");
			}
		}
	}
	else
	{
		l->WriteToFile(Error, "Skybox Buffers not empty");
	}
}

/**
* Function:	Skybox::DrawSkybox(Renderer* renderer, MatrixWrapper* cameraposition)
* Description:	Draws the skybox to the active scene.
*/
void Skybox::DrawSkybox(Renderer* renderer, MatrixWrapper* cameraposition)
{
	renderer->SetZBuffer(false);
	cameraposition->MatrixScaling(100, 100, 100);

	if (FAILED(renderer->setTransform(E_WORLD, cameraposition)))
	{
		l->WriteToFile(Error, "Skybox SetTransform failed");
	}
	if (FAILED(renderer->SetStreamSource(0, v_buffer, 0, sizeof(LIGHTLESSVERTEX))))
	{
		l->WriteToFile(Error, "Skybox SetStreamSource failed");
	}
	if (FAILED(renderer->SetFVF(ECUSTOMLIGHTLESSFVF)))
	{
		l->WriteToFile(Error, "Skybox SetFVF failed");
	}
	if (FAILED(renderer->SetIndices(i_buffer)))
	{
		l->WriteToFile(Error, "Skybox SetIndices failed");
	}
	if (FAILED(renderer->SetTexture(texture)))
	{
		l->WriteToFile(Error, "Skybox SetTextureHM failed");
	}
	if (FAILED(renderer->DrawIndexedPrimitive(EPT_TRIANGLELIST, 0, 0, amountOfVertices, 0, amountOfIndices / 3)))
	{
		l->WriteToFile(Error, "Skybox IndexDraw failed");
	}

	renderer->SetZBuffer(true);
}