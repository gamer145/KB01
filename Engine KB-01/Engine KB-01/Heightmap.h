#ifndef HEIGHTMAP_H
#define HEIGHTMAP_H

#include "Logger.h"
#include "Renderer.h"


class Heightmap
{
public:
	Heightmap();
	~Heightmap();
	void SetupHeightmapMatrix(float x, float y, float z);
	void CreateHeightmap(Renderer* render, LPCWSTR argFileName);
	void RenderHeightmap(Renderer* render);
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