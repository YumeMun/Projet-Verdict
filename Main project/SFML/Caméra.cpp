#include "Cam�ra.h"
#include "GameManager.h"
#include "Jeu.h"

Cam�ra::Cam�ra(Player* _player1)
{
	std::cout << "Camera constructor" << std::endl;

	m_actualWindow = GameManager::Instance()->GetWindow();

	sizeCamera = { (1920*1.8)/2.4, (1080*1.8)/2.4 };
	camera.setViewport({ 0, 0, 1, 1 });
	centerCam = _player1->GetPos();
	camera.setCenter(_player1->GetPos());
	camera.setSize(sizeCamera);
	//camera.zoom(1.8);
	std::cout << "center cam y start: " << centerCam.y << std::endl;
	std::cout << "center cam x start: " << centerCam.x << std::endl;
}

Cam�ra::~Cam�ra()
{
}

void Cam�ra::Update(float _dTime, TimerStart* _timer, Player* _player1, Player* _player2)
{
	//std::cout << "player 1 speed : " << _player1->Player_Movement.x << std::endl;

	if (clock.getElapsedTime().asSeconds() >= 3)
	{
		isGameStart = true;
		clock.restart();
	}

	if (_timer->GetIsTimerEnd())
	{
		if (_player1->GetPos().x > GetCameraCenter().x + (sizeCamera.x/4))
		{
			if (_player1->Player_Movement.x > 800)
			{
				camera.move(_player1->Player_Movement.x * _dTime, 0);
			}
			else
				camera.move(CAMERA_SPEED * _dTime, 0);
		}
		else if (_player2->GetPos().x > GetCameraCenter().x + (sizeCamera.x / 4))
		{
			if (_player2->Player_Movement.x > 800)
			{
				camera.move(_player2->Player_Movement.x * _dTime, 0);
			}
			else
				camera.move(CAMERA_SPEED * _dTime, 0);
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

bool Cam�ra::GetIsZoomEnd()
{
	return isZoomEnd;
}

void Cam�ra::UpdateZoom(float _Elapsed, Map* _map)
{
	if (sizeCamera.x < 1920*1.8)
	{
		camera.zoom(zoom);
	}

	if (centerCam.y > _map->GetStartPos().y - 520)
	{
		centerCam.y -= CAMERA_ZOOM_SPEED * _Elapsed;
		camera.setCenter(centerCam);
	}

	if (centerCam.x < _map->GetStartPos().x + 1300)
	{
		centerCam.x += (CAMERA_ZOOM_SPEED*(16/9)) * _Elapsed;
		camera.setCenter(centerCam);
	}
	else
	{
		centerCam = { _map->GetStartPos().x + 1300, _map->GetStartPos().y - 520 };
		camera.setCenter(centerCam);
	}
}
