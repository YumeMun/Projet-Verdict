#pragma once
#include "Scene.h"
#include "GameManager.h"
#include "ResourceManager.h"

class Intro : public Scene
{
public:
	Intro();
	~Intro();

	int Setup();
	void Update();
	void Display();
	void EventManager(sf::Event p_pollingEvent);

private:
	sf::Sprite spLogo;
	sf::RectangleShape rectFade;
	sf::Texture textureLogo;
	sf::IntRect rectLogo;
	sf::Vector2f posLogo;
	sf::Vector2f scaleLogo;
	float alphaLogo = 255;
	float x;

	bool isintroEnd = false;
	bool isFadeEnd = false;
	sf::Clock timerAnimLogo;
	sf::Clock cooldown;

	sf::RenderWindow* m_actualWindow;
};

