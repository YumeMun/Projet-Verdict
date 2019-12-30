#pragma once
#include "Collects.h"

class Shockwave :
	public Collects
{
public:
	Shockwave(int _ID, sf::Vector2f _Pos);
	~Shockwave();
	virtual void Update(Player* _Player1, Player* _Player2, float _Elapsed);
	virtual void Display(sf::RenderWindow* _Window);
	virtual bool IsAlive();

private :
	bool Alive = true;

	int ID = 0;

	sf::Clock LifeTime;

	sf::CircleShape spShockwave;
};

