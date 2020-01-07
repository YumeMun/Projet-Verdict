#include "Level_Finished.h"
#include "ResourceManager.h"
#include "GameManager.h"

Level_Finished::Level_Finished()
{
}

Level_Finished::Level_Finished(int _J1Score, int _J2Score)
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
	}

	posElement = { 1920 / 2, 1080 / 2 };

	for (int i = 0; i < 2; i++)
	{
		spPodium[i].setTexture(*ResourceManager::Instance()->GetTexture("RT")); //sample
	}

	spPodium[0].setPosition(posElement.x - 200, posElement.y);
	spPodium[0].setPosition(posElement.x + 200, posElement.y + 300);

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
		transition->ResetTransition();
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

	if (!transition->GetIsTransitionBackDone())
	{
		transition->DrawTransition();
	}

	for (int i = 0; i < 2; i++)
	{
		m_actualWindow->draw(spPodium[i]);
	}
}

void Level_Finished::EventManager(sf::Event p_pollingEvent)
{
}

void Level_Finished::GetScoreValue(Player* _player1, Player* _player2)
{
	scoreTimeFirst[0] = _player1->Score;
	scoreTimeFirst[1] = _player2->Score;

	scoreIsArrivedFirst[0] = _player1->scoreIsArrivedFirst;
	scoreIsArrivedFirst[1] = _player2->scoreIsArrivedFirst;

	scoreHitTrap[0] = _player1->scoreHitTrap;
	scoreHitTrap[1] = _player2->scoreHitTrap;

	scoreFall[0] = _player1->scoreFall;
	scoreFall[1] = _player2->scoreFall;

	std::cout << "score temps passé 1er j1 :" << scoreTimeFirst[0] << std::endl;
	std::cout << "score arrivé 1er j1 :" << scoreIsArrivedFirst[0] << std::endl;
	std::cout << "score hit pieges j1 :" << scoreHitTrap[0] << std::endl;
	std::cout << "score chutes j1 :" << scoreFall[0] << std::endl;

	std::cout << "score temps passé 1er j2 :" << scoreTimeFirst[1] << std::endl;
	std::cout << "score arrivé 1er j2 :" << scoreIsArrivedFirst[1] << std::endl;
	std::cout << "score hit pieges j2 :" << scoreHitTrap[1] << std::endl;
	std::cout << "score chutes j2 :" << scoreFall[1] << std::endl;
}
