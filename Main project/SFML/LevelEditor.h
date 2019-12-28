#pragma once
#include "HudEditor.h"

class LevelEditor :
	public Scene
{
public:
	LevelEditor();
	LevelEditor(int _SizeX, int _SizeY, std::string _LevelName);
	~LevelEditor();

	virtual void Update();
	virtual void Display();
	virtual void EventManager(sf::Event p_pollingEvent);

	void MouseManager();
	void ControllerManager();

	void Sauvegarde();
	void BackgroundChoice();

private:
	bool KeyPress = false;

	HudEditor* hud;

	float CurrentTime, LastFrameTime, ElapsedTime;

	int Tableau[34][1200];

	int Size_X;
	int Size_Y;
	std::string Save;

	sf::CircleShape SelecterTarget;

	sf::Vector2i MousePos;
	sf::Vector2i MousePosToView;

	sf::View View;
	sf::FloatRect ViewRect;

	int Select = 0;
	sf::RectangleShape Case;
	sf::Vector2f CasePos;
	sf::Vector2f SelectCasePos;

	//sf::Sprite spTile[8];

	sf::Sprite spInterface;

	int SelectionBackground = 1;
	sf::Sprite spFlèches[2];
	sf::Sprite spBackground;

	sf::Clock SelectionTimer;
};