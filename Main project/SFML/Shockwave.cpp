#include "Shockwave.h"

Shockwave::Shockwave(int _ID, sf::Vector2f _Pos)
{
	ID = _ID;

	spShockwave.setRadius(200);
	spShockwave.setFillColor(sf::Color(0, 0, 200, 200));
	spShockwave.setOrigin(spShockwave.getGlobalBounds().width / 2, spShockwave.getGlobalBounds().height / 2);
	spShockwave.setPosition(_Pos);
}

Shockwave::~Shockwave()
{
}

void Shockwave::Update(Player* _Player1, Player* _Player2, float _Elapsed)
{
	if(ID == 1)
	spShockwave.setPosition(_Player1->GetPos());
	else if (ID == 2)
		spShockwave.setPosition(_Player2->GetPos());

	if (LifeTime.getElapsedTime().asSeconds() >= 0.5)
		Alive = false;
}

void Shockwave::Display(sf::RenderWindow* _Window)
{
	_Window->draw(spShockwave);
}

bool Shockwave::IsAlive()
{
	return Alive;
}
