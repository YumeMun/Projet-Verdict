#pragma once
#include "Collects.h"

class Oilflake :
	public Collects
{
public:
	Oilflake(int _ID, sf::Vector2f _Pos);
	~Oilflake();
	virtual void Update(Player* _Player1, Player* _Player2, float _Elapsed);
	virtual void Display(sf::RenderWindow* _Window);
	virtual bool IsAlive();

private:
	bool Alive = true;

	int ID = 0, AnimFrameIndex = 0;

	sf::Clock AnimTime;

	sf::Sprite spOil;
};

