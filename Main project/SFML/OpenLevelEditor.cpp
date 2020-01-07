#include "LevelSelector.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "dirent.h"

OpenLevelEditor::OpenLevelEditor()
{
	std::cout << "LevelSelector constructor" << std::endl;

	m_actualWindow = GameManager::Instance()->GetWindow();

	ObjSeparator = ".txt";
	LoadLevels();

	spPopUp.setTexture(*ResourceManager::Instance()->GetTexture("Fenêtre popup"));
	spPopUp.setOrigin(spPopUp.getGlobalBounds().width / 2, spPopUp.getGlobalBounds().height / 2);
	spPopUp.setPosition(960, 540);

	for (int i = 0; i < 3; i++)
	{
		PopUpText[i].setFont(*ResourceManager::Instance()->GetFont("Font"));
		PopUpText[i].setCharacterSize(35);
		PopUpText[i].setFillColor(sf::Color::White);

		PopUpText[1].setString("Oui");
		PopUpText[1].setCharacterSize(35);
		PopUpText[1].setPosition(800, 570);

		PopUpText[2].setString("Non");
		PopUpText[2].setCharacterSize(35);
		PopUpText[2].setPosition(1050, 570);
	}

	NoFileText.setFont(*ResourceManager::Instance()->GetFont("Font"));
	NoFileText.setCharacterSize(50);
	NoFileText.setFillColor(sf::Color::White);
	NoFileText.setString("	Aucun niveau à charger,\nveuillez créer un nouveau niveau");
	NoFileText.setOrigin(NoFileText.getGlobalBounds().width / 2, NoFileText.getGlobalBounds().height / 2);
	NoFileText.setPosition(960, 540);

	Setup();
}

OpenLevelEditor::~OpenLevelEditor()
{
}

void OpenLevelEditor::Update()
{
	if (FilesNumber != 0)
	{
		if (LeftPressed == true)
		{
			m_LevelSelector[m_MenuChoice - 1].move(50, 0);
			m_LevelSelector[m_MenuChoice].move(50, 0);

			LevelNameText[m_MenuChoice + 1].move(50, 0);
			LevelNameText[m_MenuChoice + 2].move(50, 0);

			if (m_LevelSelector[m_MenuChoice - 1].getPosition().x >= 960)
			{
				m_LevelSelector[m_MenuChoice - 1].setPosition(960, 540);
				LevelNameText[m_MenuChoice + 1].setPosition(540, 120);
				LeftPressed = false;
			}
		}

		if (RightPressed == true)
		{
			m_LevelSelector[m_MenuChoice - 1].move(-50, 0);
			m_LevelSelector[m_MenuChoice - 2].move(-50, 0);

			LevelNameText[m_MenuChoice + 1].move(-50, 0);
			LevelNameText[m_MenuChoice].move(-50, 0);

			if (m_LevelSelector[m_MenuChoice - 1].getPosition().x <= 960)
			{
				m_LevelSelector[m_MenuChoice - 1].setPosition(960, 540);
				LevelNameText[m_MenuChoice + 1].setPosition(540, 120);
				RightPressed = false;
			}
		}

		if (PopUpActivated != 0)
			PopUp();
	}
}

void OpenLevelEditor::Display()
{
	m_actualWindow->draw(spBackground);

	if (FilesNumber != 0)
	{
		m_actualWindow->draw(spButton);

		for (int i = 0; i < m_LevelSelector.size(); i++)
		{
			m_actualWindow->draw(m_LevelSelector[i]);

			m_actualWindow->draw(LevelNameText[2 + i]);
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
			m_actualWindow->draw(spTouches);
		}

		if (PopUpActivated != 0)
		{
			m_actualWindow->draw(spPopUp);

			for (int i = 0; i < 3; i++)
			{
				if (PopUpActivated == 1)
				{
					m_actualWindow->draw(PopUpText[i]);
				}
				else
					m_actualWindow->draw(PopUpText[0]);
			}
		}
	}
	else
		m_actualWindow->draw(NoFileText);

	m_actualWindow->draw(spBoutonRetour);
}

void OpenLevelEditor::Setup()
{
	spBackground.setTexture(*ResourceManager::Instance()->GetTexture("Background interface"));
	spBackground.setColor(sf::Color{ 100, 100, 100, 255 });

	spButton.setTexture(*ResourceManager::Instance()->GetTexture("Selection niveau bouton"));
	spButton.setOrigin(spButton.getGlobalBounds().width / 2, spButton.getGlobalBounds().height / 2);
	spButton.setPosition(900, 150);

	spFlèches[0].setTexture(*ResourceManager::Instance()->GetTexture("Selection niveau flèche droite"));
	spFlèches[1].setTexture(*ResourceManager::Instance()->GetTexture("Selection niveau flèche gauche"));

	spFlèches[0].setPosition(1500, 500);
	spFlèches[1].setPosition(350, 500);

	spTouches.setTexture(*ResourceManager::Instance()->GetTexture("Touches sélection"));
	spTouches.setOrigin(spTouches.getGlobalBounds().width / 2, spTouches.getGlobalBounds().height / 2);
	spTouches.setPosition(720, 650);

	int x = 0;
	for (int i = 1; i <= FilesNumber; i++)
	{
		spLevelSelection.setTexture(*ResourceManager::Instance()->GetTexture("Background sélection niveau"));
		spLevelSelection.setOrigin(spLevelSelection.getGlobalBounds().width / 2, spLevelSelection.getGlobalBounds().height / 2);
		spLevelSelection.setPosition(960 + x, 540);
		m_LevelSelector.push_back(spLevelSelection);

		LevelNameText[i + 1].setPosition(540 + x, 120);

		x = 1360;
	}
}

