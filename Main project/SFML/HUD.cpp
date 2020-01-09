#include "HUD.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "Caméra.h"
#include "Player.h"

HUD::HUD()
{
	m_actualWindow = GameManager::Instance()->GetWindow();


	SetupProgressLevel();
	SetupPlayerHUD();
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
	IconPlayer[0].setTexture(*ResourceManager::Instance()->GetTexture("HUD J1"));
	IconPlayer[1].setTexture(*ResourceManager::Instance()->GetTexture("HUD J2"));

	IconPlayer[0].setTextureRect(sf::IntRect{ 17 * 449, 0, 449, 203 });
	IconPlayer[1].setTextureRect(sf::IntRect{ 17 * 449, 0, 449, 203 });

	IconPlayer[0].setPosition(0, 0);
	IconPlayer[1].setPosition(1920 - 449, 0);

	for (int i = 0; i < 2; i++)
	{
		spRocket[i].setTexture(*ResourceManager::Instance()->GetTexture("Collect1"));
		spShockWave[i].setTexture(*ResourceManager::Instance()->GetTexture("Collect2"));
		spOilFlake[i].setTexture(*ResourceManager::Instance()->GetTexture("Collect3"));
		spInvincible[i].setTexture(*ResourceManager::Instance()->GetTexture("Collect4"));
		spSwap[i].setTexture(*ResourceManager::Instance()->GetTexture("Collect5"));
		spBumper[i].setTexture(*ResourceManager::Instance()->GetTexture("Collect6"));

		spRocket[i].setOrigin(spRocket[i].getGlobalBounds().width / 2, spRocket[i].getGlobalBounds().height / 2);
		spShockWave[i].setOrigin(spShockWave[i].getGlobalBounds().width / 2, spShockWave[i].getGlobalBounds().height / 2);
		spOilFlake[i].setOrigin(spOilFlake[i].getGlobalBounds().width / 2, spOilFlake[i].getGlobalBounds().height / 2);
		spInvincible[i].setOrigin(spInvincible[i].getGlobalBounds().width / 2, spInvincible[i].getGlobalBounds().height / 2);
		spSwap[i].setOrigin(spSwap[i].getGlobalBounds().width / 2, spSwap[i].getGlobalBounds().height / 2);
		spBumper[i].setOrigin(spBumper[i].getGlobalBounds().width / 2, spBumper[i].getGlobalBounds().height / 2);


	}
	spRocket[0].setPosition(IconPlayer[0].getPosition().x + 190, IconPlayer[0].getPosition().y + 100);
	spRocket[1].setPosition(IconPlayer[1].getPosition().x + 250, IconPlayer[1].getPosition().y + 100);
	spShockWave[0].setPosition(IconPlayer[0].getPosition().x + 190, IconPlayer[0].getPosition().y + 100);
	spShockWave[1].setPosition(IconPlayer[1].getPosition().x + 250, IconPlayer[1].getPosition().y + 100);
	spOilFlake[0].setPosition(IconPlayer[0].getPosition().x + 190, IconPlayer[0].getPosition().y + 100);
	spOilFlake[1].setPosition(IconPlayer[1].getPosition().x + 250, IconPlayer[1].getPosition().y + 100);
	spInvincible[0].setPosition(IconPlayer[0].getPosition().x + 190, IconPlayer[0].getPosition().y + 100);
	spInvincible[1].setPosition(IconPlayer[1].getPosition().x + 250, IconPlayer[1].getPosition().y + 100);
	spSwap[0].setPosition(IconPlayer[0].getPosition().x + 190, IconPlayer[0].getPosition().y + 100);
	spSwap[1].setPosition(IconPlayer[1].getPosition().x + 250, IconPlayer[1].getPosition().y + 100);
	spBumper[0].setPosition(IconPlayer[0].getPosition().x + 190, IconPlayer[0].getPosition().y + 100);
	spBumper[1].setPosition(IconPlayer[1].getPosition().x + 250, IconPlayer[1].getPosition().y + 100);
}

