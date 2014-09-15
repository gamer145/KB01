#ifndef VISUALOBJECT_H
#define VISUALOBJECT_H

#include "Entity.h"
#include "Model.h"
#include "Texture.h"

class Renderer;
class VisualObject : public Entity
{
public:
	VisualObject();
	~VisualObject();
	void Initialize();
	std::string getModel();
	std::string getTexture();
	DWORD getSubSets();
	void setModel(std::string newMeshname);
	void setTexture(std::string newTextname);
	void setSubSet(int newDWORD);
	void setPosition(D3DXMATRIX newPosition);
	void draw(Renderer* myRenderer, D3DXMATRIX WorldMatrix);

private:
	std::string meshname;
	std::string textname;
	DWORD subsets;
};

#endif