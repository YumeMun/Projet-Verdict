#include "Level_Finished.h"
#include "ResourceManager.h"
#include "GameManager.h"

Level_Finished::Level_Finished()
{
}

Level_Finished::Level_Finished(int _J1Score, int _J2Score, Player* _player1, Player* _player2, int _skinJ1, int _skinJ2, std::string _LevelName)
{
	m_actualWindow = GameManager::Instance()->GetWindow();

	transition = new Transition({ 0, 0 }, { 0, 1080 / 2 });

	J1Score = _J1Score;
	J2Score = _J2Score;

	SkinJ1 = _skinJ1;
	SkinJ2 = _skinJ2;

	LevelName = _LevelName;

	WinText.setFont(*ResourceManager::Instance()->GetFont("Font"));
	WinText.setCharacterSize(50);
	WinText.setFillColor(sf::Color::White);

	spBackground.setTexture(*ResourceManager::Instance()->GetTexture("Background victoire"));
	spContour.setTexture(*ResourceManager::Instance()->GetTexture("Contour victoire"));
	spLight.setTexture(*ResourceManager::Instance()->GetTexture("Lumière victoire"));
	spFlèche.setTexture(*ResourceManager::Instance()->GetTexture("Flèche menu"));

	for (int i = 0; i < 3; i++)
	{
		spButton[i].setTexture(*ResourceManager::Instance()->GetTexture("Menu bouton non sélectionné"));
		spButton[i].setPosition(1350, 450 + i * 100);

		ButtonText[i].setFont(*ResourceManager::Instance()->GetFont("Font"));
		ButtonText[i].setCharacterSize(35);
		ButtonText[i].setFillColor(sf::Color::White);
		ButtonText[i].setPosition(1370, 450 + i * 100);

		ButtonText[0].setString("Rejouer");
		ButtonText[1].setString("Choisir un autre niveau");
		ButtonText[2].setString("Retourner au menu");
	}

	for (int i = 0; i < 2; i++)
	{
		ScoreText[i].setFont(*ResourceManager::Instance()->GetFont("Font"));
		ScoreText[i].setCharacterSize(50);
		ScoreText[i].setFillColor(sf::Color::White);

		isPlayerText[i].setFont(*ResourceManager::Instance()->GetFont("Font"));
		isPlayerText[i].setCharacterSize(50);
		isPlayerText[i].setFillColor(sf::Color::White);
	}

	GetScoreValue(_player1, _player2);

	posElement[0] = { (1920 / 2) - 200, 1080 - 75 };
	posElement[1] = { (1920 / 2) + 200, 1080 - 75 };

	spPlayer[0].setTexture(*ResourceManager::Instance()->GetTexture("Player1_Colo" + std::to_string(_skinJ1)));
	spPlayer[1].setTexture(*ResourceManager::Instance()->GetTexture("Player2_Colo" + std::to_string(_skinJ2)));
	rectPlayer[0] = { 0, 0, 360, 135 };
	rectPlayer[1] = { 0, 0, 372, 150 };

	for (int i = 0; i < 2; i++)
	{
		spPodium[i].setTexture(*ResourceManager::Instance()->GetTexture("Podium"));
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

	ScoreText[0].setPosition(400, 200);
	ScoreText[1].setPosition(1920 - 400, 200);

	isPlayerText[0].setPosition(380, 350);
	isPlayerText[1].setPosition(1920 - 400, 350);

	isPlayerText[0].setOrigin(isPlayerText[0].getGlobalBounds().width / 2, isPlayerText[0].getGlobalBounds().height / 2);
	isPlayerText[1].setOrigin(isPlayerText[1].getGlobalBounds().width / 2, isPlayerText[1].getGlobalBounds().height / 2);

	posLogo[0] = { 200, 700 };
	posLogo[1] = { 1920 - 500, 700 };
	posLogo[2] = { 1920 / 2, 400 };

	if (J1Score > J2Score)
	{
		WinText.setString("Joueur 1 a gagné !");
		WinText.setOrigin(WinText.getGlobalBounds().width / 2, 0);
		WinText.setPosition(960, 100);
		spLight.setPosition(spPlayer[0].getPosition().x - 350, 0);
	}
	else if (J1Score < J2Score)
	{
		WinText.setString("Joueur 2 a gagné !");
		WinText.setOrigin(WinText.getGlobalBounds().width / 2, 0);
		WinText.setPosition(960, 100);
		spLight.setPosition(spPlayer[1].getPosition().x - 350, 0);
	}
	else if (J1Score == J2Score)
	{
		WinText.setString("Egalité !");
		WinText.setOrigin(WinText.getGlobalBounds().width / 2, 0);
		WinText.setPosition(960, 100);
	}

	ScoreText[0].setString("Score du joueur 1 :");
	isPlayerText[0].setString(std::to_string(scoreFinal[0]));
	ScoreText[0].setOrigin(ScoreText[0].getGlobalBounds().width / 2, 0);

	ScoreText[1].setString("Score du joueur 2 :");
	isPlayerText[1].setString(std::to_string(scoreFinal[1]));
	ScoreText[1].setOrigin(ScoreText[1].getGlobalBounds().width / 2, 0);

	if (sf::Joystick::isButtonPressed(0, 1))
	{
		transition->ResetTransition();
		GameManager::Instance()->LoadScene(e_Enum::e_Scene::MENU);
	}

	if (isScoreEnd)
	{
		if (m_Clock.getElapsedTime().asSeconds() >= 0.3)
		{
			if (sf::Joystick::isButtonPressed(0, 0))
			{
				if (Selection == 1)
					GameManager::Instance()->m_ActualScene = new Jeu(LevelName, SkinJ1, SkinJ2);
				else if (Selection == 2)
					GameManager::Instance()->LoadScene(e_Enum::e_Scene::LEVELSELECTOR);
				else if (Selection == 3)
					GameManager::Instance()->LoadScene(e_Enum::e_Scene::MENU);
			}


			if (sf::Joystick::getAxisPosition(0, sf::Joystick::Y) < -50.f)
			{
				if (Selection != 1)
					Selection = Selection - 1;
				else
					Selection = 3;
				m_Clock.restart();
			}
			if (sf::Joystick::getAxisPosition(0, sf::Joystick::Y) > 50.f)
			{
				if (Selection != 3)
					Selection = Selection + 1;
				else
					Selection = 1;
				m_Clock.restart();
			}
		}

		if (Selection == 1)
		{
			ButtonText[0].setPosition(1410, 450);
			ButtonText[1].setPosition(1370, 550);
			ButtonText[2].setPosition(1370, 650);
		}
		else if (Selection == 2)
		{
			ButtonText[0].setPosition(1370, 450);
			ButtonText[1].setPosition(1410, 550);
			ButtonText[2].setPosition(1370, 650);
		}
		else if (Selection == 3)
		{
			ButtonText[0].setPosition(1370, 450);
			ButtonText[1].setPosition(1370, 550);
			ButtonText[2].setPosition(1410, 650);
		}
	}
}

void Level_Finished::Display()
{
	m_actualWindow->draw(spBackground);
	m_actualWindow->draw(spContour);

	for (int i = 0; i < 2; i++)
	{
		m_actualWindow->draw(spPodium[i]);
		m_actualWindow->draw(spPlayer[i]);
	}

	if (isScoreEnd)
	{
		if (J1Score != J2Score)
		{
			m_actualWindow->draw(spLight);
		}

		m_actualWindow->draw(WinText);

		if (AnimLogo.getElapsedTime().asMilliseconds() > 150)
		{
			if (FrameIndexLogo < 19)
				FrameIndexLogo++;
			else
				FrameIndexLogo = 19;

			spLogo.setTextureRect(sf::IntRect{ FrameIndexLogo * 414, 0, 414, 402 });
		}

		if (J1Score != J2Score)
		{
			m_actualWindow->draw(spLogo);
		}

		for (int i = 0; i < 3; i++)
		{
			if (i == Selection - 1)
			{
				spButton[i].setTexture(*ResourceManager::Instance()->GetTexture("Menu bouton sélectionné"));
				spFlèche.setPosition(spButton[i].getPosition().x + 10, spButton[i].getPosition().y + 7);
			}
			else
			{
				spButton[i].setTexture(*ResourceManager::Instance()->GetTexture("Menu bouton non sélectionné"));
			}
			m_actualWindow->draw(spButton[i]);
			m_actualWindow->draw(ButtonText[i]);
			m_actualWindow->draw(spFlèche);
		}
	}

	for (int i = 0; i < 2; i++)
	{
		m_actualWindow->draw(ScoreText[i]);
		m_actualWindow->draw(isPlayerText[i]);
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


	for (int i = 0; i < 2; i++)
	{
		scoreTimeFirst[i];
		scoreIsArrivedFirst[i];
		scoreHitTrap[i];
		scoreFall[i];

		//scoreFinalDivide[i] = scoreFinal[i] / FACTOR_DIVIDE;
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
				if (scoreFinal[i] < 0)
				{
					scoreFinal[i] = 0;
				}

				scoreFinalDivide[i] = scoreFinal[i] / FACTOR_DIVIDE;
				posElement[i].y = -scoreFinalDivide[i];

				spPodium[i].setPosition((posElement[i].x), (posElement[i].y + 800));
				spPlayer[i].setPosition(spPodium[i].getPosition());
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
