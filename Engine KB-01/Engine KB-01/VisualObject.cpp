#include "VisualObject.h"

VisualObject::VisualObject()
{
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

void VisualObject::setPosition(D3DXMATRIX newPosition)
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

void VisualObject::draw(Renderer* myRenderer, D3DXMATRIX WorldMatrix)
{
	myRenderer->SetTexture(textname);
							
//	D3DXMATRIX* world = &D3DTS_WORLD;

	MatrixWrapper* TheNewMatrix = new MatrixWrapper((getPosition() * WorldMatrix));

	myRenderer->setTransform(E_WORLD, TheNewMatrix);

	myRenderer->DrawSubSet(meshname);

						
}