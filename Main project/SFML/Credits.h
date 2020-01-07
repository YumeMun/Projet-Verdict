#pragma once
#include "Scene.h"

class Credits :
	public Scene
{
public:
	Credits();
	~Credits();

	virtual void Update();
	virtual void Display();
	virtual void EventManager(sf::Event p_pollingEvent);

private:
	sf::Sprite spBackground;
	sf::Sound Retour;
};