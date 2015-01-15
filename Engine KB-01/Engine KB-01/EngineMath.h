#ifndef _ENGINEMATH_H_
#define _ENGINEMATH_H_

#include "EngineKB01Definitions.h"

namespace EngineMath
{
		void Normalize(VERTEX* VectorToBeNormalized);

		void AddVertices(VERTEX* input, VERTEX* output);
		void AddVectors(VECTOR* input, VECTOR* output);
		void AddNormals(VERTEX* input, VERTEX* output);

		void CrossProductVector(VERTEX* output, VECTOR* input1, VECTOR* input2);
		void CrossProductVertex(VERTEX* output, VERTEX* input1, VERTEX* input2);
};

#endif