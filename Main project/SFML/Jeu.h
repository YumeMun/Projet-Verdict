#pragma once
#include "HUD.h"
#include "Collects.h"
#include "Player.h"
#include "Level_Finished.h"
#include "TimerStart.h"
#include "Shockwave.h"
#include "Oilflake.h"
#include "Rocket.h"
#include "PlayerSelector.h"

class Jeu :public Scene
{
private:
	float CurrentTime, LastFrameTime, ElapsedTime;

	std::string LevelName;

	Map* map;
	Caméra* caméra;
	HUD* hud;
	Player* Player1, * Player2;
	class Transition* transition;
	class TimerStart* timerStart;

	//Missile* missile;
	//Collects* collects;

	sf::Sprite spFirstOrSecond[2];

	sf::Clock Clock;
	void MenuIG(int ID);
	bool MenuIG_Activated = false;
	sf::Sprite spMenuIG;
	sf::Text MenuIGText[6];
	int SelectionMenuIG = 1;
	int StateMenuIG = 0;
	int ID;
	int skinJ1;
	int skinJ2;
	sf::Sound sound;
	sf::Sound Retour;
	std::vector<Collects*> Collectibles;

	bool isPlayerAnimStart = true;
public:
	Jeu();
	Jeu(std::string _LevelName, int skinSelectedJ1, int skinSelectedJ2);
	~Jeu();
	virtual void Update();
	virtual void Display();
	virtual void EventManager(sf::Event p_pollingEvent);

	void CollectiblesManager();
};