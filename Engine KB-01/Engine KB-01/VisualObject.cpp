#include "VisualObject.h"

/**
* Function: VisualObject::VisualObject()
* Description: Constructor
*/
VisualObject::VisualObject()
{
	Position = new MatrixWrapper();
}

/**
* Function: VisualObject::~VisualObject()
* Description: Destructor
*/
VisualObject::~VisualObject()
{
}

/**
* Function: VisualObject::getModel()
* Description: Gets the model
*/
std::string VisualObject::getModel()
{
	return meshname;
}

/**
* Function: VisualObject::getTexture()
* Description: Gets the texture
*/
std::string VisualObject::getTexture()
{
	return textname;
}

/**
* Function: VisualObject::setModel(std::string newMeshname)
* Description: Sets the model
*/
void VisualObject::setModel(std::string newMeshname)
{
	meshname = newMeshname;
}

/**
* Function: VisualObject::setTexture(std::string newTextname)
* Description: Sets the texture
*/
void VisualObject::setTexture(std::string newTextname)
{
	textname = newTextname;
}

/**
* Function: VisualObject::setPosition(MatrixWrapper* newPosition)
* Description: Sets the Position of the VisualObject
*/
void VisualObject::setPosition(MatrixWrapper* newPosition)
{
	Position = newPosition;
}


/**
* Function: VisualObject::Initialize()
* Description: Parent function, this does not have a specific implementation
*/
void VisualObject::Initialize()
{
	//Not yet implemented
}

/**
* Function: VisualObject::getSubSets()
* Description: Gets the subsets of the visualobject
*/
DWORD VisualObject::getSubSets()
{
	return subsets;
}

/**
* Function: VisualObject::setSubSet(int newDWORD)
* Description: Sets the subsets of the visualobject
*/
void VisualObject::setSubSet(int newDWORD)
{
	subsets = newDWORD;
}

/**
* Function:  VisualObject::draw(Renderer* myDirectXRenderer)
* Description: Draw this object to the scene. Needs a renderer to draw and draws everything according to the components of the visualobject
*/
void VisualObject::draw(Renderer* myDirectXRenderer)
{
	myDirectXRenderer->SetTexture(textname);
							
	//myDirectXRenderer->RenderToTexture();

	myDirectXRenderer->setTransform(E_WORLD, getPosition());

	myDirectXRenderer->DrawSubSet(meshname);

	
}