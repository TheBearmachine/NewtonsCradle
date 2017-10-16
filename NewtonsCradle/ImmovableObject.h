#pragma once
#include "PhysicalObject.h"

class ImmovableObject : public PhysicalObject
{
public:
	ImmovableObject(const VectorF &pos);
	virtual ~ImmovableObject();

	virtual sf::FloatRect getBroadDetectionBox() { return sf::FloatRect(); }
	virtual void getNarrowDetectionData(float* outValues) {}
	virtual void onCollision(VectorF penetration) {}

	virtual void setVelocity(const VectorF &v) {}
	virtual VectorF getVelocity() const { return VectorF(0.0f, 0.0f); }

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {}
	virtual void onCollision(VectorF penetration, VectorF velocity) {}
	virtual void update(const sf::Time &deltaTime) {}
	virtual void lateUpdate(const sf::Time &deltaTime) {}

private:
};