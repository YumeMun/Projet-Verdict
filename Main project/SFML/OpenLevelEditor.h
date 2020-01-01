#pragma once
#include "Scene.h"

class OpenLevelEditor :
	public Scene
{
public:
	OpenLevelEditor();
	~OpenLevelEditor();

	virtual void Setup();
	virtual void Update();
	virtual void Display();
	virtual void EventManager(sf::Event p_pollingEvent);

private:
	sf::Sprite spLevelSelection;
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
	sf::Sprite spTouches;

	sf::Text LevelNameText[100];
	std::string LevelName[100];

	void LoadLevels();
	std::string ObjSeparator;

	void PopUp();
	int PopUpActivated = 0;
	sf::Sprite spPopUp;
	sf::Text PopUpText[3];
	int SelectionPopUp = 1;
	sf::Clock SelectionTimer;

	sf::Text NoFileText;
};