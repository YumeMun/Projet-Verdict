#include "Smoke.h"
#include "ResourceManager.h"

Smoke::Smoke(sf::Vector2f _Pos)
{
	spSmoke.setTexture(*ResourceManager::Instance()->GetTexture("Smoke"));
	spSmoke.setOrigin(spSmoke.getGlobalBounds().width / 2, spSmoke.getGlobalBounds().height / 2);
	spSmoke.setPosition(_Pos);

	SmokeAlpha = sf::Color(255, 255, 255, 255);
	spSmoke.setColor(SmokeAlpha);
}

Smoke::~Smoke()
{
}

void Smoke::Update(float _Elapsed)
{
	if (SmokeAlpha.a - 500 * _Elapsed >= 0)
		SmokeAlpha.a -= 500 * _Elapsed;
	else
		SmokeAlpha.a = 0;

	if (SmokeAlpha.a <= 0)
		SmokeAlpha.a = 0;

	spSmoke.setColor(SmokeAlpha);
}

void Smoke::Display(sf::RenderWindow* _Window)
{
	_Window->draw(spSmoke);
}
