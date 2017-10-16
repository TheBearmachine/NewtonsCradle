#include "PhysicalObject.h"

PhysicalObject::PhysicalObject() :
	PhysicalObject(true)
{
}

PhysicalObject::PhysicalObject(bool applyGravity) :
	position(), forces(), applyGravity(applyGravity),
	elasticity(1.0f), mass(1.0f), invertedMass(1.0f), collided(false)
{
}

PhysicalObject::~PhysicalObject()
{
}

void PhysicalObject::applyForce(const VectorF & force)
{
	forces += force;
}

void PhysicalObject::setPosition(const VectorF & pos)
{
	position = pos;
}

void PhysicalObject::setPosition(const float & x, const float & y)
{
	position.x = x;
	position.y = y;
}

void PhysicalObject::move(const VectorF & offset)
{
	position += offset;
}

void PhysicalObject::move(const float & offsetX, const float & offsetY)
{
	position.x += offsetX;
	position.y += offsetY;
}

VectorF PhysicalObject::getPosition() const
{
	return position;
}

void PhysicalObject::setMass(const float & newMass)
{
	if (newMass == 0.0f)
	{
		mass = 0.001f;
		invertedMass = 1.0f / mass;
		return;
	}
	mass = newMass;
	invertedMass = 1.0f / mass;
}

float PhysicalObject::getMass() const
{
	return mass;
}

float PhysicalObject::getInvertedMass() const
{
	return invertedMass;
}

void PhysicalObject::setApplyGravity(const bool & applyGravity)
{
	this->applyGravity = applyGravity;
}

bool PhysicalObject::getApplyGravity() const
{
	return applyGravity;
}

void PhysicalObject::setElasticity(const float & e)
{
	elasticity = e;
}

float PhysicalObject::getElasticity() const
{
	return elasticity;
}
