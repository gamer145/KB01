#ifndef GROUND_H
#define GROUND_H

#include "Logger.h"
#include "Renderer.h"
#include "EngineMath.h"
#include "Resource_Manager.h"

class Ground
{
public:
	//Constructor
	Ground();

	//Destructor
	~Ground();

	//Sets up the position of the Ground as a whole
	void SetupGroundMatrix(float x, float y, float z);

	//Sets up the Ground components, fills in all the individual vertex values and indice values. Loads it all in, prepares it all. It does way too much
	void CreateGround(Renderer* render, Resource_Manager* resourcemanager, LPCWSTR argFileName);

	//Draws the ground
	void DrawGround(Renderer* render);
	//Loads in a greyscale image specified by the path given as argument, this greyscale image is used as base to generate the ground from
	byte* LoadBMP(LPCWSTR argFileName);

	//Returns the height of the image
	int GetHeight();

	//Returns the width of the image
	int GetWidth();

	//Sets a texture to be used in the ground
	void SetTexture(std::string tex);

private:
	//IndexBuffer name
	std::string i_buffer;

	//VertexBuffer name
	std::string v_buffer;

	//Texture name
	std::string texture;

	//Height Image
	int heightBMP;

	//Width Image
	int widthBMP;

	//Logger
	Logger* l;

	//World position
	MatrixWrapper* Position;
};

#endif