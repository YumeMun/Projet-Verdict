#pragma once
#include "Fx.h"

class ExploRocket :
	public Fx
{
public :
	ExploRocket(sf::Vector2f _Pos);
	~ExploRocket();
	virtual void Update(float _Elapsed, Player* _Player1, Player* _Player2);
	virtual void Display(sf::RenderWindow* _Window);
	virtual bool IsAlive();

private :
	bool Alive = true;

	int AnimFrameIndex = 0;

	sf::Sprite spExplo;

	sf::Clock AnimTime;
};

