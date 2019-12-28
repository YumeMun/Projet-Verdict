#pragma once
#include "Scene.h"

class Menu :
	public Scene
{
public:
	Menu();
	~Menu();
	virtual void Update();
	virtual void Display();
	virtual void EventManager(sf::Event p_pollingEvent);

private:
	sf::Text m_NewGame;
	sf::Text m_Option;
	sf::Text m_Commande;
	sf::Text m_LevelEditor;
	sf::Text m_Quit;
	int m_MenuChoice = 1;
	sf::Clock m_Clock;

	sf::Sprite spBackground;
};