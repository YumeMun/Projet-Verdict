#include "HUD.h"
#include "GameManager.h"
#include "Caméra.h"
#include "Player.h"

HUD::HUD()
{
	std::cout << "HUD constructor" << std::endl;

	m_actualWindow = GameManager::Instance()->GetWindow();
	
	
	SetupProgressLevel();
		//SetupIconCollectable();
	SetupPlayerHUD();

	for (int i = 0; i < 2; i++)
	{
		iconCollectable[i].setRadius(30);
		iconCollectable[i].setFillColor(sf::Color::Green);
	}
}

HUD::~HUD()
{
}

void HUD::SetupProgressLevel()
{
	progressionNiveau.setFillColor(sf::Color::Green);
	progressionNiveau.setSize({ MINI_LEVEL_WIDTH, MINI_LEVEL_HEIGHT });

	Player1.setFillColor(sf::Color::Red);
	Player1.setSize({ PLAYER_WIDTH, PLAYER_WIDTH });

	Player2.setFillColor(sf::Color::Cyan);
	Player2.setSize({ PLAYER_WIDTH, PLAYER_WIDTH });
}

void HUD::SetupPlayerHUD()
{
	for (int i = 0; i < 2; i++)
	{
		iconPlayer[i].setSize(sf::Vector2f(100, 100));
		iconPlayer[i].setFillColor(sf::Color::Red);
		iconPlayer[i].setPosition(sf::Vector2f(50, 50));

		bcIconPlayer[i].setSize(sf::Vector2f(220, 120));
		bcIconPlayer[i].setFillColor(sf::Color::Yellow);
		bcIconPlayer[i].setPosition(sf::Vector2f(50-10, 50-10));
	}

	iconPlayer[1].setFillColor(sf::Color::Cyan);
	iconPlayer[1].setPosition(sf::Vector2f(1920-150, 50));
	bcIconPlayer[1].setPosition(sf::Vector2f(1920-260, 50 - 10));
}

void HUD::Update(sf::Vector2f _viewCenter, sf::Vector2f _sizeCamera, sf::Vector2f _posP1, sf::Vector2f _posP2)
{
	SetProgressionPlayer(_posP1, _posP2);
	//GetCollisionWithCollectible(_posPlayer1, _posPlayer2);

	/*for (int i = 0; i < NB_COLLECTABLE; i++)
	{
		if (listCollectable[i]->isCollected)
		{
			std::cout << "item collected, item no :" << i << std::endl;
			for (int y = 0; y < NB_PLAYER; y++)
			{
				if (!listCollectable[y]->isPlayerFull)
				{
					if (listCollectable[y]->playerThatCollected)
					{
						listCollectable[y]->iconCollectable[i].setPosition(listCollectable[y]->posPlayerHUD);
						listCollectable[y]->isIconDrawable = true;
						listCollectable[i]->isCollected = false;
						listCollectable[y]->isPlayerFull = true;
					}
				}
			}
		}
	}*/
}

void HUD::Display(bool _J1HasCollectible, bool _J2HasCollectible)
{
	m_actualWindow->draw(progressionNiveau);
	m_actualWindow->draw(Player2);
	m_actualWindow->draw(Player1);

	for (int i = 0; i < 2; i++)
	{
		m_actualWindow->draw(bcIconPlayer[i]);
		m_actualWindow->draw(iconPlayer[i]);
	}

	if (_J1HasCollectible == true)
	{
		iconCollectable[0].setPosition(bcIconPlayer[0].getPosition().x + 130, bcIconPlayer[0].getPosition().y + 30);
		m_actualWindow->draw(iconCollectable[0]);
	}
	if (_J2HasCollectible == true)
	{
		iconCollectable[1].setPosition(bcIconPlayer[1].getPosition().x + 40, bcIconPlayer[0].getPosition().y + 30);
		m_actualWindow->draw(iconCollectable[1]);
	}
}

void HUD::SetProgressionLevel(sf::Vector2f _viewCenter, sf::Vector2f _sizeCamera, sf::Vector2f _posPlayer1, sf::Vector2f _posPlayer2)
{
	posProgressionNiveau = { _viewCenter.x - (progressionNiveau.getGlobalBounds().width / 2), (_viewCenter.y - (_sizeCamera.x / 5)) - (_sizeCamera.x / POS_MINI_LEVEL) };
	progressionNiveau.setPosition(posProgressionNiveau);
	progressionNiveau.setSize({ MINI_LEVEL_WIDTH * (_sizeCamera.x / CAMERA_HEIGHT_MIN), MINI_LEVEL_HEIGHT * (_sizeCamera.x / CAMERA_HEIGHT_MIN)});

	progressionPlayer1 = (_posPlayer1.x / (LEVEL_WIDTH / MINI_LEVEL_WIDTH) * (_sizeCamera.x / (LEVEL_WIDTH / 4))); // parcours du j1 relatif a la taille du mini level --> relatif au level
	progressionPlayer2 = (_posPlayer2.x / (LEVEL_WIDTH / MINI_LEVEL_WIDTH) * (_sizeCamera.x / (LEVEL_WIDTH))); // parcours du j2 relatif a la taille du mini level --> relatif au level

	Player1.setPosition({ posProgressionNiveau.x + progressionPlayer1, posProgressionNiveau.y - (_sizeCamera.x / POS_PLAYER_Y_RELATIVE_LEVEL) });
	Player1.setSize({ PLAYER_WIDTH * (_sizeCamera.x / CAMERA_HEIGHT_MIN), PLAYER_WIDTH * (_sizeCamera.x / CAMERA_HEIGHT_MIN) });

	Player2.setPosition({ posProgressionNiveau.x + progressionPlayer2, posProgressionNiveau.y - (_sizeCamera.x / POS_PLAYER_Y_RELATIVE_LEVEL) });
	Player2.setSize({ PLAYER_WIDTH * (_sizeCamera.x / CAMERA_HEIGHT_MIN), PLAYER_WIDTH * (_sizeCamera.x / CAMERA_HEIGHT_MIN) });

	//std::cout << _posPlayer1.x << std::endl;
}

void HUD::SetProgressionPlayer(sf::Vector2f _posPlayer1, sf::Vector2f _posPlayer2)
{
	progressionPlayer1 = _posPlayer1.x / (LEVEL_WIDTH / MINI_LEVEL_WIDTH);
	progressionPlayer2 = _posPlayer2.x / (LEVEL_WIDTH / MINI_LEVEL_WIDTH);

	progressionNiveau.setPosition(sf::Vector2f((1920 / 2) - (progressionNiveau.getGlobalBounds().width / 2), POS_MINI_LEVEL_Y));
	Player1.setPosition({ progressionNiveau.getPosition().x - (Player1.getGlobalBounds().width/2) + progressionPlayer1, POS_MINI_PLAYER_Y });
	Player2.setPosition({ progressionNiveau.getPosition().x - (Player2.getGlobalBounds().width/2) + progressionPlayer2, POS_MINI_PLAYER_Y });

	//std::cout << _posPlayer1.x << std::endl;
}