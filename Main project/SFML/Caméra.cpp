#include "Cam�ra.h"
#include "GameManager.h"
#include "Jeu.h"

Cam�ra::Cam�ra()
{
	std::cout << "Camera constructor" << std::endl;

	m_actualWindow = GameManager::Instance()->GetWindow();

	sizeCamera = { 1920, 1080 };
	camera.setViewport({ 0, 0, 1, 1 });
	camera.setCenter(1920, 1080);
	camera.setSize(sizeCamera);
	camera.zoom(2);

	respawnPoint = { 6000, 500 };

	listRespawnPoint[0] = { 6000, 500 };
	listRespawnPoint[1] = { 9000, 700 };
	listRespawnPoint[2] = { 12000, 900 };
}

Cam�ra::~Cam�ra()
{
}

void Cam�ra::Update(float _dTime)
{
	if (clock.getElapsedTime().asSeconds() >= 3)
	{
		isGameStart = true;
		clock.restart();
	}

	if (isGameStart)
	{
		cameraCenter.x += CAMERA_SPEED * _dTime;
		camera.setCenter(cameraCenter);
	}
}

void Cam�ra::Display()
{

}

sf::View* Cam�ra::GetCamera()
{
	return &camera;
}

sf::Vector2f Cam�ra::GetCameraCenter()
{
	cameraCenter.x = camera.getCenter().x;
	cameraCenter.y = GetCamera()->getCenter().y;
	return cameraCenter;
}

float Cam�ra::GetDistancePlayer()
{
	return distancePlayerX;
}

sf::Vector2f Cam�ra::GetSizeCamera()
{
	return camera.getSize();
}

sf::Vector2f Cam�ra::GetCamOrigin()
{
	return sf::Vector2f(GetCameraCenter().x - GetSizeCamera().x / 4, GetCameraCenter().y);
}

bool Cam�ra::GetStart()
{
	return isGameStart;
}
