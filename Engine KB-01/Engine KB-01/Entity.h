#ifndef ENTITY_H
#define ENTITY_H

#include "MatrixWrapper.h"

//Virtual class, every gameObject is an entity and has certain base properties. 
//But depending on their typing, they add onto this

class Entity
{
public:
	//Returns the Entity's position
	virtual MatrixWrapper* getPosition();
	virtual void Initialize() =0;
	Entity();
	~Entity();
protected:
	//Every Entity has a position in the world
	MatrixWrapper* Position;
private:

};

#endif