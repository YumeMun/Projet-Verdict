#pragma once
#include "Scene.h"

class OpenLevelEditor :
	public Scene
{
public:
	OpenLevelEditor();
	~OpenLevelEditor();

	virtual void Update();
	virtual void Display();
	virtual void EventManager(sf::Event p_pollingEvent);

	void LoadLevels();

private:
	sf::Clock SelectionTimer;
	int LevelSelected = 0;
	int FilesNumber = 0;

	std::string ObjSeparator;

	sf::RectangleShape LevelIcon[10];

	std::string LevelName[10];
	sf::Text LevelNameText[10];

	sf::Sprite spBackground;
};