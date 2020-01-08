#pragma once
#include "Fx.h"

class BoostEffect :
	public Fx
{
public :
	BoostEffect(int _ID, sf::Vector2f _Pos);
	~BoostEffect();
	virtual void Update(float _Elapsed, Player* _Player1, Player* _Player2);
	virtual void Display(sf::RenderWindow* _Window);
	virtual bool IsAlive();

private :
	bool Alive = true;

	int ID = 0, AnimFrameIndex = 0;

	sf::Clock AnimTime;

	sf::Sprite spBoostFx;
};

