#include "LevelSelector.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "dirent.h"

LevelSelector::LevelSelector()
{
	std::cout << "LevelSelector constructor" << std::endl;

	m_actualWindow = GameManager::Instance()->GetWindow();

	ObjSeparator = ".txt";
	LoadLevels();

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
	m_actualWindow->draw(spBackground);

	for (int i = 0; i < m_LevelSelector.size(); i++)
	{
		m_actualWindow->draw(m_LevelSelector[i]);

		if (i == m_MenuChoice - 1)
			m_actualWindow->draw(LevelNameText[i]);
	}

	m_actualWindow->draw(spBoutonRetour);
}

void LevelSelector::Setup()
{
	int x = 0;
	for (int i = 1; i <= FilesNumber; i++)
	{
		std::cout << "ok" << std::endl;
		m_shape.setSize({ 800, 800 });
		m_shape.setFillColor(sf::Color::White);
		m_shape.setPosition(560 + x, 140);
		m_LevelSelector.push_back(m_shape);
		x = 1360;
	}

	spBackground.setTexture(*ResourceManager::Instance()->GetTexture("Background interface"));
	spBackground.setColor(sf::Color{ 100, 100, 100, 255 });
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
			if (m_MenuChoice != FilesNumber)
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

void LevelSelector::LoadLevels()
{
	DIR* rep;
	std::string LoadNames;

	rep = opendir("Ressources/Sauvegardes");
	struct dirent* lecture;

	while ((lecture = readdir(rep)))
	{
		LoadNames += lecture->d_name;
	}

	static int pos = 0;
	std::string data;

	LoadNames.erase(0, 3);

	for (int i = 0; i < 10; i++)
	{
		pos = LoadNames.find(ObjSeparator);
		data = LoadNames.substr(0, pos);
		LevelName[i] = data;
		LoadNames.erase(0, pos + ObjSeparator.length());

		LevelNameText[i].setFont(*ResourceManager::Instance()->GetFont("Font"));
		LevelNameText[i].setFillColor(sf::Color::Black);
		LevelNameText[i].setCharacterSize(40);
		LevelNameText[i].setString(LevelName[i]);
		LevelNameText[i].setPosition(900, 960);

		if (LevelName[i] != "")
		{
			FilesNumber++;
		}

		std::cout << "Nom du fichier : " << LevelName[i] << std::endl;
		std::cout << "Nombre de fichiers : " << FilesNumber << std::endl;
	}
}