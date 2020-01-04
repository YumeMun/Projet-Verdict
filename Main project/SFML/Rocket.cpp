#include "Rocket.h"
#include "ResourceManager.h"

Rocket::Rocket(int _ID, int _Dir, sf::Vector2f _Pos)
{
	ID = _ID;
	Direction = _Dir;

	spRocket.setTexture(*ResourceManager::Instance()->GetTexture("Rocket"));
	spRocket.setOrigin(spRocket.getGlobalBounds().width / 2, spRocket.getGlobalBounds().height / 2);
	spRocket.setPosition(_Pos);

	if (Direction == 0)
		spRocket.setScale(1, 1);
	else if (Direction == 1)
		spRocket.setScale(-1, 1);
}

Rocket::~Rocket()
{
}

void Rocket::Update(Player* _Player1, Player* _Player2, Map* _Map, float _Elapsed)
{
	if (Direction == 0)
	{
		spRocket.move((SPEED * 2) * _Elapsed, 0);

		if (SmokeAppear.getElapsedTime().asSeconds() >= 0.005)
		{
			Smoke* newSmoke = new Smoke(sf::Vector2f(spRocket.getPosition().x - 75, spRocket.getPosition().y));
			SmokeList.push_back(newSmoke);
			SmokeAppear.restart();
		}
	}
	else if (Direction == 1)
	{
		spRocket.move(-(SPEED * 2) * _Elapsed, 0);

		if (SmokeAppear.getElapsedTime().asSeconds() >= 0.005)
		{
			Smoke* newSmoke = new Smoke(sf::Vector2f(spRocket.getPosition().x + 100, spRocket.getPosition().y));
			SmokeList.push_back(newSmoke);
			SmokeAppear.restart();
		}
	}

	for (int i = 0; i < SmokeList.size(); i++)
	{
		SmokeList[i]->Update(_Elapsed);

		if (SmokeList[i]->SmokeAlpha.a <= 0)
			SmokeList.erase(SmokeList.begin() + i);
	}

	if (ID == 1)
	{
		if (_Player2->GetSprite().getGlobalBounds().contains(spRocket.getPosition()) && _Player2->Invincible == false)
		{
			Alive = false;
			_Player2->Player_Movement.x = 0;
		}
	}
	else if (ID == 2)
	{
		if (_Player1->GetSprite().getGlobalBounds().contains(spRocket.getPosition()) && _Player1->Invincible == false)
		{
			Alive = false;
			_Player1->Player_Movement.x = 0;
		}
	}

	if (_Map->GetTile(spRocket.getPosition().x, spRocket.getPosition().y) != 0)
		Alive = false;
}

void Rocket::Display(sf::RenderWindow* _Window)
{
	for (int i = 0; i < SmokeList.size(); i++)
	{
		SmokeList[i]->Display(_Window);
	}

	_Window->draw(spRocket);
}

bool Rocket::IsAlive()
{
	return Alive;
}
