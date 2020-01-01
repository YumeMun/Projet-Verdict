#pragma once
#include "Scene.h"
#include "Transition.h"

class PlayerSelector : public Scene
{
public:
	PlayerSelector();
	PlayerSelector(std::string _LevelName);
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
	class Transition* transition;
	bool isGameStart = false;

	sf::Sprite spBackground;

	std::string LevelName;
};