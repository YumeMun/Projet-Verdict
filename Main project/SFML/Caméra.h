#pragma once
#include "Scene.h"
#define DISTANCE_MIN_X 1000
#define DISTANCE_MAX_X 1500
#define CAMERA_WIDTH_MIN 2000*1.778 // = (distance min x * 2) * ratio ecran
#define CAMERA_HEIGHT_MIN 2000  // = (distance min x * 2)
#define RATIO_ECRAN 16/9
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#define DISTANCE_KILL_X 1920/2 //selon affichage //ancien : 2765
#define ZOOM_START_SPEED 300
#define CAMERA_START_WIDTH 1000*1.778
#define CAMERA_START_HEIGHT 1000
#define NOMBRE_POINT_SPAWN 3
#define PLAYER_SPEED 300

#define CAMERA_SPEED 700

class Caméra
{
public:
	Caméra();
	~Caméra();

	void Update(float _dTime);
	void Display();

	sf::View* GetCamera();
	sf::Vector2f GetCameraCenter();
	float GetDistancePlayer();
	sf::Vector2f GetSizeCamera();

	//Pas la vrai origine(25% de l'écran)
	sf::Vector2f GetCamOrigin();

	bool GetStart();

private:
	sf::RenderWindow* m_actualWindow;

	sf::Texture textureBc;
	sf::Sprite spBc;

	sf::Vector2f sizeCamera;
	sf::Vector2f cameraCenter;
	float distancePlayerX;
	float distancePlayerY;
	bool isPlayer1First;
	bool isPlayer1Upper;

	bool isGameStart = false;
	bool isCurrentSpawnPointFind = false;
	sf::Vector2f respawnPoint;
	sf::Vector2f listRespawnPoint[NOMBRE_POINT_SPAWN];
	sf::View camera;

	sf::Clock clock;
};