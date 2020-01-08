#include "Bumper.h"
#include "ResourceManager.h"

Bumper::Bumper(int _ID, int _Dir, sf::Vector2f _Pos)
{
	ID = _ID;
	Dir = _Dir;

	spBumper.setTexture(*ResourceManager::Instance()->GetTexture("Bumper"));
	spBumper.setTextureRect(sf::IntRect(0, 0, 64, 64));
	spBumper.setOrigin(spBumper.getGlobalBounds().width / 2, spBumper.getGlobalBounds().height);
	spBumper.setPosition(_Pos);

	if (_Dir == 0)
	{
		Bumper_Movement.x = SPEED * 2;
		Bumper_Movement.y = -SPEED;
	}
	else if (_Dir == 1)
	{
		Bumper_Movement.x = -SPEED;
		Bumper_Movement.y = -SPEED;
	}
}

Bumper::~Bumper()
{
}

void Bumper::Update(Player* _Player1, Player* _Player2, Map* _Map, float _Elapsed, Caméra* _Cam)
{
	if (Grounded == false)
	{
		Bumper_Movement.y += GRAVITY * GRAVITYFACTOR * _Elapsed;

		spBumper.move(Bumper_Movement * _Elapsed);

		for (int i = 1; i < 7; i++)
		{
			if (_Map->GetTile(spBumper.getPosition().x, spBumper.getPosition().y) == i)
			{
				spBumper.setPosition(spBumper.getPosition().x, _Map->GetNextTile(i, sf::Vector2f(spBumper.getPosition())).y);
				Grounded = true;
			}
		}

		if (_Map->GetTile(spBumper.getPosition().x, spBumper.getPosition().y) == 11)
		{
			spBumper.setPosition(spBumper.getPosition().x, _Map->GetNextTile(11, sf::Vector2f(spBumper.getPosition())).y);
			Grounded = true;
		}
		else if (_Map->GetTile(spBumper.getPosition().x, spBumper.getPosition().y) == 7 || _Map->GetTile(spBumper.getPosition().x, spBumper.getPosition().y) == 12)
		{
			Bumper_Movement.x = -SPEED;
		}
		else if (_Map->GetTile(spBumper.getPosition().x, spBumper.getPosition().y) == 8 || _Map->GetTile(spBumper.getPosition().x, spBumper.getPosition().y) == 13)
		{
			Bumper_Movement.x = SPEED;
		}
	}
	else if (Grounded == true)
	{
		if (spBumper.getGlobalBounds().contains(_Player1->GetPos()))
		{
			m_bumper.setBuffer(*ResourceManager::Instance()->GetSoundBuffer("BumperEffect"));
			m_bumper.play();
			_Player1->Player_Movement.y = -SPEED * 3;
			Alive = false;
		}
		else if (spBumper.getGlobalBounds().contains(_Player2->GetPos()))
		{
			m_bumper.setBuffer(*ResourceManager::Instance()->GetSoundBuffer("BumperEffect"));
			m_bumper.play();
			_Player2->Player_Movement.y = -SPEED * 3;
			Alive = false;
		}

		if (AnimTime.getElapsedTime().asSeconds() >= 0.07)
		{
			if (AnimFrameIndex < 19)
				AnimFrameIndex++;
			else
				AnimFrameIndex = 0;

			AnimTime.restart();
		}

		spBumper.setTextureRect(sf::IntRect(64 * AnimFrameIndex, 0, 64, 64));
	}

	if (spBumper.getPosition().x < _Cam->GetCameraCenter().x - _Cam->GetSizeCamera().x / 2 ||
		spBumper.getPosition().y > _Cam->GetCameraCenter().y + _Cam->GetSizeCamera().y / 2)
	{
		Alive = false;
	}
}

void Bumper::Display(sf::RenderWindow* _Window)
{
	_Window->draw(spBumper);
}

bool Bumper::IsAlive()
{
	return Alive;
}

void Bumper::AddFxs(std::vector<Fx*> &_List)
{
}
