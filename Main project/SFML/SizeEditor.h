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

	sf::Sprite spInfosRect;
	sf::Text InfosText;

	sf::Sprite spButton;
	sf::Sprite spLevelIcon[3];
	sf::Sound sound;
	sf::Sound retour;
	sf::Text LevelNumero[3];

	int LevelSelected;
	sf::Clock SelectionTimer;

	sf::Sprite spBackground;
	sf::Sprite spFlèche;
};