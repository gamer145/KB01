#include "Skybox.h"

Skybox::Skybox()
{
	amountOfVertices = 24;
	amountOfIndices = 36;

	aSkyboxVertices = new VERTEX[amountOfVertices]();
	
	aSkyboxVertices[0] = VERTEX(-2.0f, -2.0f, 2.0f, 0.25f, 0.6666f);//front
	aSkyboxVertices[1] = VERTEX(2.0f, -2.0f, 2.0f, 0.50f, 0.6666f);
	aSkyboxVertices[2] = VERTEX(2.0f, 2.0f, 2.0f, 0.50f, 0.3333f);
	aSkyboxVertices[3] = VERTEX(-2.0f, 2.0f, 2.0f, 0.25f, 0.3333f);
	aSkyboxVertices[4] = VERTEX(2.0f, -2.0f, 2.0f, 0.50f, 0.6666f);//right
	aSkyboxVertices[5] = VERTEX(2.0f, -2.0f, -2.0f, 0.75f, 0.6666f);
	aSkyboxVertices[6] = VERTEX(2.0f, 2.0f, -2.0f, 0.75f, 0.3333f);
	aSkyboxVertices[7] = VERTEX(2.0f, 2.0f, 2.0f, 0.50f, 0.3333f);
	aSkyboxVertices[8] = VERTEX(2.0f, -2.0f, -2.0f, 0.75f, 0.6666f);//back
	aSkyboxVertices[9] = VERTEX(-2.0f, -2.0f, -2.0f, 1.0f, 0.6666f);
	aSkyboxVertices[10] = VERTEX(-2.0f, 2.0f, -2.0f, 1.0f, 0.3333f);
	aSkyboxVertices[11] = VERTEX(2.0f, 2.0f, -2.0f, 0.75f, 0.3333f);
	aSkyboxVertices[12] = VERTEX(-2.0f, -2.0f, -2.0f, 0.0f, 0.6666f);//left
	aSkyboxVertices[13] = VERTEX(-2.0f, -2.0f, 2.0f, 0.25f, 0.6666f);
	aSkyboxVertices[14] = VERTEX(-2.0f, 2.0f, 2.0f, 0.25f, 0.3333f);
	aSkyboxVertices[15] = VERTEX(-2.0f, 2.0f, -2.0f, 0.0f, 0.3333f);
	aSkyboxVertices[16] = VERTEX(-2.0f, 2.0f, 2.0f, 0.25f, 0.3333f);//top
	aSkyboxVertices[17] = VERTEX(2.0f, 2.0f, 2.0f, 0.50f, 0.3333f);
	aSkyboxVertices[18] = VERTEX(2.0f, 2.0f, -2.0f, 0.50f, 0.0f);
	aSkyboxVertices[19] = VERTEX(-2.0f, 2.0f, -2.0f, 0.25f, 0.0f);
	aSkyboxVertices[20] = VERTEX(-2.0f, -2.0f, 2.0f, 0.25f, 0.6666f);//bottom
	aSkyboxVertices[21] = VERTEX(2.0f, -2.0f, 2.0f, 0.50f, 0.6666f);
	aSkyboxVertices[22] = VERTEX(2.0f, -2.0f, -2.0f, 0.50f, 1.0f);
	aSkyboxVertices[23] = VERTEX(-2.0f, -2.0f, -2.0f, 0.25f, 1.0f);

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
	texture = "dome2.jpg";
}

Skybox::~Skybox()
{

}

void Skybox::InitializeSkybox(Renderer* renderer, Resource_Manager* resourcemanager)
{

	resourcemanager->loadManualTexture(texture);

	if ((!i_buffer.empty()) && (!v_buffer.empty()))
	{
		

		renderer->CreateIndexBuffer(amountOfIndices * sizeof(int), 0, FMT_INDEX32, EPOOL_DEFAULT, i_buffer, NULL);
		renderer->CreateVertexBuffer(amountOfVertices * sizeof(VERTEX), 0, ECUSTOMVERTEX, EPOOL_DEFAULT, v_buffer, NULL);
	}
}

void Skybox::DrawSkybox(Renderer* renderer, MatrixWrapper* cameraposition)
{
	renderer->SetZBuffer(false);
	cameraposition->MatrixScaling(100, 100, 100);

	if (FAILED(renderer->setTransform(E_WORLD, cameraposition)))
	{
		l->WriteToFile(Error, "SetTransformFailed", 0);
	}
	if (FAILED(renderer->SetStreamSource(0, v_buffer, 0, sizeof(VERTEX))))
	{
		l->WriteToFile(Error, "SetStreamSourceFailed", 0);
	}
	if (FAILED(renderer->SetFVF(ECUSTOMVERTEX)))
	{
		l->WriteToFile(Error, "SetFVFFailed", 0);
	}
	if (FAILED(renderer->SetIndices(i_buffer)))
	{
		l->WriteToFile(Error, "SetIndicesFailed", 0);
	}
	if (FAILED(renderer->SetTexture("dome2.jpg")))
	{
		l->WriteToFile(Error, "SetTextureHMFailed", 0);
	}
	if (FAILED(renderer->DrawIndexedPrimitive(EPT_TRIANGLELIST, 0, 0, amountOfVertices, 0, amountOfIndices / 3)))
	{
		l->WriteToFile(Error, "IndexDrawFailed", 0);
	}

	renderer->SetZBuffer(true);
}