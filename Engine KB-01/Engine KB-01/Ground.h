#ifndef GROUND_H
#define GROUND_H

#include "Logger.h"
#include "Renderer.h"
#include "EngineMath.h"


class Ground
{
public:
	Ground();
	~Ground();
	void SetupGroundMatrix(float x, float y, float z);
	void CreateGround(Renderer* render, LPCWSTR argFileName);
	void RenderGround(Renderer* render);
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