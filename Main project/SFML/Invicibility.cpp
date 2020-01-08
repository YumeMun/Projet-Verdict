#include "Invicibility.h"
#include "ResourceManager.h"

Invicibility::Invicibility(int _ID, sf::Vector2f _Pos)
{
	ID = _ID;
	spShield.setTexture(*ResourceManager::Instance()->GetTexture("Shield"));
	spShield.setTextureRect(sf::IntRect(0, 0, 353, 183));
	spShield.setOrigin(spShield.getGlobalBounds().width / 2, spShield.getGlobalBounds().height / 2);
	spShield.setPosition(_Pos);
}

Invicibility::~Invicibility()
{
}

void Invicibility::Update(Player* _Player1, Player* _Player2, Map* _Map, float _Elapsed, Caméra* _Cam)
{
	if (ID == 1)
	{
		spShield.setPosition(_Player1->GetPos());

		if (_Player1->Invincible == false)
			Alive = false;
	}
	else if (ID == 2)
	{
		spShield.setPosition(_Player2->GetPos());

		if (_Player2->Invincible == false)
			Alive = false;
	}

	if (AnimTime.getElapsedTime().asSeconds() >= 0.05)
	{
		if (AnimFrameIndex < 9)
			AnimFrameIndex++;
		else
			AnimFrameIndex = 0;

		AnimTime.restart();
	}

	spShield.setTextureRect(sf::IntRect(353 * AnimFrameIndex, 0, 353, 183));
}

void Invicibility::Display(sf::RenderWindow* _Window)
{
	_Window->draw(spShield);
}

bool Invicibility::IsAlive()
{
	return Alive;
}

void Invicibility::AddFxs(std::vector<Fx*>& _List)
{
}
