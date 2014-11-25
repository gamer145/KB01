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

void VisualObject::draw(Renderer* myDirectXRenderer, MatrixWrapper* WorldMatrix)
{
	myDirectXRenderer->SetTexture(textname);
							
//	D3DXMATRIX* world = &D3DTS_WORLD;

	MatrixWrapper* TheNewMatrix = new MatrixWrapper();

	TheNewMatrix->SetMatrix((getPosition()->GetMatrix() * WorldMatrix->GetMatrix()));

	myDirectXRenderer->setTransform(E_WORLD, TheNewMatrix);

	myDirectXRenderer->DrawSubSet(meshname);

						
}