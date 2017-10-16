#include "Ball.h"
#include <SFML/Graphics/RenderTarget.hpp>

Ball::Ball() :
	Ball(VectorF(), 10.0f)
{

}

Ball::Ball(VectorF pos, float radius) :
	PhysicalObject(),
	circleShape(radius)
{
	collidableType = CollidableType::Circle;
	circleShape.setFillColor(sf::Color(125, 125, 125, 255));
	offset.x = circleShape.getLocalBounds().width / 2.0f;
	offset.y = circleShape.getLocalBounds().height / 2.0f;

#ifdef DEBUG
	debugRect.setFillColor(sf::Color::Transparent);
	debugRect.setOutlineColor(sf::Color::Red);
	debugRect.setOutlineThickness(-1.0f);
	debugRect.setSize(sf::Vector2f(circleShape.getRadius() * 2.0f, circleShape.getRadius() * 2.0f));
#endif // DEBUG
}

Ball::~Ball()
{

}

void Ball::setColor(const sf::Color & col)
{
	circleShape.setFillColor(col);
}

void Ball::setRadius(const float & r)
{
	circleShape.setRadius(r);
	offset.x = r;
	offset.y = r;

#ifdef DEBUG
	debugRect.setSize(sf::Vector2f(circleShape.getRadius() * 2.0f, circleShape.getRadius() * 2.0f));
#endif // DEBUG
}

sf::FloatRect Ball::getBroadDetectionBox()
{
	return sf::FloatRect(position.x - offset.x, position.y - offset.y, circleShape.getRadius() * 2.0f, circleShape.getRadius() * 2.0f);
}

void Ball::getNarrowDetectionData(float * outValues)
{
	outValues[0] = position.x;
	outValues[1] = position.y;
	outValues[2] = circleShape.getRadius();
}

void Ball::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform.translate(sf::Vector2f(position.x - offset.x, position.y - offset.y));
	target.draw(circleShape, states);

#ifdef DEBUG
	target.draw(debugRect, states);
#endif // DEBUG
}
