#pragma once
#include "Collects.h"
class Invicibility :
	public Collects
{
public:
	Invicibility(int _ID, sf::Vector2f _Pos);
	~Invicibility();
	virtual void Update(Player* _Player1, Player* _Player2, Map* _Map, float _Elapsed, Caméra* _Cam);
	virtual void Display(sf::RenderWindow* _Window);
	virtual bool IsAlive();
	virtual void AddFxs(std::vector<Fx*>& _List);

private:
	bool Alive = true;

	int AnimFrameIndex = 0, ID = 0;

	sf::Clock AnimTime;

	sf::Sprite spShield;
};