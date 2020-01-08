#include "Rocket.h"
#include "ResourceManager.h"

Rocket::Rocket(int _ID, int _Dir, sf::Vector2f _Pos)
{
	ID = _ID;
	Direction = _Dir;

	spRocket.setTexture(*ResourceManager::Instance()->GetTexture("Rocket"));
	spRocket.setOrigin(spRocket.getGlobalBounds().width / 2, spRocket.getGlobalBounds().height / 2);
	spRocket.setPosition(_Pos);

	m_missile.setBuffer(*ResourceManager::Instance()->GetSoundBuffer("Missile Lancer"));
	m_missile.play();

	if (Direction == 0)
		spRocket.setScale(1, 1);
	else if (Direction == 1)
		spRocket.setScale(-1, 1);
}

Rocket::~Rocket()
{
}

void Rocket::Update(Player* _Player1, Player* _Player2, Map* _Map, float _Elapsed, Caméra* _Cam)
{
	if (Direction == 0)
	{
		spRocket.move((SPEED * 2) * _Elapsed, 0);
	}
	else if (Direction == 1)
	{
		spRocket.move(-(SPEED * 2) * _Elapsed, 0);
	}

	if (ID == 1)
	{
		if (_Player2->GetSprite().getGlobalBounds().contains(spRocket.getPosition()) && _Player2->Invincible == false)
		{
			m_missile.stop();
			m_rocket.setBuffer(*ResourceManager::Instance()->GetSoundBuffer("Impact Missile"));
			m_rocket.play();

			m_engineoff.setBuffer(*ResourceManager::Instance()->GetSoundBuffer("EngineOff"));
			m_engineoff.play();

			m_engineon.setBuffer(*ResourceManager::Instance()->GetSoundBuffer("EngineOn"));
			m_engineon.play();

			Alive = false;
			_Player2->Player_Movement.x = 0;
		}
	}
	else if (ID == 2)
	{
		if (_Player1->GetSprite().getGlobalBounds().contains(spRocket.getPosition()) && _Player1->Invincible == false)
		{
			m_missile.stop();
			m_rocket.setBuffer(*ResourceManager::Instance()->GetSoundBuffer("Impact Missile"));
			m_rocket.play();

			m_engineoff.setBuffer(*ResourceManager::Instance()->GetSoundBuffer("EngineOff"));
			m_engineoff.play();

			m_engineon.setBuffer(*ResourceManager::Instance()->GetSoundBuffer("EngineOn"));
			m_engineon.play();

			Alive = false;
			_Player1->Player_Movement.x = 0;
		}
	}

	if (_Map->GetTile(spRocket.getPosition().x, spRocket.getPosition().y) != 0)
	{
		m_missile.stop();
		m_rocket.setBuffer(*ResourceManager::Instance()->GetSoundBuffer("Impact Missile"));
		m_rocket.play();

		Alive = false;
	}
}

void Rocket::Display(sf::RenderWindow* _Window)
{
	_Window->draw(spRocket);
}

bool Rocket::IsAlive()
{
	return Alive;
}

void Rocket::AddFxs(std::vector<Fx*> &_List)
{
	if (Direction == 0)
	{
		if (SmokeAppear.getElapsedTime().asSeconds() >= 0.02)
		{
			Smoke* newSmoke = new Smoke(sf::Vector2f(spRocket.getPosition().x - 75, spRocket.getPosition().y), rand() % 350 + 1);
			_List.push_back(newSmoke);
			SmokeAppear.restart();
		}
	}
	else if (Direction == 1)
	{
		if (SmokeAppear.getElapsedTime().asSeconds() >= 0.02)
		{
			Smoke* newSmoke = new Smoke(sf::Vector2f(spRocket.getPosition().x + 100, spRocket.getPosition().y), rand() % 350 + 1);
			_List.push_back(newSmoke);
			SmokeAppear.restart();
		}
	}

	if (Alive == false)
	{
		ExploRocket* newFx = new ExploRocket(spRocket.getPosition());
		_List.push_back(newFx);
	}
}
