#include "Skybox.h"

Skybox::Skybox()
{
	amountOfVertices = 24;
	amountOfIndices = 36;
		
	aSkyboxVertices = new LIGHTLESSVERTEX[amountOfVertices];
	
	aSkyboxVertices[0] = LIGHTLESSVERTEX(-2.0f, -2.0f, 2.0f, 0.25f, 0.6666f);//front
	aSkyboxVertices[1] = LIGHTLESSVERTEX(2.0f, -2.0f, 2.0f, 0.50f, 0.6666f);
	aSkyboxVertices[2] = LIGHTLESSVERTEX(2.0f, 2.0f, 2.0f, 0.50f, 0.3333f);
	aSkyboxVertices[3] = LIGHTLESSVERTEX(-2.0f, 2.0f, 2.0f, 0.25f, 0.3333f);
	aSkyboxVertices[4] = LIGHTLESSVERTEX(2.0f, -2.0f, 2.0f, 0.50f, 0.6666f);//right
	aSkyboxVertices[5] = LIGHTLESSVERTEX(2.0f, -2.0f, -2.0f, 0.75f, 0.6666f);
	aSkyboxVertices[6] = LIGHTLESSVERTEX(2.0f, 2.0f, -2.0f, 0.75f, 0.3333f);
	aSkyboxVertices[7] = LIGHTLESSVERTEX(2.0f, 2.0f, 2.0f, 0.50f, 0.3333f);
	aSkyboxVertices[8] = LIGHTLESSVERTEX(2.0f, -2.0f, -2.0f, 0.75f, 0.6666f);//back
	aSkyboxVertices[9] = LIGHTLESSVERTEX(-2.0f, -2.0f, -2.0f, 1.0f, 0.6666f);
	aSkyboxVertices[10] = LIGHTLESSVERTEX(-2.0f, 2.0f, -2.0f, 1.0f, 0.3333f);
	aSkyboxVertices[11] = LIGHTLESSVERTEX(2.0f, 2.0f, -2.0f, 0.75f, 0.3333f);
	aSkyboxVertices[12] = LIGHTLESSVERTEX(-2.0f, -2.0f, -2.0f, 0.0f, 0.6666f);//left
	aSkyboxVertices[13] = LIGHTLESSVERTEX(-2.0f, -2.0f, 2.0f, 0.25f, 0.6666f);
	aSkyboxVertices[14] = LIGHTLESSVERTEX(-2.0f, 2.0f, 2.0f, 0.25f, 0.3333f);
	aSkyboxVertices[15] = LIGHTLESSVERTEX(-2.0f, 2.0f, -2.0f, 0.0f, 0.3333f);
	aSkyboxVertices[16] = LIGHTLESSVERTEX(-2.0f, 2.0f, 2.0f, 0.25f, 0.3333f);//top
	aSkyboxVertices[17] = LIGHTLESSVERTEX(2.0f, 2.0f, 2.0f, 0.50f, 0.3333f);
	aSkyboxVertices[18] = LIGHTLESSVERTEX(2.0f, 2.0f, -2.0f, 0.50f, 0.0f);
	aSkyboxVertices[19] = LIGHTLESSVERTEX(-2.0f, 2.0f, -2.0f, 0.25f, 0.0f);
	aSkyboxVertices[20] = LIGHTLESSVERTEX(-2.0f, -2.0f, 2.0f, 0.25f, 0.6666f);//bottom
	aSkyboxVertices[21] = LIGHTLESSVERTEX(2.0f, -2.0f, 2.0f, 0.50f, 0.6666f);
	aSkyboxVertices[22] = LIGHTLESSVERTEX(2.0f, -2.0f, -2.0f, 0.50f, 1.0f);
	aSkyboxVertices[23] = LIGHTLESSVERTEX(-2.0f, -2.0f, -2.0f, 0.25f, 1.0f);

	aSkyboxIndices = new unsigned int[amountOfIndices];

	aSkyboxIndices[0] = 0; aSkyboxIndices[2] = 1; aSkyboxIndices[1] = 2;//front
	aSkyboxIndices[3] = 0; aSkyboxIndices[5] = 2; aSkyboxIndices[4] = 3;
	aSkyboxIndices[6] = 4; aSkyboxIndices[8] = 5; aSkyboxIndices[7] = 6;//right
	aSkyboxIndices[9] = 4; aSkyboxIndices[11] = 6; aSkyboxIndices[10] = 7;
	aSkyboxIndices[12] = 8; aSkyboxIndices[14] = 9; aSkyboxIndices[13] = 10;//back
	aSkyboxIndices[15] = 8; aSkyboxIndices[17] = 10; aSkyboxIndices[16] = 11;
	aSkyboxIndices[18] = 12; aSkyboxIndices[20] = 13; aSkyboxIndices[19] = 14;//left
	aSkyboxIndices[21] = 12; aSkyboxIndices[23] = 14; aSkyboxIndices[22] = 15;
	aSkyboxIndices[24] = 16; aSkyboxIndices[26] = 17; aSkyboxIndices[25] = 18;//top
	aSkyboxIndices[27] = 16; aSkyboxIndices[29] = 18; aSkyboxIndices[28] = 19;
	aSkyboxIndices[31] = 20; aSkyboxIndices[32] = 21; aSkyboxIndices[30] = 22;//bottom
	aSkyboxIndices[34] = 20; aSkyboxIndices[35] = 22; aSkyboxIndices[33] = 23;

	i_buffer = "SkyboxIndexBuffer";
	v_buffer = "SkyboxVertexBuffer";
}

Skybox::~Skybox()
{

}

void Skybox::SetTexture(std::string tex)
{
	texture = tex;
}

void Skybox::InitializeSkybox(Renderer* renderer, Resource_Manager* resourcemanager)
{

	resourcemanager->loadManualTexture(texture);

	if ((!i_buffer.empty()) && (!v_buffer.empty()))
	{
		if (FAILED(renderer->CreateIndexBuffer(amountOfIndices * sizeof(int), 0, FMT_INDEX32, EPOOL_DEFAULT, i_buffer, NULL)))
		{
			l->WriteToFile(Error, "Skybox CreateIndexBuffer failed");
		}
		if (FAILED(renderer->CreateVertexBuffer(amountOfVertices * sizeof(LIGHTLESSVERTEX), 0, ECUSTOMLIGHTLESSFVF, EPOOL_DEFAULT, v_buffer, NULL)))
		{
			l->WriteToFile(Error, "Skybox CreateVertexBuffer failed");
		}
	}
	else
	{
		l->WriteToFile(Error, "Skybox Buffers not empty");
	}
}

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