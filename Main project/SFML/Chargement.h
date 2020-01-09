#pragma once
#include "Scene.h"
#include <thread>

class Chargement :
	public Scene
{
public:
	Chargement();
	~Chargement();
	virtual void Update();
	virtual void Display();
	virtual void EventManager(sf::Event p_pollingEvent);

	void Load();

private:
	std::thread LoadThread;
	bool isLoaded;

	sf::Font Font;

	sf::RectangleShape LoadingBar, LoadingBack;

	sf::IntRect rectLogo;
	sf::Clock timerAnimLogo;
	int animCount = 0;
	bool isLogoRestart = false;

	sf::Texture BackgroundTexture[2];
	sf::Sprite spBackground[2];

	sf::Texture LogoTexture[2];
	sf::Sprite spLogo[2];
	float Scale[2];

	sf::Text Percent;

	sf::Clock AnimLogo;
};