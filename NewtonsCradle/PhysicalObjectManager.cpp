#include "PhysicalObjectManager.h"
#include "VectorRotation.h"
#include "Constants.h"

// Increased gravity to compensate for the scale

PhysicalObjectManager::PhysicalObjectManager() :
	physObjects()
{

}

PhysicalObjectManager::~PhysicalObjectManager()
{

}

void PhysicalObjectManager::addObject(PhysicalObject * object)
{
	physObjects.push_back(object);
}

void PhysicalObjectManager::addConstraint(Constraint * constraint)
{
	constraints.push_back(constraint);
}

void PhysicalObjectManager::applyContinuousForces(const sf::Time &deltaTime)
{
	// Gravity
	for (auto po : physObjects)
	{
		if (po->getApplyGravity())
			po->applyForce(VectorF(0.0f, po->getMass() * Constants::Gravity * deltaTime.asSeconds()));
	}
}

void PhysicalObjectManager::update(const sf::Time & deltaTime)
{
	for (auto po : physObjects)
	{
		po->update(deltaTime);
	}
	for (auto c : constraints)
	{
		c->update(deltaTime);
	}
}

void PhysicalObjectManager::lateUpdate(const sf::Time & deltaTime)
{
	for (auto po : physObjects)
	{
		po->lateUpdate(deltaTime);
	}
}

void PhysicalObjectManager::resolveConstraints(const sf::Time &deltaTime)
{
	for (auto c : constraints)
	{
		c->solveConstraint(deltaTime);
	}
}

void PhysicalObjectManager::checkForCollisions()
{
	// Do a two stage collision check using rectangles first and then circles
	// (Probably overkill as circles and rectangles are fairly similar in computation usage).
	PhysObjPairStack possibleCollisions = broadDetectionPhase();
	narrowDetectionPhase(possibleCollisions);
}

void PhysicalObjectManager::draw(sf::RenderWindow & window)
{
	for (auto c : constraints)
	{
		window.draw(*c);
	}
	for (auto po : physObjects)
	{
		window.draw(*po);
	}
}

PhysicalObjectManager::PhysObjPairStack PhysicalObjectManager::broadDetectionPhase()
{
	PhysObjPairStack possibleCollisions;

	// Iterate through every pair of objects (REALLY expensive (O(n^n)) and would need to be culled in larger applications)
	for (size_t i = 0; i < physObjects.size() - 1; i++)
	{
		for (size_t j = i + 1; j < physObjects.size(); j++)
		{
			if (physObjects[i]->getBroadDetectionBox().intersects(physObjects[j]->getBroadDetectionBox()))
			{
				possibleCollisions.push(std::make_pair(physObjects[i], physObjects[j])); // Pair up potential collisions
			}
		}
	}
	return possibleCollisions;
}

void PhysicalObjectManager::narrowDetectionPhase(PhysObjPairStack & physObjPairStack)
{
	while (!physObjPairStack.empty())
	{
		std::pair<PhysicalObject*, PhysicalObject*> pairToCheck = physObjPairStack.top();
		physObjPairStack.pop();
		if (pairToCheck.first->getCollidableType() == PhysicalObject::CollidableType::Circle
			&& pairToCheck.second->getCollidableType() == PhysicalObject::CollidableType::Circle) // Circle against circle detection
		{
			PhysicalObject *obj1 = pairToCheck.first, *obj2 = pairToCheck.second; // Just to shorten the syntaxes
			float col1[3], col2[3];
			obj1->getNarrowDetectionData(col1);
			obj2->getNarrowDetectionData(col2);
			float dxSq = powf(col1[0] - col2[0], 2.0f);
			float dySq = powf(col1[1] - col2[1], 2.0f);
			float radius = col1[2] + col2[2];
			float radiusSq = powf(radius, 2.0f);

			if (dxSq + dySq < radiusSq) // If true, there has been a collision
			{
				// Find the direct of the collision
				VectorF dir = VectorF::normalize(obj1->getPosition() - obj2->getPosition());
				float elasticity = (obj1->getElasticity() + obj2->getElasticity()) / 2.0f;

				VectorF vBefore1 = obj1->getVelocity();
				VectorF vBefore2 = obj2->getVelocity();
				float m1 = obj1->getMass(), m2 = obj2->getMass();
				float j = (-(1 + elasticity) * (vBefore1 - vBefore2).dotProduct(dir)) /
					((1 / m1) + (1 / m2));

				VectorF vAfter1 = vBefore1 + (dir * j) / m1;
				VectorF vAfter2 = vBefore2 - (dir * j) / m2;
				float penDist = radius - (obj1->getPosition() - obj2->getPosition()).magnitude();
				VectorF pen1 = (dir * penDist).project(vBefore1);
				VectorF pen2 = (dir * -penDist).project(vBefore2);

				obj1->setVelocity(vAfter1);
				obj2->setVelocity(vAfter2);

				// Do not move the colliding objects out of eachother here,
				// but at a later stage to prevent new potential collisions popping up
				obj1->onCollision(pen1);
				obj2->onCollision(pen2);
			}
		}
	}
}
