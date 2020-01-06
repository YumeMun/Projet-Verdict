#include "Caméra.h"
#include "GameManager.h"
#include "Jeu.h"

Caméra::Caméra(Player* _player1)
{
	std::cout << "Camera constructor" << std::endl;

	m_actualWindow = GameManager::Instance()->GetWindow();

	sizeCamera = { 1920/2, 1080/2 };
	camera.setViewport({ 0, 0, 1, 1 });
	startCenterCam.x = _player1->GetPos().x;
	startCenterCam.y = _player1->GetPos().y;
	centerCam = startCenterCam;
	camera.setCenter(centerCam);
	camera.setSize(sizeCamera);
}

Caméra::~Caméra()
{
}

void Caméra::Update(float _dTime, TimerStart* _timer, Player* _player1, Player* _player2, Map* _map)
{
	std::cout << "flag pos : " << _map->GetEndFlag().x << std::endl;
	std::cout << "center cam : " << centerCam.x << std::endl;

	if (clock.getElapsedTime().asSeconds() >= 3)
	{
		isGameStart = true;
		clock.restart();
	}

	if (_timer->GetIsTimerEnd())
	{
		if (isStarting)
		{
			if (_player1->GetPos().x > GetCameraCenter().x || _player2->GetPos().x > GetCameraCenter().x)
			{
				isStarting = false;
			}
		}
		else
		{
			if (!isEnding)
			{
				if (_player1->GetPos().x > GetCameraCenter().x + (sizeCamera.x / 4))
				{
					if (_player1->Player_Movement.x > 800)
					{
						cameraSpeed = _player1->Player_Movement.x;
					}
					else
						cameraSpeed = CAMERA_SPEED;
				}
				else if (_player2->GetPos().x > GetCameraCenter().x + (sizeCamera.x / 4))
				{
					if (_player2->Player_Movement.x > 800)
					{
						cameraSpeed = _player2->Player_Movement.x;
					}
					else
						cameraSpeed = CAMERA_SPEED;
				}
				else
					cameraSpeed = CAMERA_SPEED;

				camera.move(cameraSpeed * _dTime, 0);

				centerCam.x += cameraSpeed * _dTime;
				if (centerCam.x >= _map->GetEndFlag().x)
				{
					isEnding = true;
					std::cout << "IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIs ending = true " << std::endl;
				}
			}
		}
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

bool Caméra::GetIsZoomEnd()
{
	return isZoomEnd;
}

void Caméra::UpdateZoom(float _Elapsed, Map* _map, Player* _player1, Player* _player2)
{
	if (sizeCamera.x < 1920)
	{
		camera.zoom(zoom);
	}

	if (centerCam.x < _player2->GetPos().x + ((1920/2)+620))
	{
		centerCam.x += (CAMERA_ZOOM_SPEED * (16 / 9)) * _Elapsed;
		camera.setCenter(centerCam);
	}
	else if (centerCam.y < 1080/2)
	{
		centerCam.y += (CAMERA_ZOOM_SPEED) * _Elapsed;
		camera.setCenter(centerCam);
	}
	else
	{
		centerCam.x = _player2->GetPos().x + ((1920 / 2)+620);
		centerCam.y = 1080 / 2;
		camera.setCenter(centerCam);
	}
}