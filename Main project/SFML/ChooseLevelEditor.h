#pragma once
#include "Scene.h"

class ChooseLevelEditor : public Scene
{
public:
	ChooseLevelEditor();
	~ChooseLevelEditor();

	virtual void Update();
	virtual void Display();
	virtual void EventManager(sf::Event p_pollingEvent);

private:
	int ChoiceSelected;
	sf::Clock SelectionTimer;

	sf::CircleShape ChoiceIcon[2];
	sf::Text ChoiceText[2];

	sf::Sprite spBackground;
};