#pragma once
#include "Scene.h"

class Commandes :
	public Scene
{
public:
	Commandes();
	~Commandes();

	virtual void Update();
	virtual void Display();
	virtual void EventManager(sf::Event p_pollingEvent);

private:
	sf::Text ControlsText;

	sf::Sprite spBackground;
	sf::Sprite spCommandes;

	sf::Sprite spTouches[2];
	bool KeyPress = false;
	int Selection = 1;
};