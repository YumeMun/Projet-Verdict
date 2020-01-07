#pragma once
#include "Scene.h"
#include "Transition.h"

#define NB_SKIN 4

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
	//sf::RectangleShape rectPlay;
	sf::Sprite spReady;
	sf::Vector2f buttonOrigin;
	sf::Vector2f textOrigin;
	sf::Text textSkinSelect[3];
	sf::String strSkinSelect[3];
	sf::Clock timerAlreadyUse;
	bool isAlreadyUseDrawable = false;

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
	sf::Sound Retour;
	sf::Sound Valider;
	sf::Sound sound;
	sf::Sprite spBackground;

	std::string LevelName;
};