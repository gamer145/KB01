#ifndef VISUALOBJECT_H
#define VISUALOBJECT_H

#include "Entity.h"
#include "Model.h"
#include "Texture.h"
#include "Renderer.h"

class VisualObject : public Entity
{
public:
	//Constructor
	VisualObject();

	//Destructor
	~VisualObject();

	//Parent function, this does not have a specific implementation
	void Initialize();

	//Gets the model, the meshname
	std::string getModel();

	//Gets the texture, the texturename
	std::string getTexture();

	//Gets the subSets
	EDWORD getSubSets();

	//Sets the model
	void setModel(std::string newMeshname);

	//Sets the texture
	void setTexture(std::string newTextname);

	//Sets the Subset
	void setSubSet(int newDWORD);

	//Sets the Position of the VisualObject
	void setPosition(MatrixWrapper* newPosition);

	//The draw logic for a visual object, since it has visual components (a model/texture) that needs to be drawn
	void draw(Renderer* myDirectXRenderer);

private:
	//Model/meshname
	std::string meshname;

	//Texture
	std::string textname;

	//Subset, which parts of the mesh needs to be used
	EDWORD subsets;
};

#endif