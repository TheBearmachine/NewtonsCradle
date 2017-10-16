#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Time.hpp>

class Constraint : public sf::Drawable
{
public:
	Constraint();
	virtual ~Constraint();

	virtual void solveConstraint(const sf::Time &deltaTime) = 0;

	virtual void update(const sf::Time &deltaTime) = 0;
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

protected:

};