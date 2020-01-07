#pragma once
#include "Scene.h"

class Fx
{
public:

	Fx();
	~Fx();
	virtual void Update(float _Elapsed) = 0;
	virtual void Display(sf::RenderWindow* _Window) = 0;
	virtual bool IsAlive() = 0;
};

