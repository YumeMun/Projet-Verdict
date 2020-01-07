#pragma once
#include "Scene.h"
#include "Player.h"
#include "ExploRocket.h"

class Collects
{
public :

	Collects();
	~Collects();
	virtual void Update(Player* _Player1, Player* _Player2, Map* _Map, float _Elapsed, Caméra* _Cam) = 0;
	virtual void Display(sf::RenderWindow* _Window) = 0;
	virtual bool IsAlive() = 0;
	virtual void AddFxs(std::vector<Fx*> &_List) = 0;
};
