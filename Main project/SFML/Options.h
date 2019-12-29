#pragma once
#include "Scene.h"

class Options :
	public Scene
{
public:
	Options();
	~Options();

	virtual void Update();
	virtual void Display();
	virtual void EventManager(sf::Event p_pollingEvent);

private:
	sf::Sprite spBackground;
	sf::Sprite spFlèche;

	sf::Sprite spVolume[2];
	sf::Sprite spButton[2];
	sf::Text OptionsText[2];

	sf::IntRect VolumeRect[2];

	int Selection = 1;

	sf::Clock SelectionTimer;
};