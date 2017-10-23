#include "NewtonsCradleApplication.h"
#include "EulerBall.h"
#include <SFML/Window/Event.hpp>

static const char* APP_TITLE = "Newton's Cradle";
static const float BALL_RADIUS = 30.0f;

static const char* FONT = "../sui_generis_rg.ttf";

NewtonsCradleApplication::NewtonsCradleApplication() :
	moveBall(false)
{
#ifdef DEBUG
	bool success =
		font.loadFromFile(FONT);
	ballData.setFont(font);
	ballData.setPosition(5, 5);
	ballData.setFillColor(sf::Color::Green);
	ballData.setCharacterSize(20);
#endif

	// Initialize window
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	renderWin.create(sf::VideoMode(640, 480), APP_TITLE, 7U, settings);

	// Some help variables
	float stringLength = 150.0f;
	float yPosAnchor = 100.0f;
	float yPosBall = yPosAnchor + stringLength;
	float xPosFirst = 200.0f;
	float xPosLast = xPosFirst + BALL_RADIUS * 2.0 * (NR_BALLS - 1);
	float ballMass = 1.0f;

	// Frame setup
	frameThing.setPrimitiveType(sf::PrimitiveType::TrianglesStrip);
	frameThing.resize(8);
	for (size_t i = 0; i < 8; i++)
	{
		frameThing[i].color = sf::Color(90, 90, 90);
	}
	float xOff1 = 60.0f, xOff2 = 50.0f;
	frameThing[0].position = VectorF(xPosFirst - xOff1, yPosBall + 50.0f).toSfVec();
	frameThing[1].position = VectorF(xPosFirst - xOff2 + 15.0f, yPosBall + 50.0f).toSfVec();
	frameThing[2].position = VectorF(xPosFirst - xOff1, yPosAnchor - 5.0f).toSfVec();
	frameThing[3].position = VectorF(xPosFirst - xOff2, yPosAnchor + 5.0f).toSfVec();
	frameThing[4].position = VectorF(xPosLast + xOff1, yPosAnchor - 5.0f).toSfVec();
	frameThing[5].position = VectorF(xPosLast + xOff2, yPosAnchor + 5.0f).toSfVec();
	frameThing[6].position = VectorF(xPosLast + xOff1, yPosBall + 50.0f).toSfVec();
	frameThing[7].position = VectorF(xPosLast + xOff2 - 15.0f, yPosBall + 50.0f).toSfVec();

	/*										*/
	/* Gravity can be changed in Constants	*/
	/*										*/
	for (size_t i = 0; i < NR_BALLS; i++)
	{
		float xPos = xPosFirst + i * BALL_RADIUS * 2.0f;

		ballTest[i] = new EulerBall();
		ballTest[i]->setMass(ballMass);
		ballTest[i]->setRadius(BALL_RADIUS);
		ballTest[i]->setPosition(xPos, yPosBall);
		ballTest[i]->setElasticity(1.0f);
		//ballTest[i]->setApplyGravity(false);
		physObjMan.addObject(ballTest[i]);

		immovableObj[i] = new ImmovableObject(VectorF(xPos, yPosAnchor));
		constraintTest[i] = new StringConstraint(stringLength);
		constraintTest[i]->setAttachments(immovableObj[i], ballTest[i]);
		physObjMan.addConstraint(constraintTest[i]);
	}

	ballTest[0]->setColor(sf::Color(175, 125, 125));
	//ballTest[0]->setPosition(immovableObj[0]->getPosition() + VectorF(-stringLength, 0.0f));
}

NewtonsCradleApplication::~NewtonsCradleApplication()
{

}

void NewtonsCradleApplication::run()
{
	sf::Clock clock;

	while (renderWin.isOpen())
	{
		sf::Event event;
		while (renderWin.pollEvent(event))
		{
			if (moveBall && event.type == event.MouseMoved)
			{
				VectorF mousePos = renderWin.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
				ballTest[0]->setPosition(mousePos);
				ballTest[0]->setVelocity(VectorF(0.0f, 0.0f));
			}

			if (event.type == sf::Event::Closed)
			{
				renderWin.close();
			}
			else if (event.type == event.MouseButtonPressed)
			{
				sf::Vector2f mousePos = renderWin.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
				if (ballTest[0]->getBroadDetectionBox().contains(mousePos))
				{
					moveBall = true;
					ballTest[0]->setVelocity(VectorF(0.0f, 0.0f));
					ballTest[0]->setPosition(mousePos);
					ballTest[0]->setApplyGravity(false);
				}
			}
			else if (event.type == event.MouseButtonReleased)
			{
				moveBall = false;
				ballTest[0]->setApplyGravity(true);
			}

		}
		sf::Time deltaTime = clock.restart();

		physObjMan.applyContinuousForces(deltaTime);
		physObjMan.resolveConstraints(deltaTime);
#ifdef DEBUG
		ballData.setString(updateString());
#endif
		physObjMan.update(deltaTime);
		physObjMan.checkForCollisions();
		physObjMan.lateUpdate(deltaTime);
		renderWin.clear();
		physObjMan.draw(renderWin);
		renderWin.draw(frameThing);
#ifdef DEBUG
		renderWin.draw(ballData);
#endif
		renderWin.display();
	}
}

std::string NewtonsCradleApplication::updateString()
{
	VectorF force = ballTest[0]->getForces();
	VectorF velocity = ballTest[0]->getVelocity();
	std::string returnString = /*"Acting forces - " + force.toString() + */"Current velocity - " + velocity.toString();
	return returnString;
}
