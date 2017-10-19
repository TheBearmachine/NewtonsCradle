#include "NewtonsCradleApplication.h"
#include "EulerBall.h"
#include <SFML/Window/Event.hpp>

static const char* APP_TITLE = "";
static const float BALL_RADIUS = 30.0f;
static const float BALL_MASS = 100.0f;

NewtonsCradleApplication::NewtonsCradleApplication()
{
	// Initialize everything
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	renderWin.create(sf::VideoMode(640, 480), APP_TITLE, 7U, settings);

	for (size_t i = 0; i < NR_BALLS; i++)
	{
		ballTest[i] = new EulerBall();
		ballTest[i]->setMass(BALL_MASS);
		ballTest[i]->setRadius(BALL_RADIUS);
		ballTest[i]->setPosition(100 + i * BALL_RADIUS * 2, 200);
		ballTest[i]->setElasticity(.5f);
		ballTest[i]->setApplyGravity(false);
		physObjMan.addObject(ballTest[i]);

		immovableObj[i] = new ImmovableObject(sf::Vector2f(100 + i * BALL_RADIUS * 2, 100));
		constraintTest[i] = new StringConstraint(100.0f);
		constraintTest[i]->setAttachments(immovableObj[i], ballTest[i]);
		physObjMan.addConstraint(constraintTest[i]);
	}

	ballTest[0]->setPosition(50, 150);
	//ballTest[0]->applyForce(VectorF(1500.0f, 0.0f));
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
			if (event.type == sf::Event::Closed)
			{
				renderWin.close();
			}
			/*else if (event.type == event.KeyPressed && event.key.code == sf::Keyboard::Add)
			{
				testRadius += 1.0f;
				testRadius = std::fminf(testRadius, 40.0f);
				ballTest->setRadius(testRadius);
			}
			else if (event.type == event.KeyPressed && event.key.code == sf::Keyboard::Subtract)
			{
				testRadius -= 1.0f;
				testRadius = std::fmaxf(testRadius, 5.0f);
				ballTest->setRadius(testRadius);
			}*/
		}
		sf::Time deltaTime = clock.restart();

		//////////////////////////////////
		/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			ballTest2->move(-50.0f * deltaTime.asSeconds(), 0.0f);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			ballTest2->move(50.0f * deltaTime.asSeconds(), 0.0f);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			ballTest2->move(0.0f, -50.0f * deltaTime.asSeconds());
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			ballTest2->move(0.0f, 50.0f * deltaTime.asSeconds());*/
			//////////////////////////////////

		physObjMan.applyContinuousForces(deltaTime);
		physObjMan.update(deltaTime);
		physObjMan.resolveConstraints(deltaTime);
		physObjMan.checkForCollisions();
		physObjMan.lateUpdate(deltaTime);
		renderWin.clear();
		physObjMan.draw(renderWin);
		renderWin.display();
	}
}
