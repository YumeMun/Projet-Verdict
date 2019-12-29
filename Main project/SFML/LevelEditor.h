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

	sf::Sprite spSelecterTarget;

	sf::Vector2i MousePos;
	sf::Vector2i MousePosToView;

	sf::View View;
	sf::FloatRect ViewRect;

	int Select = 0;
	sf::RectangleShape Case;
	sf::Vector2f CasePos;
	sf::Vector2f SelectCasePos;

	sf::Sprite spTile[60];

	bool HudDisplay = true;
	sf::Sprite spInterface;

	int SelectionBackground = 1;
	sf::Sprite spFlèches[2];
	sf::Sprite spBackground;

	sf::Clock SelectionTimer;

	int PopUpActivated = 0;
	sf::Sprite spPopUp;
	sf::Text PopUpText[3];
	int SelectionPopUp = 1;

	sf::Sprite spBoutonSauvegarde;
	sf::Sprite spTouches;
	sf::Sprite spToucheSelect;
	sf::Sprite spTouchesZoom[4];

	sf::RectangleShape BandeauGaucheRect;
};