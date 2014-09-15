#ifndef MODEL_H
#define MODEL_H

#include "iostream"

class Model
{
public:
	Model();
	~Model();
	std::string getModelName();
	void setModelName(std::string newModel);

	
	void* getActualModel();
	void setActualModel(void* newModel);
	void* getMesh();
	void setMesh(void* newMesh);

private:
	std::string ModelName;
	void* ActualModel;
	void* mesh;
};

#endif // MODEL_H //

