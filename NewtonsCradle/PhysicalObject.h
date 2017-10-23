#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Rect.hpp>
#ifdef DEBUG
#include <SFML/Graphics/RectangleShape.hpp>
#endif // DEBUG
#include "VectorF.h"

class PhysicalObject : public sf::Drawable
{
public:
	enum CollidableType
	{
		ImmovableObject,// Not exactly a collision type, but it needs to be handled specially
		Circle,			// A circle will return three floats : X, Y, radius
		Square			// A square would return 4 floats: X, Y, width, height
	};

	PhysicalObject();
	PhysicalObject(bool applyGravity);
	virtual ~PhysicalObject();

	virtual void applyForce(const VectorF &force);
	virtual VectorF getForces() const;
	virtual void setPosition(const VectorF &pos);
	virtual void setPosition(const float &x, const float &y);
	virtual void move(const VectorF &offset);
	virtual void move(const float &offsetX, const float &offsetY);
	VectorF getPosition() const;

	void setMass(const float &newMass);
	float getMass() const;
	float getInvertedMass() const;

	virtual void setVelocity(const VectorF &v) = 0;
	virtual VectorF getVelocity() const = 0;

	void setApplyGravity(const bool &applyGravity);
	bool getApplyGravity() const;

	void setElasticity(const float &e);
	float getElasticity() const;

	virtual sf::FloatRect getBroadDetectionBox() = 0;
	virtual void getNarrowDetectionData(float* outValues) = 0;
	virtual void onCollision(VectorF penetration) = 0;

	CollidableType getCollidableType() { return collidableType; }

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const = 0;
	virtual void update(const sf::Time &deltaTime) = 0;
	virtual void lateUpdate(const sf::Time &deltaTime) = 0;

protected:
	VectorF position;	// The objects global coordinates for the center of mass
	VectorF offset;		// Used as a local center of mass / origin sort of thing
	VectorF forces;		// The acting forces on an object. Should be reset after each frame
	float mass;			// Mass is just weight * gravity, where gravity is constant in this case
	float invertedMass;
	bool applyGravity;	// If the object should be affected by a gravitational pull downwards on the screen
	float elasticity;
	bool collided;
	CollidableType collidableType;

#ifdef DEBUG
	sf::RectangleShape debugRect;
#endif // DEBUG

};