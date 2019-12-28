#include "Menu.h"
#include "GameManager.h"
#include "ResourceManager.h"

Menu::Menu()
{
	std::cout << "Menu constructor" << std::endl;

	m_actualWindow = GameManager::Instance()->GetWindow();

	m_NewGame.setFont(*ResourceManager::Instance()->GetFont("Font"));
	m_NewGame.setCharacterSize(70);
	m_NewGame.setFillColor(sf::Color::White);
	m_NewGame.setString("Nouvelle Partie");
	m_NewGame.setString("Jouer");
	m_NewGame.setPosition(300, 300);

	m_LevelEditor.setFont(*ResourceManager::Instance()->GetFont("Font"));
	m_LevelEditor.setCharacterSize(70);
	m_LevelEditor.setFillColor(sf::Color::White);
	m_LevelEditor.setString("Éditeur de niveau");
	m_LevelEditor.setPosition(300, 400);

	m_Option.setFont(*ResourceManager::Instance()->GetFont("Font"));
	m_Option.setCharacterSize(70);
	m_Option.setFillColor(sf::Color::White);
	m_Option.setString("Contrôles");
	m_Option.setPosition(300, 500);

	m_Commande.setFont(*ResourceManager::Instance()->GetFont("Font"));
	m_Commande.setCharacterSize(70);
	m_Commande.setFillColor(sf::Color::White);
	m_Commande.setString("Options");
	m_Commande.setPosition(300, 600);

	m_Quit.setFont(*ResourceManager::Instance()->GetFont("Font"));
	m_Quit.setCharacterSize(70);
	m_Quit.setFillColor(sf::Color::White);
	m_Quit.setString("Quitter");
	m_Quit.setPosition(300, 700);
}

Menu::~Menu()
{
}

void Menu::Update()
{
	if (m_MenuChoice == 1)
		m_NewGame.setFillColor(sf::Color::Red);
	else
		m_NewGame.setFillColor(sf::Color::White);

	if (m_MenuChoice == 2)
		m_LevelEditor.setFillColor(sf::Color::Red);
	else
		m_LevelEditor.setFillColor(sf::Color::White);

	if (m_MenuChoice == 3)
		m_Option.setFillColor(sf::Color::Red);
	else
		m_Option.setFillColor(sf::Color::White);

	if (m_MenuChoice == 4)
		m_Commande.setFillColor(sf::Color::Red);
	else
		m_Commande.setFillColor(sf::Color::White);

	if (m_MenuChoice == 5)
		m_Quit.setFillColor(sf::Color::Red);
	else
		m_Quit.setFillColor(sf::Color::White);
}

void Menu::Display()
{
	m_actualWindow->draw(m_NewGame);
	m_actualWindow->draw(m_LevelEditor);
	m_actualWindow->draw(m_Option);
	m_actualWindow->draw(m_Quit);
	m_actualWindow->draw(m_Commande);
}

void Menu::EventManager(sf::Event p_pollingEvent)
{
	if (m_Clock.getElapsedTime().asSeconds() >= 0.3)
	{
		if (sf::Joystick::isButtonPressed(0, 0))
		{
			if (m_MenuChoice == 1)
				GameManager::Instance()->LoadScene(e_Enum::e_Scene::LEVELSELECTOR);
			if (m_MenuChoice == 2)
				GameManager::Instance()->LoadScene(e_Enum::e_Scene::CHOOSELEVELEDITOR);
			if (m_MenuChoice == 3)
				GameManager::Instance()->LoadScene(e_Enum::e_Scene::OPTIONS);
			if (m_MenuChoice == 4)
				std::cout << "Options"; // Sprite pop-up des différents controles
			if (m_MenuChoice == 5)
				m_actualWindow->close();
		}

		if (sf::Joystick::getAxisPosition(0, sf::Joystick::Y) < -50.f)
		{
			if (m_MenuChoice != 1)
				m_MenuChoice = m_MenuChoice - 1;
			else
				m_MenuChoice = 5;
			m_Clock.restart();
		}
		if (sf::Joystick::getAxisPosition(0, sf::Joystick::Y) > 50.f)
		{
			if (m_MenuChoice != 5)
				m_MenuChoice = m_MenuChoice + 1;
			else
				m_MenuChoice = 1;
			m_Clock.restart();
		}
	}
}