#include "Oilflake.h"
#include "ResourceManager.h"

Oilflake::Oilflake(int _ID, sf::Vector2f _Pos)
{
	ID = _ID;

	spOil.setTexture(*ResourceManager::Instance()->GetTexture("OilFlake"));

	spOil.setTextureRect(sf::IntRect(0, 0, 192, 64));

	spOil.setOrigin(spOil.getGlobalBounds().width / 2, spOil.getGlobalBounds().height);

	spOil.setPosition(_Pos);
}

Oilflake::~Oilflake()
{
}

void Oilflake::Update(Player* _Player1, Player* _Player2, Map* _Map, float _Elapsed, Caméra* _Cam)
{
	if (Grounded == false)
	{
		Oil_Movement.y += GRAVITY * GRAVITYFACTOR * _Elapsed;

		spOil.move(Oil_Movement * _Elapsed);

		if ((_Map->GetTile(spOil.getPosition().x, spOil.getPosition().y) >= 1 && _Map->GetTile(spOil.getPosition().x, spOil.getPosition().y) <= 6) || _Map->GetTile(spOil.getPosition().x, spOil.getPosition().y) == 11)
		{
			for (int i = 1; i < 7; i++)
			{
				if (_Map->GetTile(spOil.getPosition().x, spOil.getPosition().y) == i)
				{
					spOil.setPosition(sf::Vector2f(spOil.getPosition().x, _Map->GetNextTile(i, sf::Vector2f(spOil.getPosition().x, spOil.getPosition().y)).y));
				}
			}

			if (_Map->GetTile(spOil.getPosition().x, spOil.getPosition().y) == 11)
			{
				spOil.setPosition(sf::Vector2f(spOil.getPosition().x, _Map->GetNextTile(11, sf::Vector2f(spOil.getPosition().x, spOil.getPosition().y)).y));
			}

			Grounded = true;
		}
		else if (_Map->GetTile(spOil.getPosition().x, spOil.getPosition().y) == 7 || _Map->GetTile(spOil.getPosition().x, spOil.getPosition().y) == 12)
		{
			/*Alteration.setBuffer(*ResourceManager::Instance()->GetSoundBuffer("Alteration"));
			Alteration.setVolume(50);
			Alteration.play();
			_Player2->Oiled = true;*/

			if (_Map->GetTile(spOil.getPosition().x, spOil.getPosition().y) == 7)
			{
				spOil.setPosition(sf::Vector2f(spOil.getPosition().x + 10, _Map->GetNextTile(7, sf::Vector2f(spOil.getPosition().x, spOil.getPosition().y)).y + 10));
			}
			else if (_Map->GetTile(spOil.getPosition().x, spOil.getPosition().y) == 12)
			{
				spOil.setPosition(sf::Vector2f(spOil.getPosition().x + 10, _Map->GetNextTile(12, sf::Vector2f(spOil.getPosition().x, spOil.getPosition().y)).y + 10));
			}

			spOil.setRotation(315);
			Grounded = true;
		}
		else if (_Map->GetTile(spOil.getPosition().x, spOil.getPosition().y) == 8 || _Map->GetTile(spOil.getPosition().x, spOil.getPosition().y) == 13)
		{
			if (_Map->GetTile(spOil.getPosition().x, spOil.getPosition().y) == 8)
			{
				spOil.setPosition(sf::Vector2f(spOil.getPosition().x - 15, _Map->GetNextTile(8, sf::Vector2f(spOil.getPosition().x, spOil.getPosition().y)).y));
			}
			else if (_Map->GetTile(spOil.getPosition().x, spOil.getPosition().y) == 13)
			{
				spOil.setPosition(sf::Vector2f(spOil.getPosition().x - 15, _Map->GetNextTile(13, sf::Vector2f(spOil.getPosition().x, spOil.getPosition().y)).y));
			}

			spOil.setRotation(45);
			Grounded = true;
		}
	}
	else if (Grounded == true)
	{
		if (ID == 1)
		{
			if (_Player2->GetPos().x >= spOil.getGlobalBounds().left &&
				_Player2->GetPos().x <= spOil.getGlobalBounds().left + spOil.getGlobalBounds().width &&
				_Player2->GetPos().y >= spOil.getGlobalBounds().top - 100 &&
				_Player2->GetPos().y <= spOil.getGlobalBounds().top + spOil.getGlobalBounds().height + 100 && _Player2->Invincible == false)
			{
				if (_Player2->Oiled == false)
				{
					Alteration.setBuffer(*ResourceManager::Instance()->GetSoundBuffer("Alteration"));
					Alteration.setVolume(50);
					Alteration.play();
				}

				_Player2->Oiled = true;
			}
			else
				_Player2->Oiled = false;
		}
		else if (ID == 2)
		{
			if (_Player1->GetPos().x >= spOil.getGlobalBounds().left &&
				_Player1->GetPos().x <= spOil.getGlobalBounds().left + spOil.getGlobalBounds().width &&
				_Player1->GetPos().y >= spOil.getGlobalBounds().top - 100 &&
				_Player1->GetPos().y <= spOil.getGlobalBounds().top + spOil.getGlobalBounds().height + 100 && _Player1->Invincible == false)
			{
				if (_Player1->Oiled == false)
				{
					Alteration.setBuffer(*ResourceManager::Instance()->GetSoundBuffer("Alteration"));
					Alteration.setVolume(50);
					Alteration.play();
				}

				_Player1->Oiled = true;
			}
			else
				_Player1->Oiled = false;
		}

		if (AnimFrameIndex < 24)
		{
			if (AnimTime.getElapsedTime().asSeconds() >= 0.05)
			{
				AnimFrameIndex++;
				AnimTime.restart();
			}
		}
	}

	spOil.setTextureRect(sf::IntRect(192 * AnimFrameIndex, 0, 192, 64));

	if (spOil.getPosition().x < _Cam->GetCameraCenter().x - _Cam->GetSizeCamera().x / 2 ||
		spOil.getPosition().y > _Cam->GetCameraCenter().y + _Cam->GetSizeCamera().y / 2)
	{
		Alive = false;
	}
}

void Oilflake::Display(sf::RenderWindow* _Window)
{
	_Window->draw(spOil);
}

bool Oilflake::IsAlive()
{
	return Alive;
}

void Oilflake::AddFxs(std::vector<Fx*> &_List)
{
}
