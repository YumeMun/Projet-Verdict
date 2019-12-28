#pragma once
#include "GameManager.h"
#include "Scene.h"

#define TRANSITION_SPEED 10

class Transition
{
public:
	Transition();
	Transition(sf::Vector2f _posShape1, sf::Vector2f _posShape2);
	~Transition();

	void Setup();
	void SetupBack(sf::Vector2f _posShape1, sf::Vector2f _posShape2);

	void Update();
	void UpdateBack();

	void ResetTransition();
	void DrawTransition();

	bool GetIsTransitionDone();
	bool GetIsTransitionBackDone();

private:
	sf::RenderWindow* m_actualWindow;

	sf::Clock timerCooldownStand;
	sf::ConvexShape shape[2];
	sf::Vector2f posShape[2];

	bool isTransitionDone = false;
	bool isTransitionBackDone = false;
	bool isMovementEnd = false;
};

