#ifndef SKYBOX_H
#define SKYBOX_H

#include "Logger.h"
#include "Renderer.h"
#include "EngineKB01Definitions.h"
#include "Resource_Manager.h"

class Skybox
{
public:
	Skybox();
	~Skybox();
	void InitializeSkybox(Renderer* renderer, Resource_Manager* resourcemanager);
	void DrawSkybox(Renderer* renderer, MatrixWrapper* cameraposition);


private:
	std::string i_buffer;
	std::string v_buffer;
	std::string texture;
	Logger* l;
	int amountOfVertices;
	int amountOfIndices;
	VERTEX* aSkyboxVertices;
	unsigned int* aSkyboxIndices;
	//MatrixWrapper* Position;
};

#endif