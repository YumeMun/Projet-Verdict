#include "Level_Finished.h"
#include "ResourceManager.h"
#include "GameManager.h"

Level_Finished::Level_Finished()
{
}

Level_Finished::Level_Finished(int _J1Score, int _J2Score)
{
	m_actualWindow = GameManager::Instance()->GetWindow();

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
	}
}

Level_Finished::~Level_Finished()
{
}

void Level_Finished::Update()
{
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

	ScoreText[0].setString("Score du joueur 1 : " + std::to_string(J1Score));
	ScoreText[0].setOrigin(ScoreText[0].getGlobalBounds().width / 2, 0);

	ScoreText[1].setString("Score du joueur 2 : " + std::to_string(J2Score));
	ScoreText[1].setOrigin(ScoreText[1].getGlobalBounds().width / 2, 0);

	if (sf::Joystick::isButtonPressed(0, 1))
	{
		GameManager::Instance()->LoadScene(e_Enum::e_Scene::MENU);
	}
}

void Level_Finished::Display()
{
	m_actualWindow->draw(WinText);

	for (int i = 0; i < 2; i++)
	{
		ScoreText[i].setPosition(700 + i * 550, 540);
		m_actualWindow->draw(ScoreText[i]);
	}
}

void Level_Finished::EventManager(sf::Event p_pollingEvent)
{
}
