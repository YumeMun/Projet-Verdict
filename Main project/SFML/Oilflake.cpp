#include "Oilflake.h"
#include "ResourceManager.h"

Oilflake::Oilflake(int _ID, sf::Vector2f _Pos)
{
	ID = _ID;

	spOil.setTexture(*ResourceManager::Instance()->GetTexture("OilFlake"));

	spOil.setTextureRect(sf::IntRect(0, 0, 200, 40));

	spOil.setPosition(_Pos);
}

Oilflake::~Oilflake()
{
}

void Oilflake::Update(Player* _Player1, Player* _Player2, Map* _Map, float _Elapsed)
{
	if (ID == 1)
	{
		if (_Player2->GetPos().x >= spOil.getGlobalBounds().left &&
			_Player2->GetPos().x <= spOil.getGlobalBounds().left + spOil.getGlobalBounds().width &&
			_Player2->GetPos().y >= spOil.getGlobalBounds().top - 200 &&
			_Player2->GetPos().y <= spOil.getGlobalBounds().top + spOil.getGlobalBounds().height)
		{
			_Player2->Oiled = true;
		}
		else
			_Player2->Oiled = false;
	}
	else if (ID == 2)
	{
		if (_Player1->GetPos().x >= spOil.getGlobalBounds().left &&
			_Player1->GetPos().x <= spOil.getGlobalBounds().left + spOil.getGlobalBounds().width &&
			_Player1->GetPos().y >= spOil.getGlobalBounds().top - 200 &&
			_Player1->GetPos().y <= spOil.getGlobalBounds().top + spOil.getGlobalBounds().height)
		{
			_Player1->Oiled = true;
		}
		else 
			_Player1->Oiled = false;
	}

	if (AnimFrameIndex < 7)
	{
		if (AnimTime.getElapsedTime().asSeconds() >= 0.05)
		{
			AnimFrameIndex++;
			AnimTime.restart();
		}
	}

	spOil.setTextureRect(sf::IntRect(200 * AnimFrameIndex, 0, 200, 40));
}

void Oilflake::Display(sf::RenderWindow* _Window)
{
	_Window->draw(spOil);
}

bool Oilflake::IsAlive()
{
	return Alive;
}
