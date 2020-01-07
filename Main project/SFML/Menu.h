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
	sf::Text m_Credits;
	int m_MenuChoice = 1;
	sf::Clock m_Clock;
	sf::Sound Valider;
	sf::Sound sound;
	sf::Sprite spBackground;
	sf::Sprite spButton[5];
	sf::Sprite spFlèche;
	sf::Sprite spCreditsButton;

	sf::Sprite spLogo;
	sf::IntRect rectLogo;
	sf::Clock timerAnimLogo;
	sf::Clock timerLogoRestart;
	bool isRestart = false;
	int animCount = 0;
};