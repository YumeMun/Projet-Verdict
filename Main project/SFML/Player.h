#pragma once
#include "Scene.h"
#include "Map.h"
#include "Missile.h"


class Player
{
public:
	Player();
	Player(int _ID, sf::Vector2f _Pos);
	~Player();
	void Update(float _Elapsed, Map* _Map, Caméra* _Cam, sf::Vector2f _Pos);
	void Display(sf::RenderWindow* _Window);
	void Controls(Map* _Map);
	void Traps(Map* _Map);
	bool IsAlive();
	void Animations();

	sf::Sprite GetSprite();

	sf::Vector2f GetPos();

	bool Hasfinished;
	sf::Clock PlayerFirstTimer;
	int Score;

	//void MissileCollide();

	bool CollectibleCollide(Map* _Map);
	bool CollectibleUsed();
	bool HasCollectible, Oiled = false;
	int GetCollectID();
	void LauchCollectible();
	void SetCollectID(int _CollectID);

	sf::Vector2f Player_Movement;
	//Missile* newMissile;

	void SetHitTrap();
	void SetHitLazer();

private:
	bool KeyPress = false, Alive = true, Jump = true, Boost = false, UseIt = false;

	int ID = 0, Player_Direction = 0, Missile_Direction = 0, CollectID = 0;

	sf::Clock AnimClock;
	bool StartAnim = false;

	bool isJumping = false;
	bool isSpeedMax = false;
	bool isSwitching = false;
	bool isSwitchingBack = false;
	bool isHitLazer = false;

	int trapHitCount = 1;
	float trapSpeedFactor = 1; 
	sf::Clock timerTrapFactor;

	sf::Clock BoostClock;

	sf::Sprite spPlayer;
	sf::IntRect PlayerRect;

	sf::Vector2f Player_Vector;
	sf::Vector2f Player_SlopVector;
	sf::Vector2f Player_ColliderLimit;

	enum _eDirection
	{
		NONE,
		UP,
		DOWN
	};

	int FrameIndex = 0;
	int lastFrameSpeed = 800;
};
