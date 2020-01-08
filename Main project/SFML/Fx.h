#pragma once
#include "Scene.h"
#include "Player.h"

class Fx
{
public:

	Fx();
	~Fx();
	virtual void Update(float _Elapsed, Player* _Player1, Player* _Player2) = 0;
	virtual void Display(sf::RenderWindow* _Window) = 0;
	virtual bool IsAlive() = 0;
};

