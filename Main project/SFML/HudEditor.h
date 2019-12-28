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

	sf::RenderWindow* m_actualWindow;

	//sf::Sprite spTile[8];

	sf::Sprite spTile[60];

	sf::Sprite spBandeau;
	sf::RectangleShape SelectionShape;
};