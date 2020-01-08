#include "BoostEffect.h"
#include "ResourceManager.h"

BoostEffect::BoostEffect(int _ID, sf::Vector2f _Pos)
{
	ID = _ID;

	spBoostFx.setTexture(*ResourceManager::Instance()->GetTexture("BoostFx" + std::to_string(ID)));

	if (ID == 1)
		spBoostFx.setTextureRect(sf::IntRect(0, 0, 360, 135));
	else if (ID == 2)
		spBoostFx.setTextureRect(sf::IntRect(0, 0, 372, 150));

	spBoostFx.setOrigin(spBoostFx.getGlobalBounds().width / 2, spBoostFx.getGlobalBounds().height / 2);

	spBoostFx.setScale(0.7, 0.7);

	spBoostFx.setPosition(_Pos);
}

BoostEffect::~BoostEffect()
{
}

void BoostEffect::Update(float _Elapsed, Player* _Player1, Player* _Player2)
{
	if (AnimTime.getElapsedTime().asSeconds() >= 0.01)
	{
		AnimFrameIndex++;

		if (AnimFrameIndex >= 9)
			AnimFrameIndex = 0;

		AnimTime.restart();
	}

	if (ID == 1)
	{
		spBoostFx.setPosition(_Player1->GetPos());
		spBoostFx.setTextureRect(sf::IntRect(360 * AnimFrameIndex, 0, 360, 135));

		if (_Player1->Boost == false || _Player1->Jump == true)
			Alive = false;
	}
	else if (ID == 2)
	{
		spBoostFx.setPosition(_Player2->GetPos());
		spBoostFx.setTextureRect(sf::IntRect(372 * AnimFrameIndex, 0, 372, 150));

		if (_Player2->Boost == false || _Player2->Jump == true)
			Alive = false;
	}
}

void BoostEffect::Display(sf::RenderWindow* _Window)
{
	_Window->draw(spBoostFx);
}

bool BoostEffect::IsAlive()
{
	return Alive;
}