void HUD::Update(sf::Vector2f _viewCenter, sf::Vector2f _sizeCamera, sf::Vector2f _posP1, sf::Vector2f _posP2)
{
	//SetProgressionPlayer(_posP1, _posP2);
}

void HUD::Display(Player* _Player1, Player* _Player2)
{
	//m_actualWindow->draw(progressionNiveau);
	//m_actualWindow->draw(Player2);
	//m_actualWindow->draw(Player1);

	for (int i = 0; i < 2; i++)
	{
		m_actualWindow->draw(IconPlayer[i]);
	}

	AnimationHUD(_Player1, _Player2);

	if (HudDisplay[0] == true)
	{
		if (_Player1->GetCollectID() == e_Enum::e_Collects::ROCKET)
			m_actualWindow->draw(spRocket[0]);
		else if (_Player1->GetCollectID() == e_Enum::e_Collects::SHOCKWAVE)
			m_actualWindow->draw(spShockWave[0]);
		else if (_Player1->GetCollectID() == e_Enum::e_Collects::OILFLAKE)
			m_actualWindow->draw(spOilFlake[0]);
		else if (_Player1->GetCollectID() == e_Enum::e_Collects::LEVITATION)
			m_actualWindow->draw(spInvincible[0]);
		else if (_Player1->GetCollectID() == e_Enum::e_Collects::SWAP)
			m_actualWindow->draw(spSwap[0]);
		else if (_Player1->GetCollectID() == e_Enum::e_Collects::BUMPER)
			m_actualWindow->draw(spBumper[0]);
	}

	if (HudDisplay[1] == true)
	{
		if (_Player2->GetCollectID() == e_Enum::e_Collects::ROCKET)
			m_actualWindow->draw(spRocket[1]);
		else if (_Player2->GetCollectID() == e_Enum::e_Collects::SHOCKWAVE)
			m_actualWindow->draw(spShockWave[1]);
		else if (_Player2->GetCollectID() == e_Enum::e_Collects::OILFLAKE)
			m_actualWindow->draw(spOilFlake[1]);
		else if (_Player2->GetCollectID() == e_Enum::e_Collects::LEVITATION)
			m_actualWindow->draw(spInvincible[1]);
		else if (_Player2->GetCollectID() == e_Enum::e_Collects::SWAP)
			m_actualWindow->draw(spSwap[1]);
		else if (_Player2->GetCollectID() == e_Enum::e_Collects::BUMPER)
			m_actualWindow->draw(spBumper[1]);
	}
}

void HUD::SetProgressionLevel(sf::Vector2f _viewCenter, sf::Vector2f _sizeCamera, sf::Vector2f _posPlayer1, sf::Vector2f _posPlayer2)
{
	posProgressionNiveau = { _viewCenter.x - (progressionNiveau.getGlobalBounds().width / 2), (_viewCenter.y - (_sizeCamera.x / 5)) - (_sizeCamera.x / POS_MINI_LEVEL) };
	progressionNiveau.setPosition(posProgressionNiveau);
	progressionNiveau.setSize({ MINI_LEVEL_WIDTH * (_sizeCamera.x / CAMERA_HEIGHT_MIN), MINI_LEVEL_HEIGHT * (_sizeCamera.x / CAMERA_HEIGHT_MIN) });

	progressionPlayer1 = (_posPlayer1.x / (LEVEL_WIDTH / MINI_LEVEL_WIDTH) * (_sizeCamera.x / (LEVEL_WIDTH / 4))); // parcours du j1 relatif a la taille du mini level --> relatif au level
	progressionPlayer2 = (_posPlayer2.x / (LEVEL_WIDTH / MINI_LEVEL_WIDTH) * (_sizeCamera.x / (LEVEL_WIDTH))); // parcours du j2 relatif a la taille du mini level --> relatif au level

	Player1.setPosition({ posProgressionNiveau.x + progressionPlayer1, posProgressionNiveau.y - (_sizeCamera.x / POS_PLAYER_Y_RELATIVE_LEVEL) });
	Player1.setSize({ PLAYER_WIDTH * (_sizeCamera.x / CAMERA_HEIGHT_MIN), PLAYER_WIDTH * (_sizeCamera.x / CAMERA_HEIGHT_MIN) });

	Player2.setPosition({ posProgressionNiveau.x + progressionPlayer2, posProgressionNiveau.y - (_sizeCamera.x / POS_PLAYER_Y_RELATIVE_LEVEL) });
	Player2.setSize({ PLAYER_WIDTH * (_sizeCamera.x / CAMERA_HEIGHT_MIN), PLAYER_WIDTH * (_sizeCamera.x / CAMERA_HEIGHT_MIN) });
}

