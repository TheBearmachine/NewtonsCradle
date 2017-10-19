#include "StringConstraint.h"
#include "VectorRotation.h"
#include <SFML/Graphics/RenderTarget.hpp>

static const float GRAVITY_CONSTANT = 9.82f;

StringConstraint::StringConstraint(float length) :
	length(length), attachments(), lineThickness(2.0f),
	orient(0.0f), torque(0.0f), L(0.0f)
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
	if (attachments[0]->getCollidableType() == PhysicalObject::CollidableType::ImmovableObject)
	{
		//float angle = VectorF::angleBetweenVectors(string, VectorF(0.0f, 1.0f)); // Angle between the string and the gravity vector
		//if (angle > 90)
		//	angle = VectorF::angleBetweenVectors(string, VectorF(0.0f, -1.0f));

		VectorF dir = VectorF::normalize(string);
		attachments[1]->setPosition(attachments[0]->getPosition() + dir * length);

		VectorF gForce(0.0f, GRAVITY_CONSTANT);

		VectorF r = attachments[1]->getPosition() - attachments[0]->getPosition();
		// Since i have no vector3 representation, this is an ugly cross product of only the z-component
		float z = r.x * gForce.y - r.y * gForce.x;
		float angularVelocity = attachments[1]->getInvertedMass() * L;
		orient += angularVelocity * deltaTime.asSeconds();
		torque += z;
		L += torque * deltaTime.asSeconds();
		torque = 0.0f;

		// v1(0, 0, ang) X r
		// v1.y * r.z - v1.z * v2.y
		// v1.z * r.x - v1.x * r.z
		VectorF finalVelocity = VectorF(-angularVelocity * r.y, angularVelocity * r.x);
		attachments[1]->setVelocity(finalVelocity);

		//VectorF vAfter0 = attachments[0]->getVelocity();
		//VectorF vAfter1 = attachments[1]->getVelocity();

		/*float extension = string.magnitude() - length;
		VectorF pen1 = (dir * -extension).project(vBefore);*/

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
