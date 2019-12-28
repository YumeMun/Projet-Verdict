#include "SizeEditor.h"
#include "GameManager.h"
#include "ResourceManager.h"

SizeEditor::SizeEditor()
{
	std::cout << "Choix de la taille" << std::endl;

	m_actualWindow = GameManager::Instance()->GetWindow();

	LevelSelected = 1;

	EnterSizeText.setFont(*ResourceManager::Instance()->GetFont("Font"));
	EnterSizeText.setFillColor(sf::Color::White);
	EnterSizeText.setCharacterSize(40);
	EnterSizeText.setString("Choisis une taille pour ton niveau !");
	EnterSizeText.setOrigin(EnterSizeText.getGlobalBounds().width / 2, 0);
	EnterSizeText.setPosition(sf::Vector2f{ 960, 100 });

	InfosRect.setSize(sf::Vector2f{ 400, 150 });
	InfosRect.setFillColor(sf::Color::Black);
	InfosRect.setOutlineColor(sf::Color::White);
	InfosRect.setOutlineThickness(3);
	InfosRect.setOrigin(InfosRect.getGlobalBounds().width / 2, InfosRect.getGlobalBounds().height / 2);
	InfosRect.setPosition(960, 800);

	InfosText.setFont(*ResourceManager::Instance()->GetFont("Font"));
	InfosText.setCharacterSize(25);
	InfosText.setFillColor(sf::Color::White);
	InfosText.setPosition(InfosRect.getPosition().x - 180, InfosRect.getPosition().y - 40);

	for (int i = 0; i < 3; i++)
	{
		LevelIcon[i].setSize(sf::Vector2f{ 150, 150 });
		LevelIcon[i].setFillColor(sf::Color::Black);
		LevelIcon[i].setOutlineColor(sf::Color::White);
		LevelIcon[i].setOutlineThickness(3);
		LevelIcon[i].setPosition(680 + i * 200, 300);

		LevelNumero[i].setFont(*ResourceManager::Instance()->GetFont("Font"));
		LevelNumero[i].setCharacterSize(30);
		LevelNumero[i].setFillColor(sf::Color::White);
		LevelNumero[0].setString("1");
		LevelNumero[1].setString("2");
		LevelNumero[2].setString("3");
		LevelNumero[i].setPosition(750 + i * 200, 400);
	}
}

SizeEditor::~SizeEditor()
{
}

void SizeEditor::Update()
{
	if (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X) >= 50 && SelectionTimer.getElapsedTime().asMilliseconds() > 300)
	{
		if(LevelSelected < 3)
		LevelSelected++;

		SelectionTimer.restart();
	}
	else if (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X) <= -50 && SelectionTimer.getElapsedTime().asMilliseconds() > 300)
	{
		if(LevelSelected > 1)
		LevelSelected--;

		SelectionTimer.restart();
	}

	if (LevelSelected == 1)
	{
		LevelIcon[0].setOutlineColor(sf::Color::Red);
		LevelNumero[0].setFillColor(sf::Color::Red);

		LevelIcon[1].setOutlineColor(sf::Color::White);
		LevelNumero[1].setFillColor(sf::Color::White);

		LevelIcon[2].setOutlineColor(sf::Color::White);
		LevelNumero[2].setFillColor(sf::Color::White);

		InfosText.setString("Longueur : Courte\nDurée estimée : 40 secondes");
	}
	else if (LevelSelected == 2)
	{
		LevelIcon[0].setOutlineColor(sf::Color::White);
		LevelNumero[0].setFillColor(sf::Color::White);

		LevelIcon[1].setOutlineColor(sf::Color::Red);
		LevelNumero[1].setFillColor(sf::Color::Red);

		LevelIcon[2].setOutlineColor(sf::Color::White);
		LevelNumero[2].setFillColor(sf::Color::White);

		InfosText.setString("Longueur : Moyenne\nDurée estimée : 1 minute");
	}
	else if (LevelSelected == 3)
	{
		LevelIcon[0].setOutlineColor(sf::Color::White);
		LevelNumero[0].setFillColor(sf::Color::White);

		LevelIcon[1].setOutlineColor(sf::Color::White);
		LevelNumero[1].setFillColor(sf::Color::White);

		LevelIcon[2].setOutlineColor(sf::Color::Red);
		LevelNumero[2].setFillColor(sf::Color::Red);

		InfosText.setString("Longueur : Grande\nDurée estimée : 1 minute 30");
	}

	if (sf::Joystick::isButtonPressed(0, 0) && SelectionTimer.getElapsedTime().asMilliseconds() > 300)
	{
		if (LevelSelected == 1)
		{
			GameManager::Instance()->m_ActualScene = new LevelEditor((38400 / 64) + 1, (2160 / 64) + 1, "");
		}
		else if (LevelSelected == 2)
		{
			GameManager::Instance()->m_ActualScene = new LevelEditor((57600 / 64) + 1, (2160 / 64) + 1, "");
		}
		else if (LevelSelected == 3)
		{
			GameManager::Instance()->m_ActualScene = new LevelEditor((76800 / 64) + 1, (2160 / 64) + 1, "");
		}
	}
	else if (sf::Joystick::isButtonPressed(0, 1) && SelectionTimer.getElapsedTime().asMilliseconds() > 300)
	{
		GameManager::Instance()->LoadScene(e_Enum::e_Scene::CHOOSELEVELEDITOR);
	}
}

void SizeEditor::Display()
{
	m_actualWindow->draw(EnterSizeText);
	m_actualWindow->draw(InfosRect);
	m_actualWindow->draw(InfosText);

	for (int i = 0; i < 3; i++)
	{
		m_actualWindow->draw(LevelIcon[i]);
		m_actualWindow->draw(LevelNumero[i]);
	}
}

void SizeEditor::EventManager(sf::Event p_pollingEvent)
{
}