#pragma once
#include "Scene.h"
#include "Missile.h"

#define NB_COLLECTS 2

class Collects
{
public :

	Collects();
	~Collects();

	void SetupCollects();
	void Update(Missile* _missile);
	void Display();

	bool GetPlayerIsCollideCollects();

	void Die();
	bool IsAlive();

	bool isMissileCreate = false;
	int isCreate = 0;
private :
	bool Alive = true;

	bool isSetup = false;
	bool isCollidePlayer;
	sf::RectangleShape CollectRect;
	sf::String type;
	std::vector<Collects*> listCollect;

	sf::RectangleShape samplePlayer;
	sf::Vector2f posSamplePlayer;

	sf::RenderWindow* m_actualWindow;
};
