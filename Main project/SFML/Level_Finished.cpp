#include "Level_Finished.h"
#include "ResourceManager.h"
#include "GameManager.h"

Level_Finished::Level_Finished()
{
}

Level_Finished::Level_Finished(int _J1Score, int _J2Score, Player* _player1, Player* _player2, int _skinJ1, int _skinJ2)
{
	m_actualWindow = GameManager::Instance()->GetWindow();

	transition = new Transition({ 0, 0 }, { 0, 1080 / 2 });

	J1Score = _J1Score;
	J2Score = _J2Score;

	WinText.setFont(*ResourceManager::Instance()->GetFont("Font"));
	WinText.setCharacterSize(50);
	WinText.setFillColor(sf::Color::Green);

	for (int i = 0; i < 2; i++)
	{
		ScoreText[i].setFont(*ResourceManager::Instance()->GetFont("Font"));
		ScoreText[i].setCharacterSize(40);
		ScoreText[i].setFillColor(sf::Color::White);

		isPlayerText[i].setFont(*ResourceManager::Instance()->GetFont("Font"));
		isPlayerText[i].setCharacterSize(40);
		isPlayerText[i].setFillColor(sf::Color::White);
	}

	GetScoreValue(_player1, _player2);

	posElement[0] = { (1920 / 2) - 200, 1080 - 75 };
	posElement[1] = { (1920 / 2) + 200, 1080 - 75 };

	spPlayer[0].setTexture(*ResourceManager::Instance()->GetTexture("Player1_Colo" + std::to_string(_skinJ1)));
	spPlayer[1].setTexture(*ResourceManager::Instance()->GetTexture("Player2_Colo" + std::to_string(_skinJ2)));
	rectPlayer[0] = {0, 0, 360, 135};
	rectPlayer[1] = {0, 0, 372, 150};

	for (int i = 0; i < 2; i++)
	{
		spPodium[i].setTexture(*ResourceManager::Instance()->GetTexture("Bras Menu")); //sample
		originElement = { spPodium[0].getGlobalBounds().width / 2,  0 };
		spPodium[i].setPosition(posElement[i]);
		spPodium[i].setOrigin(originElement);

		spPlayer[i].setTextureRect(rectPlayer[i]);
		spPlayer[i].setOrigin(spPlayer[i].getGlobalBounds().width / 2, spPlayer[i].getGlobalBounds().height);
		spPlayer[i].setPosition(spPodium[i].getPosition());
		scoreFinal[i] = 0;
	}

	spLogo.setTexture(*ResourceManager::Instance()->GetTexture("victoire")); //sample
	rectLogo = { 0, 0, 414, 402 };
	spLogo.setTextureRect(rectLogo);

	posLogo[0] = {1920 / 2 - (500 + spLogo.getGlobalBounds().width), 600};
	posLogo[1] = {1920 / 2 + 500, 600};
	posLogo[2] = {1920 / 2, 400 };

	for (int i = 0; i < 4; i++)
		isScoreStep[i] = false;

	isScoreStep[0] = true;

	countdownStart.restart();
	timerPause.restart();
}

Level_Finished::~Level_Finished()
{
}

void Level_Finished::Update()
{
	if (!transition->GetIsTransitionBackDone())
	{
		transition->UpdateBack();
	}

	if (countdownStart.getElapsedTime().asSeconds() > 2)
		isUpdatable = true;
	if (isUpdatable)
		UpdatePodium();

	ScoreText[0].setPosition(200, 500);
	ScoreText[1].setPosition(1920 - 200, 500);

	isPlayerText[0].setPosition(200, 600);
	isPlayerText[1].setPosition(1920 - 200, 600);

	if (J1Score > J2Score)
	{
		WinText.setString("Joueur 1 a gagné !");
		WinText.setOrigin(WinText.getGlobalBounds().width / 2, 0);
		WinText.setPosition(960, 200);
	}
	else if (J1Score < J2Score)
	{
		WinText.setString("Joueur 2 a gagné !");
		WinText.setOrigin(WinText.getGlobalBounds().width / 2, 0);
		WinText.setPosition(960, 200);
	}
	else if (J1Score == J2Score)
	{
		WinText.setString("Egalité !");
		WinText.setOrigin(WinText.getGlobalBounds().width / 2, 0);
		WinText.setPosition(960, 200);
	}

	ScoreText[0].setString("Score joueur 1 :");
	isPlayerText[0].setString(std::to_string(scoreFinal[0]));
	ScoreText[0].setOrigin(ScoreText[0].getGlobalBounds().width / 2, 0);

	ScoreText[1].setString("Score joueur 2 :");
	isPlayerText[1].setString(std::to_string(scoreFinal[1]));
	ScoreText[1].setOrigin(ScoreText[1].getGlobalBounds().width / 2, 0);

	if (sf::Joystick::isButtonPressed(0, 1))
	{
		transition->ResetTransition();
		GameManager::Instance()->LoadScene(e_Enum::e_Scene::MENU);
	}
}

void Level_Finished::Display()
{
	if (isScoreEnd)
	{
		m_actualWindow->draw(WinText);
		m_actualWindow->draw(spLogo);
	}

	for (int i = 0; i < 2; i++)
	{
		m_actualWindow->draw(ScoreText[i]);
		m_actualWindow->draw(isPlayerText[i]);
	}


	for (int i = 0; i < 2; i++)
	{
		m_actualWindow->draw(spPodium[i]);
		m_actualWindow->draw(spPlayer[i]);
	}

	if (!transition->GetIsTransitionBackDone())
		transition->DrawTransition();
}

