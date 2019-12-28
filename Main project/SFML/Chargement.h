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

	sf::Text LoadingTxt;
	sf::RectangleShape LoadingBar, LoadingBack;

	sf::Sprite spLogo;
	sf::IntRect rectLogo;
	sf::Clock timerAnimLogo;
	int animCount = 0;
};