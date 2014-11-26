#ifndef VISUALOBJECT_H
#define VISUALOBJECT_H

#include "Entity.h"
#include "Model.h"
#include "Texture.h"
#include "RendererInterface.h"

class Renderer;
class VisualObject : public Entity
{
public:
	VisualObject();
	~VisualObject();
	void Initialize();
	std::string getModel();
	std::string getTexture();
	EDWORD getSubSets();
	void setModel(std::string newMeshname);
	void setTexture(std::string newTextname);
	void setSubSet(int newDWORD);
	void setPosition(MatrixWrapper* newPosition);
	void draw(RendererInterface* myRenderer);

private:
	std::string meshname;
	std::string textname;
	EDWORD subsets;
};

#endif