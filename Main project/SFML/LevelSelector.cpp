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

		LevelNameText[m_MenuChoice - 1].move(50, 0);
		LevelNameText[m_MenuChoice].move(50, 0);

		if (m_LevelSelector[m_MenuChoice - 1].getPosition().x >= 960)
		{
			m_LevelSelector[m_MenuChoice - 1].setPosition(960, 540);
			LevelNameText[m_MenuChoice - 1].setPosition(540, 120);
			LeftPressed = false;
		}
	}

	if (RightPressed == true)
	{
		m_LevelSelector[m_MenuChoice - 1].move(-50, 0);
		m_LevelSelector[m_MenuChoice - 2].move(-50, 0);

		LevelNameText[m_MenuChoice - 1].move(-50, 0);
		LevelNameText[m_MenuChoice - 2].move(-50, 0);

		if (m_LevelSelector[m_MenuChoice - 1].getPosition().x <= 960)
		{
			m_LevelSelector[m_MenuChoice - 1].setPosition(960, 540);
			LevelNameText[m_MenuChoice - 1].setPosition(540, 120);
			RightPressed = false;
		}
	}
}

void LevelSelector::Display()
{
	m_actualWindow->draw(spBackground);

	if (RightPressed == false && LeftPressed == false)
	{
		m_actualWindow->draw(spButton);
	}

	for (int i = 0; i < m_LevelSelector.size(); i++)
	{
		m_actualWindow->draw(m_LevelSelector[i]);

		if (LevelName[i] == "0Niveau1" || LevelName[i] == "0Niveau2")
			LevelName[i] = LevelName[i].substr(LevelName[i].find_first_not_of('0'));

		LevelNameText[i].setString(LevelName[i]);
		m_actualWindow->draw(LevelNameText[i]);
	}

	if (RightPressed == false && LeftPressed == false)
	{
		for (int i = 0; i < 2; i++)
		{
			if (m_MenuChoice != FilesNumber)
				m_actualWindow->draw(spFlèches[0]);

			if (m_MenuChoice != 1)
				m_actualWindow->draw(spFlèches[1]);
		}
	}

	if (RightPressed == false && LeftPressed == false)
	{
		m_actualWindow->draw(spVignette);
	}

	m_actualWindow->draw(spBoutonRetour);
}

void LevelSelector::Setup()
{
	int x = 0;
	for (int i = 1; i <= FilesNumber; i++)
	{
		spLevelSelection.setTexture(*ResourceManager::Instance()->GetTexture("Background sélection niveau"));
		spLevelSelection.setOrigin(spLevelSelection.getGlobalBounds().width / 2, spLevelSelection.getGlobalBounds().height / 2);
		spLevelSelection.setPosition(960 + x, 540);

		m_LevelSelector.push_back(spLevelSelection);

		LevelNameText[i - 1].setPosition(540 + x, 120);

		x = 1360;
	}

	spBackground.setTexture(*ResourceManager::Instance()->GetTexture("Background interface"));
	spBackground.setColor(sf::Color{ 100, 100, 100, 255 });

	spButton.setTexture(*ResourceManager::Instance()->GetTexture("Selection niveau bouton"));
	spButton.setOrigin(spButton.getGlobalBounds().width / 2, spButton.getGlobalBounds().height / 2);
	spButton.setPosition(900, 150);

	spFlèches[0].setTexture(*ResourceManager::Instance()->GetTexture("Selection niveau flèche droite"));
	spFlèches[1].setTexture(*ResourceManager::Instance()->GetTexture("Selection niveau flèche gauche"));

	spFlèches[0].setPosition(1500, 500);
	spFlèches[1].setPosition(350, 500);

	spVignette.setTexture(*ResourceManager::Instance()->GetTexture("Selection niveau1"));
	spVignette.setOrigin(spVignette.getGlobalBounds().width / 2, spVignette.getGlobalBounds().height / 2);
	spVignette.setPosition(960, 540);
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
			GameManager::Instance()->m_ActualScene = new PlayerSelector(LevelName[m_MenuChoice - 1]);
		}
		else if (sf::Joystick::isButtonPressed(0, 1))
		{
			Retour.setBuffer(*ResourceManager::Instance()->GetSoundBuffer("Retour"));
			Retour.play();
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

	for (int i = 0; i < 100; i++)
	{
		pos = LoadNames.find(ObjSeparator);
		data = LoadNames.substr(0, pos);
		LevelName[i] = data;
		LoadNames.erase(0, pos + ObjSeparator.length());

		LevelNameText[i].setFont(*ResourceManager::Instance()->GetFont("Font"));
		LevelNameText[i].setFillColor(sf::Color::White);
		LevelNameText[i].setCharacterSize(50);
		LevelNameText[i].setString(LevelName[i]);

		if (LevelName[i] != "")
		{
			FilesNumber++;
		}
	}
}