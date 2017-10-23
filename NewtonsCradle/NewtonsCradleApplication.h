#pragma once
#include "EulerBall.h"
#include "StringConstraint.h"
#include "ImmovableObject.h"
#include "PhysicalObjectManager.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <vector>

class NewtonsCradleApplication
{
public:
	NewtonsCradleApplication();
	~NewtonsCradleApplication();

	void run();

private:
	std::string updateString();

	static const size_t NR_BALLS = 5;
	sf::RenderWindow renderWin;
	PhysicalObjectManager physObjMan;
	EulerBall* ballTest[NR_BALLS];
	ImmovableObject* immovableObj[NR_BALLS];
	StringConstraint* constraintTest[NR_BALLS];
	sf::VertexArray frameThing;
	bool moveBall;

#ifdef DEBUG
	// Display helpful data
	sf::Text ballData;
	sf::Font font;
#endif
};