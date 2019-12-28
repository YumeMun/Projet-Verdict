#pragma once
//#include "Collects.h"
#include "Scene.h"
#include "Map.h"

class Missile //: public Collects
{
public:
	Missile();
	Missile(int _Direction, sf::Vector2f _PlayerPos);
	~Missile();

	void Update(float _ElapsedTime, Map* _Map);

	sf::RectangleShape GetMissile();
private:
	sf::RenderWindow* m_actualWindow;

	sf::RectangleShape rectMissile;
	int Direction;

	sf::String type;
};

