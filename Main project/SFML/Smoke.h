#pragma once
#include "Fx.h"

class Smoke : public Fx
{
public :
	Smoke(sf::Vector2f _Pos, float _Angle);
	~Smoke();
	virtual void Update(float _Elapsed);
	virtual void Display(sf::RenderWindow* _Window);
	virtual bool IsAlive();

private:
	bool Alive = true;

	sf::Sprite spSmoke;
	
	sf::Color SmokeAlpha;
};

