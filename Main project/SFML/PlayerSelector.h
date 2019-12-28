#pragma once
#include "Scene.h"

class PlayerSelector : public Scene
{
public:
	PlayerSelector();
	~PlayerSelector();
	void Setup();
	virtual void Update();
	virtual void Display();
	virtual void EventManager(sf::Event p_pollingEvent);

private:
	sf::RectangleShape rectPlay;
	sf::RectangleShape player;
	std::vector<PlayerSelector*> listSelector;

	bool isSetup = false;
	bool isSelectSkin = false;
	bool isPlayerReady = false;
	bool isSkinValidate = false;
	int SkinSelector = 1;

	sf::Clock SelectionTimer;
};