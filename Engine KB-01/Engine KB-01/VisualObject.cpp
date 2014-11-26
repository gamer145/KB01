#include "VisualObject.h"

VisualObject::VisualObject()
{
	Position = new MatrixWrapper();
}

VisualObject::~VisualObject()
{
}

std::string VisualObject::getModel()
{
	return meshname;
}

std::string VisualObject::getTexture()
{
	return textname;
}

void VisualObject::setModel(std::string newMeshname)
{
	meshname = newMeshname;
}

void VisualObject::setTexture(std::string newTextname)
{
	textname = newTextname;
}

void VisualObject::setPosition(MatrixWrapper* newPosition)
{
	Position = newPosition;
}


void VisualObject::Initialize()
{
	//Not yet implemented
}

DWORD VisualObject::getSubSets()
{
	return subsets;
}

void VisualObject::setSubSet(int newDWORD)
{
	subsets = newDWORD;
}

void VisualObject::draw(RendererInterface* myRenderer)
{
	myRenderer->SetTexture(textname);

	myRenderer->setTransform(E_WORLD, getPosition());

	myRenderer->DrawSubSet(meshname);

						
}