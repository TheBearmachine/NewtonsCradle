#pragma once
#include "Ball.h"

class EulerBall : public Ball
{
public:
	EulerBall();
	EulerBall(VectorF pos, float radius);

	virtual void onCollision(VectorF penetration) override;

	virtual void setVelocity(const VectorF &v);
	virtual VectorF getVelocity() const;

	virtual void update(const sf::Time &deltaTime);
	virtual void lateUpdate(const sf::Time &deltaTime);

private:
	VectorF velocity;
	VectorF postPosition;
};