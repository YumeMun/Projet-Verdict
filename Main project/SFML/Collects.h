#pragma once
#include "Scene.h"

class Collects
{
public :

	Collects();
	~Collects();
	virtual void Update(sf::Sprite _Player1, sf::Sprite _Player2, float _Elapsed) = 0;
	virtual void Display(sf::RenderWindow* _Window) = 0;
	virtual bool IsAlive() = 0;
};
