#include "Model.h"


Model::Model(void)
{

}


Model::~Model(void)
{

}

std::string Model::getModelName()
{
	return Model::ModelName;
}

void Model::setModelName(std::string newModelName)
{
	Model::ModelName = newModelName;
}

void* Model::getActualModel()
{
	return ActualModel;
}

void Model::setActualModel(void* newModel)
{
	ActualModel = newModel;
}

void* Model::getMesh()
{
	return mesh;
}

void Model::setMesh(void* newMesh)
{
	mesh = newMesh;
}