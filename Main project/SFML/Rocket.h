#pragma once
#include "Collects.h"
#include "Smoke.h"

class Rocket :
	public Collects
{
public:
	Rocket(int _ID, int _Dir, sf::Vector2f _Pos);
	~Rocket();
	virtual void Update(Player* _Player1, Player* _Player2, Map* _Map, float _Elapsed, Caméra* _Cam);
	virtual void Display(sf::RenderWindow* _Window);
	virtual bool IsAlive();
	virtual void AddFxs(std::vector<Fx*> &_List);

private:
	bool Alive = true;

	int ID = 0, Direction = 0;

	sf::Clock SmokeAppear;

	sf::Sprite spRocket;

	std::vector<Smoke*> SmokeList;
};

