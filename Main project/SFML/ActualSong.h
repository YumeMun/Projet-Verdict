#pragma once
#include "Scene.h"

class ActualSong
{
public:
	ActualSong();
	~ActualSong();

	void Setup();
	void SetActualSong();
	void Display();

private:
	sf::Sprite spCadre;
	sf::Vector2f posCadre;
	bool isCadreDrawable = false;

	sf::Text txtActualSong;
	sf::String strActualSong[2];

	sf::RenderWindow* m_actualWindow;
};

