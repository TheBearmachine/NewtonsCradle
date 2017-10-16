#pragma once
#include <vector>
#include <stack>
#include "PhysicalObject.h"
#include "Constraint.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>

class PhysicalObjectManager
{
public:
	PhysicalObjectManager();
	~PhysicalObjectManager();

	void addObject(PhysicalObject *object);
	void addConstraint(Constraint *constraint);

	void applyContinuousForces(const sf::Time &deltaTime);
	void update(const sf::Time &deltaTime);
	void lateUpdate(const sf::Time &deltaTime);
	void resolveConstraints(const sf::Time &deltaTime);
	void checkForCollisions();
	void draw(sf::RenderWindow &window);

private:
	typedef std::vector<PhysicalObject*> PhysObjVector;
	typedef std::vector<Constraint*> ConstraintVector;
	typedef std::stack<std::pair<PhysicalObject*, PhysicalObject*>> PhysObjPairStack;

	PhysObjPairStack broadDetectionPhase();
	void narrowDetectionPhase(PhysObjPairStack &physObjPairStack);

	PhysObjVector physObjects;
	ConstraintVector constraints;
};