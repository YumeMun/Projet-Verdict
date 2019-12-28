#include "OpenLevelEditor.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "dirent.h"

OpenLevelEditor::OpenLevelEditor()
{
	m_actualWindow = GameManager::Instance()->GetWindow();

	spBackground.setTexture(*ResourceManager::Instance()->GetTexture("Background interface"));

	for (int i = 0; i < 10; i++)
	{
		LevelIcon[i].setSize(sf::Vector2f{ 200, 150 });
		LevelIcon[i].setFillColor(sf::Color::Black);
		LevelIcon[i].setOutlineColor(sf::Color::White);
		LevelIcon[i].setOutlineThickness(3);
		LevelIcon[i].setPosition(200 + i * 250, 300);
	}

	ObjSeparator = ".txt";
	LoadLevels();
}

OpenLevelEditor::~OpenLevelEditor()
{
}

void OpenLevelEditor::Update()
{
	if (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X) >= 50 && SelectionTimer.getElapsedTime().asMilliseconds() > 300)
	{
		if (LevelSelected < FilesNumber - 1)
			LevelSelected++;

		SelectionTimer.restart();
	}
	else if (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X) <= -50 && SelectionTimer.getElapsedTime().asMilliseconds() > 300)
	{
		if (LevelSelected > 0)
			LevelSelected--;

		SelectionTimer.restart();
	}

	for (int i = 0; i < 10; i++)
	{
		if (i == LevelSelected)
		{
			LevelIcon[i].setOutlineColor(sf::Color::Red);
		}
		else
		{
			LevelIcon[i].setOutlineColor(sf::Color::White);
		}
	}

	if (sf::Joystick::isButtonPressed(0, 0) && SelectionTimer.getElapsedTime().asMilliseconds() > 300)
	{
		for (int i = 0; i < 10; i++)
		{
			GameManager::Instance()->m_ActualScene = new LevelEditor(0, 0, LevelName[LevelSelected]);
		}
	}
	else if (sf::Joystick::isButtonPressed(0, 1) && SelectionTimer.getElapsedTime().asMilliseconds() > 300)
	{
		GameManager::Instance()->LoadScene(e_Enum::e_Scene::CHOOSELEVELEDITOR);
	}
}

void OpenLevelEditor::Display()
{
	m_actualWindow->draw(spBackground);

	for (int i = 0; i < 10; i++)
	{
		if (LevelName[i] != "")
		{
			m_actualWindow->draw(LevelIcon[i]);
		}

		m_actualWindow->draw(LevelNameText[i]);
	}
}

void OpenLevelEditor::EventManager(sf::Event p_pollingEvent)
{
}

void OpenLevelEditor::LoadLevels()
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
		LevelNameText[i].setFillColor(sf::Color::White);
		LevelNameText[i].setCharacterSize(30);
		LevelNameText[i].setString(LevelName[i]);
		LevelNameText[i].setPosition(230 + i * 250, 350);

		if (LevelName[i] != "")
		{
			FilesNumber++;
		}
	}
}