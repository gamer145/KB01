#ifndef ENTITY_H
#define ENTITY_H

#include <d3dx9.h>



class Entity
{
public:
	virtual D3DXMATRIX getPosition();
	virtual void Initialize() =0;
	Entity();
	~Entity();
protected:
	D3DXMATRIX Position;
private:

};

#endif