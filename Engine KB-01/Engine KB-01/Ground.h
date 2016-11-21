#ifndef GROUND_H
#define GROUND_H

#include "Logger.h"
#include "Renderer.h"
#include "EngineMath.h"
#include "Resource_Manager.h"

class Ground
{
public:
	Ground();
	~Ground();
	void SetupGroundMatrix(float x, float y, float z);
	void CreateGround(Renderer* render, Resource_Manager* resourcemanager, LPCWSTR argFileName);
	void RenderGround(Renderer* render);
	byte* LoadBMP(LPCWSTR argFileName);
	int GetHeight();
	int GetWidth();
	void SetTexture(std::string tex);

private:
	std::string i_buffer;
	std::string v_buffer;
	std::string texture;
	int heightBMP;
	int widthBMP;
	Logger* l;
	MatrixWrapper* Position;
};

#endif