#include "EngineMath.h"
#include <math.h>

/**
* Function:	EngineMath::AddVertices()
* Description: Adds the two xyz compontents of the VERTEXES to each other, the output VERTEX is used to store the end result as well
*/
void EngineMath::AddVertices(VERTEX* input, VERTEX* output)
{
	output->x += input->x;
	output->y += input->y;
	output->z += input->z;
}

/**
* Function:	EngineMath::AddVectors()
* Description: Adds the two xyz compontents of the VECTORS to each other, the output VECTOR is used to store the end result as well
*/
void EngineMath::AddVectors(VECTOR* input, VECTOR* output)
{
	output->X += input->X;
	output->Y += input->Y;
	output->Z += input->Z;
}

/**
* Function:	EngineMath::AddNormals()
* Description: Adds two normal components of the VERTEXES to each other, the output VERTEX is used to store the end result as well
*/
void EngineMath::AddNormals(VERTEX* input, VERTEX* output)
{
	output->nx += input->x;
	output->ny += input->y;
	output->nz += input->z;
}

/**
* Function:	EngineMath::Normalize()
* Description: Normalizes the VERTEX
*/
void EngineMath::Normalize(VERTEX* VectorToBeNormalized)
{
	float tempx = VectorToBeNormalized->nx;
	float tempy = VectorToBeNormalized->ny;
	float tempz = VectorToBeNormalized->nz;

	float length = sqrt((tempx * tempx) + (tempy * tempy) + (tempz * tempz));

	VectorToBeNormalized->nx = tempx / length;
	VectorToBeNormalized->ny = tempy / length;
	VectorToBeNormalized->nz = tempz / length;
}

/**
* Function:	EngineMath::CrossProductVector()
* Description: Multiplies two VECTORS with each other
*/
void EngineMath::CrossProductVector(VERTEX* output, VECTOR* input1, VECTOR* input2)
{
	float vecX = (input1->Y * input2->Z - input1->Z * input2->Y);
	float vecY = (input1->X * input2->Z - input1->Z * input2->X);
	float vecZ = (input1->X * input2->Y - input1->Y * input2->X);

	output->x = vecX;
	output->y = vecY;
	output->z = vecZ;
}

/**
* Function:	EngineMath::CrossProductVertex()
* Description: Multiplies two VERTEX with each other
*/
void EngineMath::CrossProductVertex(VERTEX* output, VERTEX* input1, VERTEX* input2)
{
	float vecX = (input1->y * input2->z - input1->z * input2->y);
	float vecY = (input1->x * input2->z - input1->z * input2->x);
	float vecZ = (input1->x * input2->y - input1->y * input2->x);

	output->x = vecX;
	output->y = vecY;
	output->z = vecZ;
}