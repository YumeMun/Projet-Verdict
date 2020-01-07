#pragma once
#include "Scene.h"

class LevelSelector : public Scene
{
public:
	LevelSelector();
	~LevelSelector();
	virtual void Update();
	virtual void Display();
	virtual void Setup();
	virtual void EventManager(sf::Event p_pollingEvent);

private:
	sf::Sprite spLevelSelection;
	sf::Sprite spVignette;

	std::vector<sf::Sprite> m_LevelSelector;
	int FilesNumber;
	int m_MenuChoice = 1;
	sf::Clock m_Clock;
	bool LeftPressed = false;
	bool RightPressed = false;
	sf::Text m_Level;

	sf::Sprite spBackground;
	sf::Sprite spButton;
	sf::Sprite spFlèches[2];
	sf::Sound Retour;
	sf::Sound Valider;
	sf::Sound sound;
	sf::Text LevelNameText[100];
	std::string LevelName[100];

	void LoadLevels();
	std::string ObjSeparator;
};