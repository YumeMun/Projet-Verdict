#include "Missile.h"

Missile::Missile()
{
}

Missile::Missile(int _Direction, sf::Vector2f _PlayerPos)
{
	type = "Missile";

	rectMissile.setSize(sf::Vector2f{ 50, 30 });
	rectMissile.setFillColor(sf::Color::Red);
	rectMissile.setPosition(_PlayerPos);

	Direction = _Direction;
}

Missile::~Missile()
{
}

void Missile::Update(float _ElapsedTime, Map* _Map)
{
	if (Direction == 0)
		rectMissile.move(1800 * _ElapsedTime, 0);

	else if (Direction == 1)
		rectMissile.move(-1800 * _ElapsedTime, 0);
}

sf::RectangleShape Missile::GetMissile()
{
	return rectMissile;
}