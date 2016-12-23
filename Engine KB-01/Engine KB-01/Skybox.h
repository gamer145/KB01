#ifndef SKYBOX_H
#define SKYBOX_H

#include "Logger.h"
#include "Renderer.h"
#include "EngineKB01Definitions.h"
#include "Resource_Manager.h"

class Skybox
{
public:
	//Constructor
	Skybox();

	//Destructor
	~Skybox();

	//initializes the skybox, creating the index and vertexbuffer used for drawing the skybox.
	void InitializeSkybox(Renderer* renderer, Resource_Manager* resourcemanager);

	//Draws the skybox to the active scene.
	void DrawSkybox(Renderer* renderer, MatrixWrapper* cameraposition);

	//Sets the skybox' texture
	void SetTexture(std::string tex);

private:
	//The index buffer's name 
	std::string i_buffer;

	//The vertex buffer's name
	std::string v_buffer;

	//The texture's name
	std::string texture;

	//Logger, our friend
	Logger* l;

	//the Amount of Vertices that we're going to load in
	int amountOfVertices;

	//the Amount of Indices that we're going to load in, based upon amount of Vertices
	int amountOfIndices;

	//The vertexbuffer as a lightless vertex
	LIGHTLESSVERTEX* skyboxVertices;

	//indics to be loaded into the indexbuffer
	unsigned int* skyboxIndices;
};

#endif