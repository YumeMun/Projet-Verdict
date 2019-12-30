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
	sf::RectangleShape m_shape;
	std::vector<sf::RectangleShape> m_LevelSelector;
	int FilesNumber;
	int m_MenuChoice = 1;
	sf::Clock m_Clock;
	bool LeftPressed = false;
	bool RightPressed = false;
	sf::Text m_Level;

	sf::Sprite spBackground;

	sf::Text LevelNameText[100];
	std::string LevelName[100];

	void LoadLevels();
	std::string ObjSeparator;
};