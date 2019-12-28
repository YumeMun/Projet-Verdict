#include "LevelEditor.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "Enum.h"
#include <fstream>

LevelEditor::LevelEditor()
{
}

LevelEditor::LevelEditor(int _SizeX, int _SizeY, std::string _LevelName)
{
	std::cout << "Editeur" << std::endl;

	m_actualWindow = GameManager::Instance()->GetWindow();

	spInterface.setTexture(*ResourceManager::Instance()->GetTexture("Interface éditeur"));

	ViewRect.left = 0, ViewRect.top = 0, ViewRect.width = 1920, ViewRect.height = 1080;
	View.reset(ViewRect);
	View.setCenter(960, 540);
	View.zoom(2);

	SelecterTarget.setRadius(32);
	SelecterTarget.setFillColor(sf::Color::Transparent);
	SelecterTarget.setOutlineThickness(5);
	SelecterTarget.setOutlineColor(sf::Color::White);
	SelecterTarget.setOrigin(32, 32);
	SelecterTarget.setPosition(m_actualWindow->getSize().x / 2, m_actualWindow->getSize().y / 2);

	spFlèches[0].setTexture(*ResourceManager::Instance()->GetTexture("Flèche gauche"));
	spFlèches[1].setTexture(*ResourceManager::Instance()->GetTexture("Flèche droite"));

	if (_LevelName == "")
	{
		Size_X = _SizeX;
		Size_Y = _SizeY;

		std::ifstream TempLoad;

		TempLoad.open("Ressources/Sauvegardes/TempSave.txt", std::ios_base::in);

		if (TempLoad)
		{
			for (int y = 0; y < Size_Y; y++)
			{
				for (int x = 0; x < Size_X; x++)
				{
					TempLoad >> Tableau[y][x];
				}
			}

			TempLoad.close();
			remove("Ressources/Sauvegardes/TempSave.txt");
		}
		else
		{
			for (int y = 0; y < Size_Y; y++)
			{
				for (int x = 0; x < Size_X; x++)
				{
					Tableau[y][x] = 0;
				}
			}
		}
	}
	else
	{
		std::ifstream LoadFile;

		LoadFile.open("Ressources/Sauvegardes/" + _LevelName + ".txt", std::ios_base::in);

		LoadFile >> Size_X;
		LoadFile >> Size_Y;
		LoadFile >> SelectionBackground;

		for (int y = 0; y < Size_Y; y++)
		{
			for (int x = 0; x < Size_X; x++)
			{
				LoadFile >> Tableau[y][x];
			}
		}

		LoadFile.close();
	}


	Case.setSize(sf::Vector2f{ 64, 64 });
	Case.setFillColor(sf::Color::Transparent);
	Case.setOutlineColor(sf::Color::White);
	Case.setOutlineThickness(1);

	//for (int i = 0; i < 8; i++)
	//{
	//	spTile[i].setTexture(*ResourceManager::Instance()->GetTexture("Case" + std::to_string(i + 1)));
	//}

	hud = new HudEditor();
}

LevelEditor::~LevelEditor()
{
}

void LevelEditor::Update()
{
	CurrentTime = (float)clock() / CLOCKS_PER_SEC;
	ElapsedTime = CurrentTime - LastFrameTime;

	if (sf::Joystick::isConnected(0))
		ControllerManager();

	LastFrameTime = CurrentTime;
}

void LevelEditor::Display()
{
	m_actualWindow->setView(m_actualWindow->getDefaultView());
	m_actualWindow->draw(spInterface);

	m_actualWindow->setView(View);

	for (int y = 0; y < Size_Y; y++)
	{
		for (int x = 0; x < Size_X; x++)
		{
			CasePos.x = (float)x * 64;
			CasePos.y = (float)y * 64;

			if (CasePos.x >= View.getCenter().x - View.getSize().x / 2 && CasePos.x <= View.getCenter().x + View.getSize().x / 2)
			{
				switch (Tableau[y][x])
				{
				case 0:
					Case.setPosition(CasePos);
					m_actualWindow->draw(Case);
					break;
				case 1:
					/*spTile[0].setPosition(CasePos);
					m_actualWindow->draw(spTile[0]);*/
					break;
				case 2:
					/*spTile[1].setPosition(CasePos);
					m_actualWindow->draw(spTile[1]);*/
					break;
				case 3:
					/*spTile[2].setPosition(CasePos);
					m_actualWindow->draw(spTile[2]);*/
					break;
				case 4:
					/*spTile[3].setPosition(CasePos);
					m_actualWindow->draw(spTile[3]);*/
					break;
				case 5:
					/*spTile[4].setPosition(CasePos);
					m_actualWindow->draw(spTile[4]);*/
					break;
				case 6:
					/*spTile[5].setPosition(CasePos);
					m_actualWindow->draw(spTile[5]);*/
					break;
				case 7:
					/*spTile[6].setPosition(CasePos);
					m_actualWindow->draw(spTile[6]);*/
					break;
				case 8:
					/*spTile[7].setPosition(CasePos);
					m_actualWindow->draw(spTile[7]);*/
					break;
				}
			}
		}
	}

	m_actualWindow->draw(SelecterTarget);

	if (HudDisplay == true)
	{
		hud->Display();
		BackgroundChoice();
	}
}

