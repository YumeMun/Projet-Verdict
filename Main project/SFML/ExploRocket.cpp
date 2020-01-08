#include "ExploRocket.h"
#include "ResourceManager.h"

ExploRocket::ExploRocket(sf::Vector2f _Pos)
{
	spExplo.setTexture(*ResourceManager::Instance()->GetTexture("ExploRocket"));
	spExplo.setTextureRect(sf::IntRect(0, 0, 257, 257));
	spExplo.setOrigin(spExplo.getGlobalBounds().width / 2, spExplo.getGlobalBounds().height / 2);
	spExplo.setPosition(_Pos);
}

ExploRocket::~ExploRocket()
{
}

void ExploRocket::Update(float _Elapsed, Player* _Player1, Player* _Player2)
{
	if (AnimTime.getElapsedTime().asSeconds() > 0.06 && AnimFrameIndex < 20)
	{
		AnimFrameIndex++;
		AnimTime.restart();
	}
	else if (AnimFrameIndex >= 20)
		Alive = false;

	spExplo.setTextureRect(sf::IntRect(257 * AnimFrameIndex, 0, 257, 257));
}

void ExploRocket::Display(sf::RenderWindow* _Window)
{
	_Window->draw(spExplo);
}

bool ExploRocket::IsAlive()
{
	return Alive;
}
