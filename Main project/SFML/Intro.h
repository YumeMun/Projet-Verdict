#pragma once
#include "Scene.h"
#include "GameManager.h"
#include "ResourceManager.h"

class Intro : public Scene
{
public:
	Intro();
	~Intro();

	void Setup();
	void Update();
	void Display();
	void EventManager(sf::Event p_pollingEvent);

private:
	sf::RenderWindow* m_actualWindow;

	sf::Texture BackgroundTexture[2];
	sf::Sprite spBackground[2];
};