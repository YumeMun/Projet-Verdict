#pragma once
#include "Collects.h"

class Bumper : public Collects
{
public :
	Bumper(int _ID, int _Dir, sf::Vector2f _Pos);
	~Bumper();
	virtual void Update(Player* _Player1, Player* _Player2, Map* _Map, float _Elapsed, Caméra* _Cam);
	virtual void Display(sf::RenderWindow* _Window);
	virtual bool IsAlive();
	virtual void AddFxs(std::vector<Fx*> &_List);

private:
	bool Alive = true, Grounded = false;

	int ID = 0, Dir = 1, AnimFrameIndex = 0;

	sf::Clock AnimTime;

	sf::Vector2f Bumper_Movement;

	sf::Sprite spBumper;
};

