#pragma once
#include "Scene.h"
#include "Caméra.h"

class Map
{
public:
	Map();
	Map(std::string _LevelName);
	~Map();

	void Update(float _Elapsed, Caméra* _Cam);
	void Display();

	int GetTile(int _X, int _Y);
	void SetTile(int _X, int _Y, int _Tile);

	sf::Vector2f GetPos();

	sf::Vector2f GetCheckPoint(sf::Vector2f _Pos);

	sf::Vector2f GetNextTile(int _Type, sf::Vector2f _Pos);

private:
	sf::RenderWindow* m_actualWindow;

	int Size_X;
	int Size_Y;
	int SelectionBackground;
	int Tableau[34][1200];
	sf::Vector2f CasePos;
	sf::Sprite Plan[4], Plan2[4], Plan1[2];

	sf::Sprite spTile[30];

	std::vector<int> XList;

	sf::CircleShape Collectible;
};