#include "LevelSelector.h"
#include "GameManager.h"
#include "ResourceManager.h"

LevelSelector::LevelSelector()
{
	std::cout << "LevelSelector constructor" << std::endl;

	m_actualWindow = GameManager::Instance()->GetWindow();

	Setup();
}

LevelSelector::~LevelSelector()
{
}

void LevelSelector::Update()
{
	if (LeftPressed == true)
	{
		m_LevelSelector[m_MenuChoice - 1].move(50, 0);
		m_LevelSelector[m_MenuChoice].move(50, 0);

		if (m_LevelSelector[m_MenuChoice - 1].getPosition().x >= 560)
		{
			m_LevelSelector[m_MenuChoice - 1].setPosition(560, 140);
			LeftPressed = false;
		}
	}

	if (RightPressed == true)
	{
		m_LevelSelector[m_MenuChoice - 1].move(-50, 0);
		m_LevelSelector[m_MenuChoice - 2].move(-50, 0);

		if (m_LevelSelector[m_MenuChoice - 1].getPosition().x <= 560)
		{
			m_LevelSelector[m_MenuChoice - 1].setPosition(560, 140);
			RightPressed = false;
		}
	}
}

void LevelSelector::Display()
{
	for (int i = 0; i < m_LevelSelector.size(); i++)
	{
		m_actualWindow->draw(m_LevelSelector[i]);
	}

	m_Level.setString("Niveau " + std::to_string(m_MenuChoice));
	m_actualWindow->draw(m_Level);

	m_actualWindow->draw(spBoutonRetour);
}

void LevelSelector::Setup()
{
	m_NbLevel = 2;

	m_Level.setFont(*ResourceManager::Instance()->GetFont("Font"));
	m_Level.setCharacterSize(40);
	m_Level.setFillColor(sf::Color::White);
	m_Level.setPosition(900, 950);

	int x = 0;
	for (int i = 1; i <= m_NbLevel; i++)
	{
		m_shape.setSize({ 800, 800 });
		m_shape.setFillColor(sf::Color::White);
		m_shape.setPosition(560 + x, 140);
		m_LevelSelector.push_back(m_shape);
		x = 1360;
	}

}

void LevelSelector::EventManager(sf::Event p_pollingEvent)
{
	if (m_Clock.getElapsedTime().asSeconds() >= 0.5)
	{
		if (sf::Joystick::getAxisPosition(0, sf::Joystick::X) < -50.f)
		{
			if (m_MenuChoice != 1)
			{
				m_MenuChoice = m_MenuChoice - 1;
				LeftPressed = true;
			}

			m_Clock.restart();
		}
		if (sf::Joystick::getAxisPosition(0, sf::Joystick::X) > 50.f)
		{
			if (m_MenuChoice != m_NbLevel)
			{
				m_MenuChoice = m_MenuChoice + 1;
				RightPressed = true;
			}
			m_Clock.restart();
		}

		if (sf::Joystick::isButtonPressed(0, 0))
		{
			GameManager::Instance()->LoadScene(e_Enum::e_Scene::PLAYERSELECTOR);
		}
		else if (sf::Joystick::isButtonPressed(0, 1))
		{
			GameManager::Instance()->LoadScene(e_Enum::e_Scene::MENU);
		}
	}
}
