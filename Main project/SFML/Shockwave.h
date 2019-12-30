#pragma once
#include "Collects.h"

class Shockwave :
	public Collects
{
public:
	Shockwave(int _ID, sf::Vector2f _Pos);
	~Shockwave();
	virtual void Update(sf::Sprite _Player1, sf::Sprite _Player2, float _Elapsed);
	virtual void Display(sf::RenderWindow* _Window);
	virtual bool IsAlive();

private :
	bool Alive = true;

	sf::Clock LifeTime;
};

