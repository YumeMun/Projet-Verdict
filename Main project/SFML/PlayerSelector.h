#pragma once
#include "Scene.h"
#include "Transition.h"

#define NB_SKIN 2

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

	int GetSkinNumberJ1();
	int GetSkinNumberJ2();

private:
	sf::RectangleShape rectPlay;
	sf::RectangleShape player;
	sf::Sprite spPlayer;
	sf::Sprite spFader;
	sf::IntRect rectPlayer;
	sf::Vector2f originPlayer;
	std::vector<PlayerSelector*> listSelector;

	bool isSetup = false;
	bool isSelectSkin = false;
	bool isPlayerReady = false;
	bool isSkinValidate = false;
	bool isFadeDrawable = false;
	int SkinSelector = 1;

	sf::Clock SelectionTimer;
	sf::Clock timerSwitchSkin;
	class Transition* transition;
	bool isGameStart = false;

	sf::Sprite spBackground;

	std::string LevelName;
};