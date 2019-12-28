#pragma once
#include "Scene.h"
#define PLAYER_WIDTH 50					//
#define POS_PLAYER_Y_RELATIVE_LEVEL 30  //
#define POS_MINI_LEVEL 25				//
#define MINI_LEVEL_WIDTH 500			//
#define MINI_LEVEL_HEIGHT 50			//ancien

#define POS_MINI_LEVEL_Y 150 //pos lvl + pos player
#define POS_MINI_PLAYER_Y 50
#define LEVEL_WIDTH 20400	

#define NB_COLLECTABLE 2
#define NB_PLAYER 2


class HUD
{
public:
	HUD();
	~HUD();

	void SetupProgressLevel();
	void SetupPlayerHUD();

	void Update(sf::Vector2f _viewCenter, sf::Vector2f _sizeCamera, sf::Vector2f _posP1, sf::Vector2f _posP2);
	void Display(bool _J1HasCollectible, bool J2HasCollectible);

	void SetProgressionLevel(sf::Vector2f _viewCenter, sf::Vector2f _sizeCamera, sf::Vector2f _posPlayer1, sf::Vector2f _posPlayer2); //ancien
	void SetProgressionPlayer(sf::Vector2f _posPlayer1, sf::Vector2f _posPlayer2);

private:
	sf::RenderWindow* m_actualWindow;
	//Player* player;

	sf::RectangleShape iconPlayer[2];
	sf::RectangleShape bcIconPlayer[2];
	
	sf::CircleShape iconCollectable[2];
	sf::Vector2f posPlayerHUD;
	std::vector<HUD*> listCollectable;
	sf::String nameCollectable;
	bool isCollected[2];
	bool isCollectableInit;
	bool isIconDrawable[2];
	bool isItemUse = false;

	bool playerThatCollected;
	bool isPlayerFull = false;

	////////////MINI-MAP///////////
	sf::RectangleShape progressionNiveau;
	sf::RectangleShape Player1;
	sf::RectangleShape Player2;
	sf::Vector2f posProgressionNiveau;
	sf::Vector2f posPlayer1;
	float progressionPlayer1;
	float progressionPlayer2;

	sf::Clock clock;
};