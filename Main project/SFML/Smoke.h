#pragma once
#include "Scene.h"

class Smoke
{
public :
	Smoke(sf::Vector2f _Pos);
	~Smoke();
	void Update(float _Elapsed);
	void Display(sf::RenderWindow* _Window);

	sf::Color SmokeAlpha;
private:

	sf::Sprite spSmoke;

};

