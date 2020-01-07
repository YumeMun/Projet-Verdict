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

	sf::Sound sound;
	sf::Sprite spButton[5];
	sf::Sprite spFlèche;
	sf::Sprite spCreditsButton;

	sf::Sprite spBackground;
	sf::Sprite spPoster;
	sf::Sprite spBordurePanneau;
	sf::Sprite spLumières;
	sf::Sprite spRampe;
	sf::Sprite spTram;
	sf::Sprite spBras;
	sf::Sprite spPanneau;

	float RotationBras = 0;

	sf::Clock AnimLights;
	sf::Clock AnimBras;
	sf::Clock AnimPanneau;

	sf::Sprite spLogo;
	sf::IntRect rectLogo;
	sf::Clock timerAnimLogo;
	sf::Clock timerLogoRestart;
	bool isRestart = false;
	int animCount = 0;
};