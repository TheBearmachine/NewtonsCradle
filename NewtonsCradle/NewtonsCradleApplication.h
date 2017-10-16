#pragma once
#include "EulerBall.h"
#include "StringConstraint.h"
#include "ImmovableObject.h"
#include "PhysicalObjectManager.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>

class NewtonsCradleApplication
{
public:
	NewtonsCradleApplication();
	~NewtonsCradleApplication();

	void run();

private:
	static const size_t NR_BALLS = 1;
	sf::RenderWindow renderWin;
	PhysicalObjectManager physObjMan;
	EulerBall* ballTest[NR_BALLS];
	ImmovableObject* immovableObj[NR_BALLS];
	StringConstraint* constraintTest[NR_BALLS];
};