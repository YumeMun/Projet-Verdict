#pragma once
#include "Scene.h"

class SizeEditor :public Scene
{
private:

public:
	SizeEditor();
	~SizeEditor();
	virtual void Update();
	virtual void Display();
	virtual void EventManager(sf::Event p_pollingEvent);

private:
	sf::Text EnterSizeText;

	sf::RectangleShape InfosRect;
	sf::Text InfosText;

	sf::RectangleShape LevelIcon[3];

	sf::Text LevelNumero[3];

	int LevelSelected;
	sf::Clock SelectionTimer;

	sf::Sprite spBackground;
};