void Level_Finished::EventManager(sf::Event p_pollingEvent)
{
}

void Level_Finished::GetScoreValue(Player* _player1, Player* _player2)
{
	scoreTimeFirst[0] = _player1->Score; //+ 300;
	scoreTimeFirst[1] = _player2->Score; //+ 100;

	scoreIsArrivedFirst[0] = _player1->scoreIsArrivedFirst;
	scoreIsArrivedFirst[1] = _player2->scoreIsArrivedFirst;

	scoreHitTrap[0] = _player1->scoreHitTrap; //+ 100;
	scoreHitTrap[1] = _player2->scoreHitTrap; //+ 50;

	scoreFall[0] = _player1->scoreFall; //+ 40;
	scoreFall[1] = _player2->scoreFall; //+ 60;

	std::cout << "score temps passe 1er j1 :" << scoreTimeFirst[0] << std::endl;
	std::cout << "score arrive 1er j1 :" << scoreIsArrivedFirst[0] << std::endl;
	std::cout << "score hit pieges j1 :" << scoreHitTrap[0] << std::endl;
	std::cout << "score chutes j1 :" << scoreFall[0] << std::endl;

	std::cout << "score temps passe 1er j2 :" << scoreTimeFirst[1] << std::endl;
	std::cout << "score arrive 1er j2 :" << scoreIsArrivedFirst[1] << std::endl;
	std::cout << "score hit pieges j2 :" << scoreHitTrap[1] << std::endl;
	std::cout << "score chutes j2 :" << scoreFall[1] << std::endl;

	for (int i = 0; i < 2; i++)
	{
		scoreTimeFirst[i];
		scoreIsArrivedFirst[i];
		scoreHitTrap[i];
		scoreFall[i];
	}
}

void Level_Finished::UpdatePodium()
{
	if (timerPause.getElapsedTime().asMilliseconds() > 800)
	{
		if (isScoreStep[0])
		{
			if (scoreTimeFirst[0] <= 0 && scoreTimeFirst[1] <= 0)
			{
				isScoreStep[0] = false;
				isScoreStep[1] = true;
				timerPause.restart();
			}
			else
			{
				std::cout << "test 0 " << std::endl;
				for (int i = 0; i < 2; i++)
				{
					if (scoreTimeFirst[i] > 0)
					{
						scoreFinal[i] += SPEED_PODIUM;
						scoreTimeFirst[i] -= SPEED_PODIUM;
					}
				}
			}
		}
	
		if (isScoreStep[1])
		{
			if (scoreIsArrivedFirst[0] <= 0 && scoreIsArrivedFirst[1] <= 0)
			{
				isScoreStep[2] = true;
				isScoreStep[1] = false;
				timerPause.restart();
			}
			else
			{
				std::cout << "test 1" << std::endl;
				for (int i = 0; i < 2; i++)
				{
					if (scoreIsArrivedFirst[i] > 0)
					{
						scoreFinal[i] += SPEED_PODIUM;
						scoreIsArrivedFirst[i] -= SPEED_PODIUM;
					}
				}
			}
		}

		if (isScoreStep[2])
		{
			if (scoreFall[0] <= 0 && scoreFall[1] <= 0)
			{
				isScoreStep[3] = true;
				isScoreStep[2] = false;
				timerPause.restart();
			}
			else
			{
				std::cout << "test 2" << std::endl;
				for (int i = 0; i < 2; i++)
				{
					if (scoreFall[i] > 0)
					{
						scoreFinal[i] -= SPEED_PODIUM;
						scoreFall[i] -= SPEED_PODIUM;

					}
				}
			}
		}

		if (!isScoreEnd)
		{
			if (isScoreStep[3])
			{
				if (scoreHitTrap[0] <= 0 && scoreHitTrap[1] <= 0)
				{
					isScoreEnd = true;
					isScoreStep[3] = false;
					timerPause.restart();
				}
				else
				{
					std::cout << "test 3" << scoreFinal[0] << std::endl;
					for (int i = 0; i < 2; i++)
					{
						if (scoreHitTrap[i] > 0)
						{
							scoreFinal[i] -= SPEED_PODIUM;
							scoreHitTrap[i] -= SPEED_PODIUM;

						}
					}
				}
			}
		}
	

		if (!isScoreEnd)
		{
			for (int i = 0; i < 2; i++)
			{
				posElement[i].y = -scoreFinal[i];

				if (scoreFinal[i] < 0)
				{
					scoreFinal[i] = 0;
				}
				spPodium[i].setPosition((posElement[i].x), (posElement[i].y + 800));
				spPlayer[i].setPosition(spPodium[i].getPosition());
				std::cout << i << " : pos : " << spPodium[i].getPosition().y << std::endl;
			}
		}
		else
		{
			if (scoreFinal[0] > scoreFinal[1])
				spLogo.setPosition(posLogo[0]);
			else if (scoreFinal[1] > scoreFinal[0])
				spLogo.setPosition(posLogo[1]);
			else if (scoreFinal[1] == scoreFinal[0])
				spLogo.setPosition(posLogo[2]);

			timerLogo.restart();

		}

		if (timerLogo.getElapsedTime().asMilliseconds() > 60)
		{
			if (frameIndex < 19)
				frameIndex++;
			else
			{
				frameIndex = 0;
				rectLogo.left = 19 * rectLogo.width;
			}

			rectLogo.left = frameIndex * rectLogo.width;
			timerLogo.restart();
		}
	}
}
