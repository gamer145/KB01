#ifndef _ENGINEMATH_H_
#define _ENGINEMATH_H_

#include "EngineKB01Definitions.h"

namespace EngineMath
{
		//Calculates the normal vector. Overwrites the inputted vector
		void Normalize(VERTEX* VectorToBeNormalized);

		//Adds 2 vertices to each other, Vectors needs to be in VERTEX format
		//Input is added onto the output VERTEX
		void AddVertices(VERTEX* input, VERTEX* output);

		//Adds 2 vertices to each other, Vectors need to be in VECTOR format
		//Input is added onto the output VECTOR
		void AddVectors(VECTOR* input, VECTOR* output);

		//Adds the normal components of 2 vertices to each other, must be in VERTEX format
		//Input is added onto the output VERTEX
		void AddNormals(VERTEX* input, VERTEX* output);

		//Multiplies two input VECTOR and puts them into the output VECTOR
		void CrossProductVector(VERTEX* output, VECTOR* input1, VECTOR* input2);

		//Multiplies two input VERTEX and puts them into the output VERTEX
		void CrossProductVertex(VERTEX* output, VERTEX* input1, VERTEX* input2);
};

#endif