void OpenLevelEditor::EventManager(sf::Event p_pollingEvent)
{
	if (FilesNumber != 0)
	{
		if (PopUpActivated == 0 && SelectionTimer.getElapsedTime().asMilliseconds() > 500)
		{
			if (m_Clock.getElapsedTime().asSeconds() >= 0.5)
			{
				if (sf::Joystick::getAxisPosition(0, sf::Joystick::X) < -50.f)
				{
					if (m_MenuChoice != 1)
					{
						sound.setBuffer(*ResourceManager::Instance()->GetSoundBuffer("Curseur menu"));
						sound.play();
						m_MenuChoice = m_MenuChoice - 1;
						LeftPressed = true;
					}

					m_Clock.restart();
				}
				if (sf::Joystick::getAxisPosition(0, sf::Joystick::X) > 50.f)
				{
					if (m_MenuChoice != FilesNumber)
					{
						sound.setBuffer(*ResourceManager::Instance()->GetSoundBuffer("Curseur menu"));
						sound.play();
						m_MenuChoice = m_MenuChoice + 1;
						RightPressed = true;
					}
					m_Clock.restart();
				}

				if (sf::Joystick::isButtonPressed(0, 0))
				{
					GameManager::Instance()->m_ActualScene = new LevelEditor(0, 0, LevelName[m_MenuChoice + 1], true);
				}
				else if (sf::Joystick::isButtonPressed(0, 2))
				{
					PopUpActivated = 1;
				}
				else if (sf::Joystick::isButtonPressed(0, 3))
				{
					GameManager::Instance()->m_ActualScene = new SaveEditor(0, 0, " ", 1, true, LevelName[m_MenuChoice + 1]);
				}
			}
		}
	}

	if (sf::Joystick::isButtonPressed(0, 1))
	{
		retour.setBuffer(*ResourceManager::Instance()->GetSoundBuffer("Retour"));
		retour.play();
		GameManager::Instance()->LoadScene(e_Enum::e_Scene::CHOOSELEVELEDITOR);
	}
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

	for (int i = 0; i < 98; i++)
	{
		pos = LoadNames.find(ObjSeparator);
		data = LoadNames.substr(0, pos);
		LevelName[i] = data;
		LoadNames.erase(0, pos + ObjSeparator.length());

		LevelNameText[i].setFont(*ResourceManager::Instance()->GetFont("Font"));
		LevelNameText[i].setFillColor(sf::Color::White);
		LevelNameText[i].setCharacterSize(50);
		LevelNameText[i].setString(LevelName[i]);

		if (LevelName[i] != "" && LevelName[i] != "0Niveau1" && LevelName[i] != "0Niveau2")
		{
			FilesNumber++;
		}
	}
}

void OpenLevelEditor::PopUp()
{
	if (PopUpActivated == 1)
	{
		PopUpText[0].setString("	Voulez-vous vraiment supprimer\n				ce niveau ?");
		PopUpText[0].setPosition(630, 470);

		if (SelectionPopUp == 1)
		{
			PopUpText[1].setFillColor(sf::Color{ 255, 156, 0, 255 });
			PopUpText[2].setFillColor(sf::Color::White);
		}
		else if (SelectionPopUp == 2)
		{
			PopUpText[1].setFillColor(sf::Color::White);
			PopUpText[2].setFillColor(sf::Color{ 255, 156, 0, 255 });
		}

		if (sf::Joystick::getAxisPosition(0, sf::Joystick::X) >= 50)
			SelectionPopUp = 2;
		else if (sf::Joystick::getAxisPosition(0, sf::Joystick::X) <= -50)
			SelectionPopUp = 1;

		if (sf::Joystick::isButtonPressed(0, 0) && SelectionTimer.getElapsedTime().asMilliseconds() > 300)
		{
			if (SelectionPopUp == 1)
			{
				PopUpActivated = 2;
			}
			else if (SelectionPopUp == 2)
				PopUpActivated = 0;

			SelectionTimer.restart();
		}
	}
	else if (PopUpActivated == 2)
	{
		std::string Temp = "Ressources/Sauvegardes/" + LevelName[m_MenuChoice + 1] + ".txt";
		remove(Temp.c_str());

		PopUpText[0].setString("	Niveau supprimé avec succès");
		PopUpText[0].setPosition(640, 510);

		if (SelectionTimer.getElapsedTime().asSeconds() > 1)
		{
			GameManager::Instance()->LoadScene(e_Enum::e_Scene::OPENLEVELEDITOR);
		}
	}
}