void HUD::SetProgressionPlayer(sf::Vector2f _posPlayer1, sf::Vector2f _posPlayer2)
{
	progressionPlayer1 = _posPlayer1.x / (LEVEL_WIDTH / MINI_LEVEL_WIDTH);
	progressionPlayer2 = _posPlayer2.x / (LEVEL_WIDTH / MINI_LEVEL_WIDTH);

	progressionNiveau.setPosition(sf::Vector2f((1920 / 2) - (progressionNiveau.getGlobalBounds().width / 2), POS_MINI_LEVEL_Y));
	Player1.setPosition({ progressionNiveau.getPosition().x - (Player1.getGlobalBounds().width / 2) + progressionPlayer1, POS_MINI_PLAYER_Y });
	Player2.setPosition({ progressionNiveau.getPosition().x - (Player2.getGlobalBounds().width / 2) + progressionPlayer2, POS_MINI_PLAYER_Y });
}

void HUD::AnimationHUD(Player* _Player1, Player* _Player2)
{
	if (_Player1->HasCollectible == true)
	{
		if (AnimClock[0].getElapsedTime().asMilliseconds() > 50)
		{
			if (FrameIndex[0] < 15)
				FrameIndex[0]++;
			else
				FrameIndex[0] = 15;

			AnimClock[0].restart();
		}

		IconPlayer[0].setTextureRect(sf::IntRect{ FrameIndex[0] * 449, 203, 449, 203 });

		if (FrameIndex[0] == 15)
		{
			HudDisplay[0] = true;
			m_actualWindow->draw(spIconCollect[0]);

			if (sf::Joystick::isButtonPressed(0, 1))
				FrameIndex[0] = 0;
		}
	}
	else if (_Player1->HasCollectible == false && HudDisplay[0] == true)
	{
		if (AnimClock[0].getElapsedTime().asMilliseconds() > 50)
		{
			if (FrameIndex[0] < 17)
				FrameIndex[0]++;
			else if (FrameIndex[0] == 17)
			{
				FrameIndex[0] = 17;
				HudDisplay[0] = false;
			}

			AnimClock[0].restart();
		}

		IconPlayer[0].setTextureRect(sf::IntRect{ FrameIndex[0] * 449, 0, 449, 203 });
	}


	if (_Player2->HasCollectible == true)
	{
		if (AnimClock[1].getElapsedTime().asMilliseconds() > 50)
		{
			if (FrameIndex[1] < 15)
				FrameIndex[1]++;
			else
				FrameIndex[1] = 15;

			AnimClock[1].restart();
		}

		IconPlayer[1].setTextureRect(sf::IntRect{ FrameIndex[1] * 449, 203, 449, 203 });

		if (FrameIndex[1] == 15)
		{
			HudDisplay[1] = true;
			m_actualWindow->draw(spIconCollect[1]);

			if (sf::Joystick::isButtonPressed(1, 1))
				FrameIndex[1] = 0;
		}
	}
	else if (_Player2->HasCollectible == false && HudDisplay[1] == true)
	{
		if (AnimClock[1].getElapsedTime().asMilliseconds() > 50)
		{
			if (FrameIndex[1] < 17)
				FrameIndex[1]++;
			else if (FrameIndex[1] == 17)
			{
				FrameIndex[1] = 17;
				HudDisplay[1] = false;
			}

			AnimClock[1].restart();
		}

		IconPlayer[1].setTextureRect(sf::IntRect{ FrameIndex[1] * 449, 0, 449, 203 });
	}
}