void LevelEditor::EventManager(sf::Event p_pollingEvent)
{
	hud->EventManager(p_pollingEvent);
}

void LevelEditor::ControllerManager()
{

	if (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X) <= -50)
	{
		SelecterTarget.move(-600 * ElapsedTime, 0);
	}
	else if (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X) >= 50)
	{
		SelecterTarget.move(600 * ElapsedTime, 0);
	}

	if (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y) <= -50)
	{
		SelecterTarget.move(0, -600 * ElapsedTime);
	}
	else if (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y) >= 50)
	{
		SelecterTarget.move(0, 600 * ElapsedTime);
	}

	if (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::U) <= -50)
	{
		View.move(-600 * ElapsedTime, 0);
		SelecterTarget.move(-600 * ElapsedTime, 0);
	}
	else if (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::U) >= 50)
	{
		View.move(600 * ElapsedTime, 0);
		SelecterTarget.move(600 * ElapsedTime, 0);
	}

	if (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::V) <= -50)
	{
		View.move(0, -600 * ElapsedTime);
		SelecterTarget.move(0, -600 * ElapsedTime);
	}
	else if (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::V) >= 50)
	{
		View.move(0, 600 * ElapsedTime);
		SelecterTarget.move(0, 600 * ElapsedTime);
	}

	if (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Z) <= -50 && View.getSize().x >= 1500)
	{
		View.zoom(0.99);
	}
	if (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Z) >= 50 && View.getSize().x <= 4000)
	{
		View.zoom(1.01);
	}

	if (SelectionTimer.getElapsedTime().asMilliseconds() > 300)
	{
		if (sf::Joystick::isButtonPressed(0, 6))
		{
			if (HudDisplay == true)
				HudDisplay = false;
			else if (HudDisplay == false)
				HudDisplay = true;

			SelectionTimer.restart();
		}

		if (sf::Joystick::isButtonPressed(0, 0))
		{
			CasePos.x = SelecterTarget.getPosition().x / 64;
			CasePos.y = SelecterTarget.getPosition().y / 64;
			Select = 1;
		}
		if (Select == 1)
		{
			if (Tableau[(int)CasePos.y][(int)CasePos.x] == 0)
			{
				Tableau[(int)CasePos.y][(int)CasePos.x] = hud->Selection;

				Select = 2;
			}
			else
				Select = 2;
		}

		if (!sf::Joystick::isButtonPressed(0, 0) && Select == 2)
		{
			Select = 0;
		}

		if (sf::Joystick::isButtonPressed(0, 2))
		{
			CasePos.x = SelecterTarget.getPosition().x / 64;
			CasePos.y = SelecterTarget.getPosition().y / 64;
			Tableau[(int)CasePos.y][(int)CasePos.x] = 0;
		}
		else if (sf::Joystick::isButtonPressed(0, 3))
		{
			for (int y = 0; y < Size_Y; y++)
			{
				for (int x = 0; x < Size_X; x++)
				{
					Tableau[y][x] = 0;
				}
			}
		}
		else if (sf::Joystick::isButtonPressed(0, 1))
		{
			GameManager::Instance()->LoadScene(e_Enum::e_Scene::CHOOSELEVELEDITOR);
		}
	}

	if (sf::Joystick::isButtonPressed(0, 7))
		Sauvegarde();
}

void LevelEditor::Sauvegarde()
{
	for (int y = 0; y < Size_Y; y++)
	{
		for (int x = 0; x < Size_X; x++)
		{
			Save += std::to_string(Tableau[y][x]) + " ";
		}

		Save += "\n";
	}

	GameManager::Instance()->m_ActualScene = new SaveEditor(Size_X, Size_Y, Save, SelectionBackground);
}

void LevelEditor::BackgroundChoice()
{
	if (SelectionBackground == 1)
		spBackground.setTexture(*ResourceManager::Instance()->GetTexture("Thème1"));
	else if (SelectionBackground == 2)
		spBackground.setTexture(*ResourceManager::Instance()->GetTexture("Thème2"));

	spFlèches[0].setPosition(20, 230);
	spFlèches[1].setPosition(260, 230);
	spBackground.setPosition(55, 200);

	for (int i = 0; i < 2; i++)
	{
		m_actualWindow->draw(spFlèches[i]);
	}

	m_actualWindow->draw(spBackground);

	if (sf::Joystick::getAxisPosition(0, sf::Joystick::PovX) >= 10)
	{
		if (SelectionBackground < 2)
			SelectionBackground++;
	}
	else if (sf::Joystick::getAxisPosition(0, sf::Joystick::PovX) <= -10)
	{
		if (SelectionBackground > 1)
			SelectionBackground--;
	}
}