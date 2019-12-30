#pragma once
#include "Scene.h"

class HudEditor
{
public:
	HudEditor();
	~HudEditor();

	void Display();
	void EventManager(sf::Event p_pollingEvent);

	int Selection;

private:
	bool KeyPress = false;

	void TileName();

	sf::RenderWindow* m_actualWindow;

	sf::Sprite spTile[60];

	sf::Sprite spTouches[2];

	sf::Sprite spBandeau;
	sf::RectangleShape SelectionShape;

	sf::Sprite spInfoTileRect;
	sf::Text InfoTileText;

	sf::Clock SelectionTimer;
};