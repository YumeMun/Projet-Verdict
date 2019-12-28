#pragma once
#include <iostream>
#include<SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Enum.h"

class GameManager;

class Scene
{
protected:
	sf::Event m_eventPoll;
	sf::RenderWindow* m_actualWindow;

public:
	Scene();
	~Scene();
	virtual void Update() = 0;
	virtual void Display() = 0;
	virtual void EventManager(sf::Event p_pollingEvent) = 0;
};