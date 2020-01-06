#pragma once
#include "Scene.h"
#include "Caméra.h"

class Map
{
public:
	Map();
	Map(std::string _LevelName);
	~Map();

	void Update(float _Elapsed, class Caméra* _Cam);
	void Display();

	int GetTile(int _X, int _Y);
	void SetTile(int _X, int _Y, int _Tile);
	int GetSizeX();
	int GetSizeY();
	sf::Vector2f GetStartPos();

	sf::Vector2f GetPos();

	sf::Vector2f GetCheckPoint(sf::Vector2f _Pos);

	sf::Vector2f GetNextTile(int _Type, sf::Vector2f _Pos);
	int GetIsLazerOn();

private:
	sf::RenderWindow* m_actualWindow;

	int Size_X;
	int Size_Y;
	int SelectionBackground;
	int Tableau[34][1200];
	sf::Vector2f CasePos;
	sf::Sprite Plan[4], Plan2[4], Plan1[2];

	sf::Sprite spTile[30];

	std::vector<int> XListCheckpoint;
	std::vector<int> XListStart;

	sf::CircleShape Collectible;

	sf::Clock timerLazer;
	int isLazerOn = 3;
	void AnimTiles();
	sf::Clock AnimBoostClock;
	int FrameIndexBoost = 0;
	sf::Clock AnimCollectClock;
	int FrameIndexCollect = 0;
	sf::Clock AnimLaserClock;
	int FrameIndexLaser = 0;
	sf::Clock AnimElectClock;
	int FrameIndexElect = 0;
	sf::Clock AnimCaisseClock;
	int FrameIndexCaisse = 0;
};