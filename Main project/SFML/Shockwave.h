#pragma once
#include "Collects.h"

class Shockwave :
	public Collects
{
public:
	Shockwave(int _ID, sf::Vector2f _Pos);
	~Shockwave();
	virtual void Update(Player* _Player1, Player* _Player2, Map* _Map, float _Elapsed, Caméra* _Cam);
	virtual void Display(sf::RenderWindow* _Window);
	virtual bool IsAlive();

private :
	bool Alive = true;

	int ID = 0, AnimFrameIndex = 0;

	sf::Clock AnimTime;

	sf::Sprite spShockwave;
};

