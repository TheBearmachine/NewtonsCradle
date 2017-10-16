#pragma once
#include "PhysicalObject.h"
#include <SFML/Graphics/CircleShape.hpp>

class Ball : public PhysicalObject
{
public:
	Ball();
	Ball(VectorF pos, float radius);
	virtual ~Ball();

	void setColor(const sf::Color &col);
	void setRadius(const float &r);

	virtual void setVelocity(const VectorF &v) = 0;
	virtual VectorF getVelocity() const = 0;

	virtual sf::FloatRect getBroadDetectionBox() override;
	virtual void getNarrowDetectionData(float* outValues) override;
	virtual void onCollision(VectorF penetration) = 0;

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
	virtual void update(const sf::Time &deltaTime) = 0;
	virtual void lateUpdate(const sf::Time &deltaTime) = 0;

private:
	sf::CircleShape circleShape;
};