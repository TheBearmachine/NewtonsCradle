#include "EulerBall.h"

// Used to achieve a feel that the scale is smaller, by speeding up the simulation
static const float SCALE = 1.0f;

EulerBall::EulerBall() :
	Ball(), velocity()
{
}

EulerBall::EulerBall(VectorF pos, float radius) :
	Ball(pos, radius), velocity()
{
}

void EulerBall::onCollision(VectorF penetration)
{
	this->velocity = velocity;
	postPosition += penetration;
	collided = true;
}

void EulerBall::setVelocity(const VectorF & v)
{
	velocity = v;
}

VectorF EulerBall::getVelocity() const
{
	return velocity;
}

void EulerBall::update(const sf::Time & deltaTime)
{
	position += velocity * deltaTime.asSeconds() * SCALE;
	velocity += forces * invertedMass * SCALE;

	forces.x = 0.0f;
	forces.y = 0.0f;
}

void EulerBall::lateUpdate(const sf::Time & deltaTime)
{
	if (collided)
	{
		move(postPosition);
		postPosition.x = 0.0f;
		postPosition.y = 0.0f;
		collided = false;
	}
}
