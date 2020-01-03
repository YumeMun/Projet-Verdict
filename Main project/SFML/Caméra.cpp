#include "Caméra.h"
#include "GameManager.h"
#include "Jeu.h"

Caméra::Caméra()
{
	std::cout << "Camera constructor" << std::endl;

	m_actualWindow = GameManager::Instance()->GetWindow();

	sizeCamera = { 1920, 1080 };
	camera.setViewport({ 0, 0, 1, 1 });
	camera.setCenter(1728, 1080);
	camera.setSize(sizeCamera);
	camera.zoom(1.8);
}

Caméra::~Caméra()
{
}

void Caméra::Update(float _dTime, TimerStart* _timer)
{
	if (clock.getElapsedTime().asSeconds() >= 3)
	{
		isGameStart = true;
		clock.restart();
	}

	if (_timer->GetIsTimerEnd())
	{
		camera.move(CAMERA_SPEED * _dTime, 0);
	}
}

void Caméra::Display()
{

}

sf::View* Caméra::GetCamera()
{
	return &camera;
}

sf::Vector2f Caméra::GetCameraCenter()
{
	return camera.getCenter();
}

float Caméra::GetDistancePlayer()
{
	return distancePlayerX;
}

sf::Vector2f Caméra::GetSizeCamera()
{
	return camera.getSize();
}

sf::Vector2f Caméra::GetCamOrigin()
{
	return sf::Vector2f(GetCameraCenter().x - GetSizeCamera().x / 4, GetCameraCenter().y);
}

bool Caméra::GetStart()
{
	return isGameStart;
}
