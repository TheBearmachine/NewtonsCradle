#pragma once
#include "Constraint.h"
#include "PhysicalObject.h"
#include <SFML/Graphics/VertexArray.hpp>

// Anchors two objects to eachother, currently only works
// if the first is a immovable object and the second a ball
class StringConstraint : public Constraint
{
public:
	StringConstraint(float length);
	virtual ~StringConstraint();

	// The first is the anchor point and the second is the mass
	void setAttachments(PhysicalObject* obj0, PhysicalObject* obj1);

	virtual void solveConstraint(const sf::Time &deltaTime) override;

	virtual void update(const sf::Time &deltaTime) override;
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

private:
	// The first is the anchor point and the second is the mass
	PhysicalObject *attachments[2];
	sf::VertexArray line;
	float lineThickness;
	float length;
	float torque;
	float L;
	float orient;
};