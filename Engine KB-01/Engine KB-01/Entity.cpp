#include "Entity.h"

Entity::Entity()
{
}

Entity::~Entity()
{
	if (Position != NULL) {
		delete Position;
	}

}

MatrixWrapper* Entity::getPosition()
{
	return Position;
}