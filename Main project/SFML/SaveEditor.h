#pragma once
#include "Scene.h"

class SaveEditor : public Scene
{
public:
	SaveEditor();
	SaveEditor(int _SizeX, int _SizeY, std::string _Save, int _SelectionBackground, bool _RenameLevel, std::string _LastLevelName);
	~SaveEditor();

	virtual void Update();
	virtual void Display();
	virtual void EventManager(sf::Event p_pollingEvent);

	void SaveIt();

private:
	bool RenameLevel;
	int Tableau[34][1200];

	void VirtualKeyboard();

	sf::Sprite spBackground;

	sf::Text SaveText;
	sf::Text NameText;

	std::string LastLevelName;
	std::string LevelName;
	std::string Save;
	int Size_X;
	int Size_Y;
	int SelectionBackground;

	sf::Clock clock;
	bool Press = false, EnterPress = false;

	sf::Sprite spButtons[2];

	int Keyboard[5][12];
	sf::RectangleShape KeyRect;
	sf::Vector2f KeyPos;

	sf::Text KeyText[60];
	int Last_X;
	int Last_Y;
	int X;
	int Y;

	bool Maj = false;

	sf::Sprite Key[4];

	int PopUpActivated = 0;
	sf::Sprite spPopUp;
	sf::Text PopUpText[3];
	int SelectionPopUp = 1;
	sf::Clock SelectionTimer;

	void LoadLevels();
	std::string ObjSeparator;
	std::string LoadLevelNames[100];
	int FilesNumber = 0;
};

enum Keys
{
	NONE,
	BASICKEY,
	BACK,
	ENTER,
	SPACE,
	
	BASICKEY_SELECTED,
	BACK_SELECTED,
	ENTER_SELECTED,
	SPACE_SELECTED
};