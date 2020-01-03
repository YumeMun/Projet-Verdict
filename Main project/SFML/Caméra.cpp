#include "Cam�ra.h"
#include "GameManager.h"
#include "Jeu.h"

Cam�ra::Cam�ra()
{
	std::cout << "Camera constructor" << std::endl;

	m_actualWindow = GameManager::Instance()->GetWindow();

	sizeCamera = { 1920, 1080 };
	camera.setViewport({ 0, 0, 1, 1 });
	camera.setCenter(1728, 1080);
	camera.setSize(sizeCamera);
	camera.zoom(1.8);
}

Cam�ra::~Cam�ra()
{
}

void Cam�ra::Update(float _dTime, TimerStart* _timer, Player* _player1, Player* _player2)
{
	if (clock.getElapsedTime().asSeconds() >= 3)
	{
		isGameStart = true;
		clock.restart();
	}

	if (_timer->GetIsTimerEnd())
	{
		if (_player1->GetPos().x > GetCameraCenter().x + (sizeCamera.x/4) || _player2->GetPos().x > GetCameraCenter().x + (sizeCamera.x / 4))
		{
			camera.move(CAMERA_SPEED_MAX * _dTime, 0);
		}
		else
			camera.move(CAMERA_SPEED * _dTime, 0);
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
	return camera.getCenter();
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
