#pragma once
#include "Scene.h"
#include "Map.h"


class Player
{
public:
	Player();
	Player(int _ID, sf::Vector2f _Pos, class Map* _Map, int _skinNumber);
	~Player();
	void Update(float _Elapsed, class Map* _Map, class Caméra* _Cam, sf::Vector2f _Pos);
	void Display(sf::RenderWindow* _Window);
	void Controls(class Map* _Map, float _Elapsed);
	void Traps(class Map* _Map, Caméra* _Cam);
	bool IsAlive();
	void Animations();

	sf::Sprite GetSprite();

	sf::Vector2f GetPos();

	bool Hasfinished;
	sf::Clock PlayerFirstTimer;
	int Score;

	//void MissileCollide();

	bool CollectibleCollide(class Map* _Map);
	bool CollectibleUsed();
	bool HasCollectible, Oiled = false, Invincible = false;
	int GetCollectID();
	int GetAimDir();
	void LauchCollectible();
	void SetCollectID(int _CollectID);

	sf::Clock InvincibleTime;
	sf::Vector2f Player_Movement;
	//Missile* newMissile;

	void SetHitTrap();
	void SetHitLazer();
	void SetAnimWheelStart();
	void SetAnimClockRestart();
	int GetFrameIndex();
	bool isAnimStartEnd = false;

private:
	bool KeyPress = false, Alive = true, Jump = true, Boost = false, UseIt = false;

	int ID = 0, Player_Direction = 0, Rocket_Direction = 0, CollectID = 0;

	sf::Clock AnimClock;
	bool StartAnim = false;

	bool isJumping = false;
	bool isSpeedMax = false;
	bool isSwitching = false;
	bool isSwitchingBack = false;
	bool isHitLazer = false;
	bool isStartJumpSpeedMax = false;

	int trapHitCount = 1;
	float trapSpeedFactor = 1; 
	sf::Clock timerTrapFactor;

	sf::Clock BoostClock;

	//Provisoire
	sf::CircleShape ColliderCircle;

	sf::Sprite spPlayer;
	sf::IntRect PlayerRect;

	sf::Sprite spNumeroJoueur;
	sf::Clock DisplayNumeroTimer;
	sf::Clock AnimNumero;
	int FrameIndexNumero = 0;
	bool isNumeroDisplay;

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
