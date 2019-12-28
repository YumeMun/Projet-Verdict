#pragma once
#include "HUD.h"
#include "Collects.h"
#include "Player.h"
#include "Level_Finished.h"

class Jeu :public Scene
{
private:
	float CurrentTime, LastFrameTime, ElapsedTime;

	Map* map;
	Cam�ra* cam�ra;
	HUD* hud;
	Player* Player1, * Player2;

	Missile* missile;
	Collects* collects;

	sf::Clock Clock;
	void MenuIG(int ID);
	bool MenuIG_Activated = false;
	sf::Sprite spMenuIG;
	sf::Text MenuIGText[6];
	int SelectionMenuIG = 1;
	int StateMenuIG = 0;
	int ID;

public:
	Jeu();
	~Jeu();
	virtual void Update();
	virtual void Display();
	virtual void EventManager(sf::Event p_pollingEvent);
};