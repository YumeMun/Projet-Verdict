#pragma once
#include "Collects.h"

class Oilflake :
	public Collects
{
public:
	Oilflake(int _ID, sf::Vector2f _Pos);
	~Oilflake();
	virtual void Update(Player* _Player1, Player* _Player2, Map* _Map, float _Elapsed, Caméra* _Cam);
	virtual void Display(sf::RenderWindow* _Window);
	virtual bool IsAlive();
	virtual void AddFxs(std::vector<Fx*> &_List);

private:
	bool Alive = true, Grounded = false;

	int ID = 0, AnimFrameIndex = 0;
	sf::Sound Alteration;
	sf::Clock AnimTime;

	sf::Vector2f Oil_Movement;

	sf::Sprite spOil;
};

