#pragma once
#include "HUD.h"
#include "Collects.h"
#include "Player.h"
#include "Level_Finished.h"
#include "TimerStart.h"
#include "Shockwave.h"
#include "Oilflake.h"
#include "Rocket.h"
#include "Bumper.h"
#include "Invicibility.h"
#include "BoostEffect.h"
#include "PlayerSelector.h"
#include "Level_Finished.h"
#include "Map.h"

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
	class Level_Finished* scoreScreen;

	//Missile* missile;
	//Collects* collects;
	int niveau;
	sf::Sprite spFirstOrSecond[2];
	sf::Music musicNiveau;
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
	sf::Sound Valider;
	sf::Sound Alteration;
	sf::Sound m_Shockwave;
	sf::Sound m_levitation;
	sf::Sound m_magnet;
	sf::Sound m_bumper;
	sf::Sound voiture;
	sf::Sound m_oil;;
	sf::Clock m_clocks;
	std::vector<Collects*> Collectibles;
	std::vector<Fx*> FXs;

	bool isPlayerAnimStart = true;
public:
	Jeu();
	Jeu(std::string _LevelName, int skinSelectedJ1, int skinSelectedJ2);
	~Jeu();
	virtual void Update();
	virtual void Display();
	virtual void EventManager(sf::Event p_pollingEvent);

	void CollectiblesManager();

	float GetElapsed();
};