#ifndef HEIGHTMAP_H
#define HEIGHTMAP_H

#include "Logger.h"
#include "RendererInterface.h"

struct HEIGHTMAPVERTEX
{
   float x, y, z, tx, ty;
};

class Heightmap
{
public:
	Heightmap();
	~Heightmap();
	void SetupHeightmapMatrix(float x, float y, float z);
	void CreateHeightmap(RendererInterface* render, LPCWSTR argFileName);
	void RenderHeightmap(RendererInterface* render);
	byte* LoadBMP(LPCWSTR argFileName);
	int GetHeight();
	int GetWidth();

private:
	std::string i_buffer;
	std::string v_buffer;
	int heightBMP;
	int widthBMP;
	Logger* l;
	MatrixWrapper* Position;
};

#endif