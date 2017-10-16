#include "ImmovableObject.h"

ImmovableObject::ImmovableObject(const VectorF & pos)
{
	position = pos;
	applyGravity = false;
	collidableType = CollidableType::ImmovableObject;
}

ImmovableObject::~ImmovableObject()
{
}
