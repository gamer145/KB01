#ifndef ENTITY_H
#define ENTITY_H

#include "MatrixWrapper.h"


class Entity
{
public:
	virtual MatrixWrapper* getPosition();
	virtual void Initialize() =0;
	Entity();
	~Entity();
protected:
	MatrixWrapper* Position;
private:

};

#endif