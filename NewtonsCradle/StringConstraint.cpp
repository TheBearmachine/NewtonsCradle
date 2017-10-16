#include "StringConstraint.h"
#include "VectorRotation.h"
#include <SFML/Graphics/RenderTarget.hpp>

static const float GRAVITY_CONSTANT = 9.82f;

StringConstraint::StringConstraint(float length) :
	length(length), attachments(), lineThickness(2.0f)
{
	line.setPrimitiveType(sf::PrimitiveType::Quads);
	line.resize(4);
	for (size_t i = 0; i < 4; i++)
	{
		line[i].color = sf::Color::Green;
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
	if (string.magnitude() > length)
	{
		for (size_t i = 0; i < 4; i++)
		{
			line[i].color = sf::Color::Red;
		}
		if (attachments[0]->getCollidableType == PhysicalObject::CollidableType::ImmovableObject)
		{
			//float angle = VectorF::angleBetweenVectors(string, VectorF(0.0f, 1.0f)); // Angle between the string and the gravity vector
			//if (angle > 90)
			//	angle = VectorF::angleBetweenVectors(string, VectorF(0.0f, -1.0f));

			VectorF dir = VectorF::normalize(string);
			VectorF grav0 = VectorF(0.0f, 1.0f) * attachments[0]->getMass() * GRAVITY_CONSTANT * deltaTime.asSeconds();
			VectorF grav1 = VectorF(0.0f, 1.0f) * attachments[1]->getMass() * GRAVITY_CONSTANT * deltaTime.asSeconds();

			VectorF vBefore0 = attachments[0]->getVelocity();
			VectorF vBefore1 = attachments[1]->getVelocity();

			//VectorF vAfter0 = attachments[0]->getVelocity();
			//VectorF vAfter1 = attachments[1]->getVelocity();


			float extension = string.magnitude() - length;
			VectorF pen0 = (dir * extension).project(vBefore0);
			VectorF pen1 = (dir * -extension).project(vBefore1);

			//attachments[0]->applyForce();
			//attachments[1]->applyForce();

			attachments[0]->onCollision(pen0);
			attachments[1]->onCollision(pen1);
			//attachments[0]->applyForce( sinf(angle) * );
		}
	}
	else
	{
		for (size_t i = 0; i < 4; i++)
		{
			line[i].color = sf::Color::Green;
		}
	}
}

void StringConstraint::update(const sf::Time & deltaTime)
{
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
