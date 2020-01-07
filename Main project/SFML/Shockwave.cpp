#include "Shockwave.h"
#include "ResourceManager.h"

Shockwave::Shockwave(int _ID, sf::Vector2f _Pos)
{
	ID = _ID;

	spShockwave.setTexture(*ResourceManager::Instance()->GetTexture("Shock"));
	spShockwave.setTextureRect(sf::IntRect(0, 0, 803, 803));
	spShockwave.setOrigin(401.5, 401.5);
	spShockwave.setPosition(_Pos);
}

Shockwave::~Shockwave()
{
}

void Shockwave::Update(Player* _Player1, Player* _Player2, Map* _Map, float _Elapsed, Caméra* _Cam)
{
	if (ID == 1)
	{
		spShockwave.setPosition(_Player1->GetPos());

		if (spShockwave.getGlobalBounds().contains(_Player2->GetPos()) && AnimFrameIndex >= 10 && _Player2->Invincible == false)
		{
			_Player2->Player_Movement.x = cos(atan2(_Player1->GetPos().y - _Player2->GetPos().y, _Player1->GetPos().x - _Player2->GetPos().x)) * 4;
			_Player2->Player_Movement.y = sin(atan2(_Player1->GetPos().y - _Player2->GetPos().y, _Player1->GetPos().x - _Player2->GetPos().x)) * 4;
		}
	}
	else if (ID == 2)
	{
		spShockwave.setPosition(_Player2->GetPos());

		if (spShockwave.getGlobalBounds().contains(_Player1->GetPos()) && AnimFrameIndex >= 10 && _Player1->Invincible == false)
		{
			_Player1->Player_Movement.x = cos(atan2(_Player1->GetPos().y - _Player2->GetPos().y, _Player1->GetPos().x - _Player2->GetPos().x)) * 4;
			_Player1->Player_Movement.y = sin(atan2(_Player1->GetPos().y - _Player2->GetPos().y, _Player1->GetPos().x - _Player2->GetPos().x)) * 4;
		}
	}

	if (AnimTime.getElapsedTime().asSeconds() >= 0.05 && AnimFrameIndex < 16)
	{
		AnimFrameIndex++;
		AnimTime.restart();
	}

	spShockwave.setTextureRect(sf::IntRect(803 * AnimFrameIndex, 0, 803, 803));

	if (AnimFrameIndex >= 16)
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
