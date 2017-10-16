#pragma once
#include "Constraint.h"
#include "PhysicalObject.h"
#include <SFML/Graphics/VertexArray.hpp>

class StringConstraint : public Constraint
{
public:
	StringConstraint(float length);
	virtual ~StringConstraint();

	void setAttachments(PhysicalObject* obj0, PhysicalObject* obj1);

	virtual void solveConstraint(const sf::Time &deltaTime) override;

	virtual void update(const sf::Time &deltaTime) override;
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;


private:
	PhysicalObject *attachments[2];
	sf::VertexArray line;
	float lineThickness;
	float length;
};