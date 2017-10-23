#include "StringConstraint.h"
#include "VectorRotation.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include "Constants.h"

StringConstraint::StringConstraint(float length) :
	length(length), attachments(), lineThickness(1.0f),
	orient(0.0f), torque(0.0f), L(0.0f)
{
	line.setPrimitiveType(sf::PrimitiveType::Quads);
	line.resize(4);
	for (size_t i = 0; i < 4; i++)
	{
		line[i].color = sf::Color(170, 170, 170);
	}
}

StringConstraint::~StringConstraint()
{

}

void StringConstraint::setAttachments(PhysicalObject * obj0, PhysicalObject * obj1)
{
	attachments[0] = obj0;
	attachments[1] = obj1;
}

void StringConstraint::solveConstraint(const sf::Time &deltaTime)
{
	if (attachments[0] == nullptr || attachments[1] == nullptr) return;

	VectorF string = attachments[1]->getPosition() - attachments[0]->getPosition();
	if (attachments[0]->getCollidableType() == PhysicalObject::CollidableType::ImmovableObject &&
		string.magnitude() > length)
	{
		VectorF dir = VectorF::normalize(string);

		// Calculate tension on the string
		float r = (attachments[1]->getPosition() - attachments[0]->getPosition()).magnitude();
		float v = attachments[1]->getVelocity().magnitude();
		float m = attachments[1]->getMass();
		VectorF T = (dir * (m / 100.0f) * ( v * v) / r);
		attachments[1]->applyForce(T * -1);

		// The tension force wont quite counterbalance the motion out from the string length
		// due to not considering the gravitational force, so we need to restrict the movement
		// This will lead to a constant velocity downwards on particles suspended along the gravitational axis
		attachments[1]->setPosition(attachments[0]->getPosition() + dir * length);
	}
}

void StringConstraint::update(const sf::Time & deltaTime)
{
	// All this deos is update the coordinates used to draw the string
	if (attachments[0] == nullptr || attachments[1] == nullptr) return;
	VectorF newPos[4];
	VectorRotation dir = VectorF::normalize(attachments[0]->getPosition() - attachments[1]->getPosition());
	VectorRotation rot = VectorRotation::inDegrees(90);
	dir = dir * rot;
	rot = VectorRotation::inDegrees(180);

	for (size_t i = 0; i < 2; i++)
	{
		newPos[i * 2] = attachments[i]->getPosition() + dir.toVector() * lineThickness;
		dir = dir * rot;
		newPos[i * 2 + 1] = attachments[i]->getPosition() + dir.toVector() * lineThickness;
	}

	for (size_t i = 0; i < 4; i++)
	{
		line[i].position = newPos[i].toSfVec();
	}
}

void StringConstraint::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (attachments[0] == nullptr || attachments[1] == nullptr) return;

	target.draw(line);
}
