#include "LevelEditor.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "Enum.h"
#include <fstream>

LevelEditor::LevelEditor()
{
}

LevelEditor::LevelEditor(int _SizeX, int _SizeY, std::string _LevelName, bool _isNewLevel)
{
	std::cout << "Editeur" << std::endl;

	m_actualWindow = GameManager::Instance()->GetWindow();

	LevelName = _LevelName;
	isNewLevel = _isNewLevel;

	spInterface.setTexture(*ResourceManager::Instance()->GetTexture("Interface éditeur"));

	ViewRect.left = 0, ViewRect.top = 0, ViewRect.width = 1920, ViewRect.height = 1080;
	View.reset(ViewRect);
	View.setCenter(960, 540);
	View.zoom(1.5);

	spSelecterTarget.setTexture(*ResourceManager::Instance()->GetTexture("Curseur pose"));
	spSelecterTarget.setOrigin(spSelecterTarget.getGlobalBounds().width / 2, spSelecterTarget.getGlobalBounds().height / 2);
	spSelecterTarget.setPosition(View.getCenter());

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

	BandeauGaucheRect.setSize(sf::Vector2f{ 370, 1080 });
	BandeauGaucheRect.setFillColor(sf::Color{ 0, 0, 0, 150 });

	spBoutonSauvegarde.setTexture(*ResourceManager::Instance()->GetTexture("Bouton sauvegarder"));
	spBoutonSauvegarde.setPosition(1500, 1000);

	spToucheSelect.setTexture(*ResourceManager::Instance()->GetTexture("Touche select"));
	spToucheSelect.setPosition(50, 880);

	spTouches.setTexture(*ResourceManager::Instance()->GetTexture("Touches éditeur"));
	spTouches.setPosition(20, 400);

	spTouchesZoom[0].setTexture(*ResourceManager::Instance()->GetTexture("LT"));
	spTouchesZoom[1].setTexture(*ResourceManager::Instance()->GetTexture("RT"));
	spTouchesZoom[2].setTexture(*ResourceManager::Instance()->GetTexture("Loupe-"));
	spTouchesZoom[3].setTexture(*ResourceManager::Instance()->GetTexture("Loupe+"));

	spTouchesZoom[0].setPosition(120, 630);
	spTouchesZoom[1].setPosition(220, 630);
	spTouchesZoom[2].setPosition(120, 760);
	spTouchesZoom[3].setPosition(220, 760);

	spTouchesZoom[0].setScale(0.8, 0.8);
	spTouchesZoom[1].setScale(0.8, 0.8);
	spTouchesZoom[2].setScale(0.5, 0.5);
	spTouchesZoom[3].setScale(0.5, 0.5);

	spPopUp.setTexture(*ResourceManager::Instance()->GetTexture("Fenêtre popup"));
	spPopUp.setOrigin(spPopUp.getGlobalBounds().width / 2, spPopUp.getGlobalBounds().height / 2);
	spPopUp.setPosition(960, 540);

	for (int i = 0; i < 3; i++)
	{
		PopUpText[i].setFont(*ResourceManager::Instance()->GetFont("Font"));
		PopUpText[i].setCharacterSize(25);
		PopUpText[i].setFillColor(sf::Color::White);


		PopUpText[1].setString("Oui");
		PopUpText[1].setCharacterSize(35);
		PopUpText[1].setPosition(800, 570);

		PopUpText[2].setString("Non");
		PopUpText[2].setCharacterSize(35);
		PopUpText[2].setPosition(1050, 570);
	}

	hud = new HudEditor();

	for (int i = 0; i < 30; i++)
	{
		spTile[i].setTexture(*ResourceManager::Instance()->GetTexture("Tileset"));

		spTile[0].setTextureRect(sf::IntRect{ 0 * 64, 0 * 64, 64, 64 });
		spTile[1].setTextureRect(sf::IntRect{ 1 * 64, 0 * 64, 64, 64 });
		spTile[2].setTextureRect(sf::IntRect{ 2 * 64, 0 * 64, 64, 64 });
		spTile[3].setTextureRect(sf::IntRect{ 0 * 64, 1 * 64, 64, 64 });
		spTile[4].setTextureRect(sf::IntRect{ 1 * 64, 1 * 64, 64, 64 });
		spTile[5].setTextureRect(sf::IntRect{ 2 * 64, 1 * 64, 64, 64 });
		spTile[6].setTextureRect(sf::IntRect{ 0 * 64, 3 * 64, 64, 64 });
		spTile[7].setTextureRect(sf::IntRect{ 1 * 64, 3 * 64, 64, 64 });
		spTile[8].setTextureRect(sf::IntRect{ 0 * 64, 4 * 64, 64, 64 });
		spTile[9].setTextureRect(sf::IntRect{ 1 * 64, 4 * 64, 64, 64 });
		spTile[10].setTextureRect(sf::IntRect{ 0 * 64, 5 * 64, 64, 64 });
		spTile[11].setTextureRect(sf::IntRect{ 0 * 64, 6 * 64, 64, 64 });
		spTile[12].setTextureRect(sf::IntRect{ 0 * 64, 7 * 64, 64, 64 });
		spTile[13].setTextureRect(sf::IntRect{ 0 * 64, 8 * 64, 64, 64 });
		spTile[14].setTextureRect(sf::IntRect{ 1 * 64, 8 * 64, 64, 64 });
		spTile[15].setTextureRect(sf::IntRect{ 0 * 64, 9 * 64, 64, 64 });

		spTile[16].setTextureRect(sf::IntRect{ 0 * 64, 10 * 64, 64, 64 });
		spTile[17].setTextureRect(sf::IntRect{ 1 * 64, 10 * 64, 64, 64 });
		spTile[18].setTextureRect(sf::IntRect{ 2 * 64, 10 * 64, 64, 64 });

		spTile[19].setTextureRect(sf::IntRect{ 0 * 64, 13 * 64, 4 * 64, 64 });

		spTile[20].setTextureRect(sf::IntRect{ 0 * 64, 14 * 64, 64, 4 * 64 });

		spTile[21].setTextureRect(sf::IntRect{ 14 * 64, 18 * 64, 64, 3 * 64 });

		spTile[22].setTextureRect(sf::IntRect{ 9 * 64, 12 * 64, 64, 64 });
		spTile[23].setTextureRect(sf::IntRect{ 0 * 64, 11 * 64, 64, 64 });
		spTile[24].setTextureRect(sf::IntRect{ 1 * 64, 11 * 64, 64, 64 });
		spTile[25].setTextureRect(sf::IntRect{ 2 * 64, 11 * 64, 64, 64 });

		spTile[26].setTextureRect(sf::IntRect{ 1 * 64, 9 * 64, 64, 64 });
	}
}

LevelEditor::~LevelEditor()
{
}

void LevelEditor::Update()
{
	CurrentTime = (float)clock() / CLOCKS_PER_SEC;
	ElapsedTime = CurrentTime - LastFrameTime;

	if (PopUpActivated == false)
	{
		if (sf::Joystick::isConnected(0))
			ControllerManager();

		if (sf::Joystick::isButtonPressed(0, 1) && SelectionTimer.getElapsedTime().asMilliseconds() > 500)
		{
			PopUpActivated = 1;
		}
		else if (sf::Joystick::isButtonPressed(0, 3) && SelectionTimer.getElapsedTime().asMilliseconds() > 500)
		{
			PopUpActivated = 2;
		}
	}
	else if (PopUpActivated == 1)
	{
		PopUpText[0].setString("					Voulez-vous vraiment quitter\n							le mode édition ?\n(Vos dernières modifications ne seront pas sauvegardées)");
		PopUpText[0].setPosition(575, 470);

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

		if (sf::Joystick::isButtonPressed(0, 0))
		{
			if (SelectionPopUp == 1)
				GameManager::Instance()->LoadScene(e_Enum::e_Scene::CHOOSELEVELEDITOR);
			else if (SelectionPopUp == 2)
			{
				SelectionTimer.restart();
				PopUpActivated = 0;
			}
		}
	}
	else if (PopUpActivated == 2)
	{
		PopUpText[0].setString("Voulez-vous vraiment tout effacer ?");
		PopUpText[0].setPosition(680, 500);

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

		if (sf::Joystick::isButtonPressed(0, 0))
		{
			if (SelectionPopUp == 1)
			{
				for (int y = 0; y < Size_Y; y++)
				{
					for (int x = 0; x < Size_X; x++)
					{
						Tableau[y][x] = 0;
					}
				}
				SelectionTimer.restart();
				PopUpActivated = 0;
			}
			else if (SelectionPopUp == 2)
			{
				SelectionTimer.restart();
				PopUpActivated = 0;
			}
		}
	}
	else if (PopUpActivated == 3)
	{
		PopUpText[0].setString("Voulez-vous sauvegarder les modifications ?");
		PopUpText[0].setPosition(680, 500);

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

		if (sf::Joystick::isButtonPressed(0, 0))
		{
			if (SelectionPopUp == 1)
			{
				SaveIt();
				SelectionTimer.restart();
			}
			else if (SelectionPopUp == 2)
			{
				SelectionTimer.restart();
				PopUpActivated = 0;
			}
		}
	}
	else if (PopUpActivated == 4)
	{
		PopUpText[0].setString("				Oups, une erreur est survenue.\nVeuillez vérifier qu'il y a bien un départ et une arrivée.");
		PopUpText[0].setPosition(600, 500);

		if (sf::Joystick::isButtonPressed(0, 0) || sf::Joystick::isButtonPressed(0, 1))
		{
			PopUpActivated = 0;
			SelectionTimer.restart();
		}
	}

	LastFrameTime = CurrentTime;
}

void LevelEditor::Display()
{
	m_actualWindow->setView(m_actualWindow->getDefaultView());
	m_actualWindow->draw(spInterface);

	m_actualWindow->setView(View);

	AnimTiles();

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
					spTile[0].setPosition(CasePos);
					m_actualWindow->draw(spTile[0]);
					break;
				case 2:
					spTile[1].setPosition(CasePos);
					m_actualWindow->draw(spTile[1]);
					break;
				case 3:
					spTile[2].setPosition(CasePos);
					m_actualWindow->draw(spTile[2]);
					break;
				case 4:
					spTile[3].setPosition(CasePos);
					m_actualWindow->draw(spTile[3]);
					break;
				case 5:
					spTile[4].setPosition(CasePos);
					m_actualWindow->draw(spTile[4]);
					break;
				case 6:
					spTile[5].setPosition(CasePos);
					m_actualWindow->draw(spTile[5]);
					break;
				case 7:
					spTile[6].setPosition(CasePos);
					m_actualWindow->draw(spTile[6]);
					break;
				case 8:
					spTile[7].setPosition(CasePos);
					m_actualWindow->draw(spTile[7]);
					break;
				case 9:
					spTile[8].setPosition(CasePos);
					m_actualWindow->draw(spTile[8]);
					break;
				case 10:
					spTile[9].setPosition(CasePos);
					m_actualWindow->draw(spTile[9]);
					break;
				case 11:
					spTile[10].setTextureRect(sf::IntRect{ FrameIndexBoost * 64, 5 * 64, 64, 64 });
					spTile[10].setPosition(CasePos);
					m_actualWindow->draw(spTile[10]);
					break;
				case 12:
					spTile[11].setTextureRect(sf::IntRect{ FrameIndexBoost * 64, 6 * 64, 64, 64 });
					spTile[11].setPosition(CasePos);
					m_actualWindow->draw(spTile[11]);
					break;
				case 13:
					spTile[12].setTextureRect(sf::IntRect{ FrameIndexBoost * 64, 7 * 64, 64, 64 });
					spTile[12].setPosition(CasePos);
					m_actualWindow->draw(spTile[12]);
					break;
				case 14:
					spTile[13].setPosition(CasePos);
					m_actualWindow->draw(spTile[13]);
					break;
				case 15:
					spTile[14].setPosition(CasePos);
					m_actualWindow->draw(spTile[14]);
					break;
				case 16:
					spTile[15].setPosition(CasePos);
					m_actualWindow->draw(spTile[15]);
					break;
				case 17:
					spTile[16].setPosition(CasePos);
					m_actualWindow->draw(spTile[16]);
					break;
				case 18:
					spTile[17].setPosition(CasePos);
					m_actualWindow->draw(spTile[17]);
					break;
				case 19:
					spTile[18].setPosition(CasePos);
					m_actualWindow->draw(spTile[18]);
					break;
				case 20:
					spTile[19].setTextureRect(sf::IntRect{ FrameIndexElect *  (4 * 64), 13 * 64, 4 * 64, 64 });
					spTile[19].setPosition(CasePos);
					m_actualWindow->draw(spTile[19]);
					break;
				case 21:
					spTile[20].setTextureRect(sf::IntRect{ FrameIndexElect * 64, 14 * 64, 64, 4 * 64 });
					spTile[20].setPosition(CasePos);
					m_actualWindow->draw(spTile[20]);
					break;
				case 22:
					spTile[21].setPosition(CasePos);
					m_actualWindow->draw(spTile[21]);
					break;
				case 23:
					spTile[22].setTextureRect(sf::IntRect{ FrameIndexCollect * 64, 12 * 64, 64, 64 });
					spTile[22].setPosition(CasePos);
					m_actualWindow->draw(spTile[22]);
					break;
				case 24:
					spTile[23].setPosition(CasePos);
					m_actualWindow->draw(spTile[23]);
					break;
				case 25:
					spTile[24].setPosition(CasePos);
					m_actualWindow->draw(spTile[24]);
					break;
				case 26:
					spTile[25].setPosition(CasePos);
					m_actualWindow->draw(spTile[25]);
					break;
				case 27:
					spTile[26].setPosition(CasePos);
					m_actualWindow->draw(spTile[26]);
					break;
				}
			}
		}
	}

	if (spSelecterTarget.getPosition().x >= 0 && spSelecterTarget.getPosition().x <= Size_X * 64 && spSelecterTarget.getPosition().y >= 0 && spSelecterTarget.getPosition().y <= Size_Y * 64)
		CheckIfCaseIsFree();

	m_actualWindow->draw(spSelecterTarget);

	if (HudDisplay == true)
	{
		m_actualWindow->setView(m_actualWindow->getDefaultView());
		m_actualWindow->draw(BandeauGaucheRect);
		hud->Display();
		BackgroundChoice();
		m_actualWindow->draw(spBoutonSauvegarde);
		m_actualWindow->draw(spTouches);
		m_actualWindow->draw(spToucheSelect);

		for (int i = 0; i < 4; i++)
		{
			m_actualWindow->draw(spTouchesZoom[i]);
		}
	}

	if (PopUpActivated != 0)
	{
		m_actualWindow->draw(spPopUp);

		if (PopUpActivated != 4)
		{
			for (int i = 0; i < 3; i++)
			{
				m_actualWindow->draw(PopUpText[i]);
			}
		}
		else
		{
			m_actualWindow->draw(PopUpText[0]);
		}
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
		if (spSelecterTarget.getPosition().x > View.getCenter().x - View.getSize().x / 2)
			spSelecterTarget.move(-600 * ElapsedTime, 0);
		else
			spSelecterTarget.move(600 * ElapsedTime, 0);
	}
	else if (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X) >= 50)
	{
		if (spSelecterTarget.getPosition().x < View.getCenter().x + View.getSize().x / 2)
			spSelecterTarget.move(600 * ElapsedTime, 0);
		else
			spSelecterTarget.move(-600 * ElapsedTime, 0);
	}

	if (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y) <= -50)
	{
		if (spSelecterTarget.getPosition().y < View.getCenter().y - View.getSize().y / 2)
			spSelecterTarget.move(0, 600 * ElapsedTime);
		else
			spSelecterTarget.move(0, -600 * ElapsedTime);
	}
	else if (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y) >= 50)
	{
		if (spSelecterTarget.getPosition().y > View.getCenter().y + View.getSize().y / 2)
			spSelecterTarget.move(0, -600 * ElapsedTime);
		else
			spSelecterTarget.move(0, 600 * ElapsedTime);
	}

	if (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::U) <= -50)
	{
		View.move(-600 * ElapsedTime, 0);
		spSelecterTarget.move(-600 * ElapsedTime, 0);
	}
	else if (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::U) >= 50)
	{
		View.move(600 * ElapsedTime, 0);
		spSelecterTarget.move(600 * ElapsedTime, 0);
	}

	if (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::V) <= -50)
	{
		View.move(0, -600 * ElapsedTime);
		spSelecterTarget.move(0, -600 * ElapsedTime);
	}
	else if (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::V) >= 50)
	{
		View.move(0, 600 * ElapsedTime);
		spSelecterTarget.move(0, 600 * ElapsedTime);
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

		if (spSelecterTarget.getPosition().x >= 0 && spSelecterTarget.getPosition().x <= Size_X * 64 && spSelecterTarget.getPosition().y >= 0 && spSelecterTarget.getPosition().y <= Size_Y * 64)
		{
			if (sf::Joystick::isButtonPressed(0, 0))
			{
				CasePos.x = spSelecterTarget.getPosition().x / 64;
				CasePos.y = spSelecterTarget.getPosition().y / 64;
				Select = 1;
			}
			if (Select == 1)
			{
				if (Tableau[(int)CasePos.y][(int)CasePos.x] == 0)
				{
					if (hud->Selection < 20)
						Tableau[(int)CasePos.y][(int)CasePos.x] = hud->Selection;

					Select = 2;

					if (hud->Selection == 16)
					{
						Tableau[(int)CasePos.y][(int)CasePos.x] = 16;
						for (int i = CasePos.y; i < 33; i++)
						{
							Tableau[(int)i + 1][(int)CasePos.x] = 27;
						}
					}
					else if (hud->Selection == 20)
					{
						if (Tableau[(int)CasePos.y][(int)CasePos.x + 1] == 0 && Tableau[(int)CasePos.y][(int)CasePos.x + 2] == 0 && Tableau[(int)CasePos.y][(int)CasePos.x + 3] == 0)
						{
							Tableau[(int)CasePos.y][(int)CasePos.x] = 20;
							Tableau[(int)CasePos.y][(int)CasePos.x + 1] = 28;
							Tableau[(int)CasePos.y][(int)CasePos.x + 2] = 28;
							Tableau[(int)CasePos.y][(int)CasePos.x + 3] = 28;
						}
					}
					else if (hud->Selection == 21)
					{
						if (Tableau[(int)CasePos.y + 1][(int)CasePos.x] == 0 && Tableau[(int)CasePos.y + 2][(int)CasePos.x] == 0 && Tableau[(int)CasePos.y + 3][(int)CasePos.x] == 0)
						{
							Tableau[(int)CasePos.y][(int)CasePos.x] = 21;
							Tableau[(int)CasePos.y + 1][(int)CasePos.x] = 28;
							Tableau[(int)CasePos.y + 2][(int)CasePos.x] = 28;
							Tableau[(int)CasePos.y + 3][(int)CasePos.x] = 28;
						}
					}
					else if (hud->Selection == 22)
					{
						if (Tableau[(int)CasePos.y + 1][(int)CasePos.x] == 0 && Tableau[(int)CasePos.y + 2][(int)CasePos.x] == 0)
						{
							Tableau[(int)CasePos.y][(int)CasePos.x] = 22;
							Tableau[(int)CasePos.y + 1][(int)CasePos.x] = 29;
							Tableau[(int)CasePos.y + 2][(int)CasePos.x] = 29;
						}
					}
					else if (hud->Selection == 7)
					{
						if (Tableau[(int)CasePos.y + 1][(int)CasePos.x] == 0)
						{
							Tableau[(int)CasePos.y][(int)CasePos.x] = 7;
							Tableau[(int)CasePos.y + 1][(int)CasePos.x] = 9;
						}
					}
					else if (hud->Selection == 8)
					{
						if (Tableau[(int)CasePos.y + 1][(int)CasePos.x] == 0)
						{
							Tableau[(int)CasePos.y][(int)CasePos.x] = 8;
							Tableau[(int)CasePos.y + 1][(int)CasePos.x] = 10;
						}
					}
					else if (hud->Selection == 12)
					{
						if (Tableau[(int)CasePos.y + 1][(int)CasePos.x] == 0)
						{
							Tableau[(int)CasePos.y][(int)CasePos.x] = 12;
							Tableau[(int)CasePos.y + 1][(int)CasePos.x] = 14;
						}
					}
					else if (hud->Selection == 13)
					{
						if (Tableau[(int)CasePos.y + 1][(int)CasePos.x] == 0)
						{
							Tableau[(int)CasePos.y][(int)CasePos.x] = 13;
							Tableau[(int)CasePos.y + 1][(int)CasePos.x] = 15;
						}
					}
					else if (hud->Selection == 23)
					{
						Tableau[(int)CasePos.y][(int)CasePos.x] = 23;
					}
					else if (hud->Selection == 24)
					{
						if (Tableau[(int)CasePos.y + 1][(int)CasePos.x] >= 1 && Tableau[(int)CasePos.y + 1][(int)CasePos.x] <= 6)
						{
							if (StartIsPut == false)
							{
								Tableau[(int)CasePos.y][(int)CasePos.x] = 24;
								StartIsPut = true;
							}
						}
					}
					else if (hud->Selection == 25)
					{
						if (Tableau[(int)CasePos.y + 1][(int)CasePos.x] >= 1 && Tableau[(int)CasePos.y + 1][(int)CasePos.x] <= 6)
						{
							if (EndIsPut == false)
							{
								Tableau[(int)CasePos.y][(int)CasePos.x] = 25;
								EndIsPut = true;
							}
						}
					}
					else if (hud->Selection == 26)
					{
						if (Tableau[(int)CasePos.y + 1][(int)CasePos.x] >= 1 && Tableau[(int)CasePos.y + 1][(int)CasePos.x] <= 6)
						{
							Tableau[(int)CasePos.y][(int)CasePos.x] = 26;
						}
					}
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
				spSelecterTarget.setTexture(*ResourceManager::Instance()->GetTexture("Curseur suppression"));
				CasePos.x = spSelecterTarget.getPosition().x / 64;
				CasePos.y = spSelecterTarget.getPosition().y / 64;

				if (Tableau[(int)CasePos.y][(int)CasePos.x] == 24)
				{
					StartIsPut = false;
				}
				else if (Tableau[(int)CasePos.y][(int)CasePos.x] == 25)
				{
					EndIsPut = false;
				}

				if (Tableau[(int)CasePos.y][(int)CasePos.x + 1] == 28)
					Tableau[(int)CasePos.y][(int)CasePos.x + 1] = 0;
				else if (Tableau[(int)CasePos.y][(int)CasePos.x + 2] == 28)
					Tableau[(int)CasePos.y][(int)CasePos.x + 2] = 0;
				else if (Tableau[(int)CasePos.y][(int)CasePos.x + 3] == 28)
					Tableau[(int)CasePos.y][(int)CasePos.x + 3] = 0;
				else if (Tableau[(int)CasePos.y][(int)CasePos.x - 1] == 20)
				{
					Tableau[(int)CasePos.y][(int)CasePos.x - 1] = 0;
					Tableau[(int)CasePos.y][(int)CasePos.x] = 0;
					Tableau[(int)CasePos.y][(int)CasePos.x + 1] = 0;
					Tableau[(int)CasePos.y][(int)CasePos.x + 2] = 0;
				}
				else if (Tableau[(int)CasePos.y][(int)CasePos.x - 2] == 20)
				{
					Tableau[(int)CasePos.y][(int)CasePos.x - 2] = 0;
					Tableau[(int)CasePos.y][(int)CasePos.x - 1] = 0;
					Tableau[(int)CasePos.y][(int)CasePos.x] = 0;
					Tableau[(int)CasePos.y][(int)CasePos.x + 1] = 0;
				}
				else if (Tableau[(int)CasePos.y][(int)CasePos.x - 3] == 20)
				{
					Tableau[(int)CasePos.y][(int)CasePos.x - 3] = 0;
					Tableau[(int)CasePos.y][(int)CasePos.x - 2] = 0;
					Tableau[(int)CasePos.y][(int)CasePos.x - 1] = 0;
					Tableau[(int)CasePos.y][(int)CasePos.x] = 0;
				}


				if (Tableau[(int)CasePos.y + 1][(int)CasePos.x] == 28)
					Tableau[(int)CasePos.y + 1][(int)CasePos.x] = 0;
				else if (Tableau[(int)CasePos.y + 2][(int)CasePos.x] == 28)
					Tableau[(int)CasePos.y + 2][(int)CasePos.x] = 0;
				else if (Tableau[(int)CasePos.y + 3][(int)CasePos.x] == 28)
					Tableau[(int)CasePos.y + 3][(int)CasePos.x] = 0;
				else if (Tableau[(int)CasePos.y - 1][(int)CasePos.x] == 21)
				{
					Tableau[(int)CasePos.y - 1][(int)CasePos.x] = 0;
					Tableau[(int)CasePos.y][(int)CasePos.x] = 0;
					Tableau[(int)CasePos.y + 1][(int)CasePos.x] = 0;
					Tableau[(int)CasePos.y + 2][(int)CasePos.x] = 0;
				}
				else if (Tableau[(int)CasePos.y - 2][(int)CasePos.x] == 21)
				{
					Tableau[(int)CasePos.y - 2][(int)CasePos.x] = 0;
					Tableau[(int)CasePos.y - 1][(int)CasePos.x] = 0;
					Tableau[(int)CasePos.y][(int)CasePos.x] = 0;
					Tableau[(int)CasePos.y + 1][(int)CasePos.x] = 0;
				}
				else if (Tableau[(int)CasePos.y - 3][(int)CasePos.x] == 21)
				{
					Tableau[(int)CasePos.y - 3][(int)CasePos.x] = 0;
					Tableau[(int)CasePos.y - 2][(int)CasePos.x] = 0;
					Tableau[(int)CasePos.y - 1][(int)CasePos.x] = 0;
					Tableau[(int)CasePos.y][(int)CasePos.x] = 0;
				}


				if (Tableau[(int)CasePos.y + 1][(int)CasePos.x] == 29)
					Tableau[(int)CasePos.y + 1][(int)CasePos.x] = 0;
				else if (Tableau[(int)CasePos.y + 2][(int)CasePos.x] == 29)
					Tableau[(int)CasePos.y + 2][(int)CasePos.x] = 0;
				else if (Tableau[(int)CasePos.y - 1][(int)CasePos.x] == 22)
				{
					Tableau[(int)CasePos.y - 1][(int)CasePos.x] = 0;
					Tableau[(int)CasePos.y][(int)CasePos.x] = 0;
					Tableau[(int)CasePos.y + 1][(int)CasePos.x] = 0;
				}
				else if (Tableau[(int)CasePos.y - 2][(int)CasePos.x] == 22)
				{
					Tableau[(int)CasePos.y - 2][(int)CasePos.x] = 0;
					Tableau[(int)CasePos.y - 1][(int)CasePos.x] = 0;
					Tableau[(int)CasePos.y][(int)CasePos.x] = 0;
				}


				Tableau[(int)CasePos.y][(int)CasePos.x] = 0;
			}
			else
				spSelecterTarget.setTexture(*ResourceManager::Instance()->GetTexture("Curseur pose"));
		}

	}

	if (sf::Joystick::isButtonPressed(0, 7))
	{
		if (StartIsPut == true && EndIsPut == true)
		{
			Sauvegarde();
		}
		else
		{
			PopUpActivated = 4;
		}
	}
}

void LevelEditor::CheckIfCaseIsFree()
{
	CasePos.x = spSelecterTarget.getPosition().x / 64;
	CasePos.y = spSelecterTarget.getPosition().y / 64;

	if (hud->Selection < 20)
	{
		if (Tableau[(int)CasePos.y][(int)CasePos.x] == 0)
		{
			CaseFreeOrNot.setSize(sf::Vector2f{ 64, 64 });
			CaseFreeOrNot.setFillColor(sf::Color{ 0, 255, 0, 100 });
			CaseFreeOrNot.setPosition((int)CasePos.x * 64, (int)CasePos.y * 64);
		}
		else
		{
			CaseFreeOrNot.setSize(sf::Vector2f{ 64, 64 });
			CaseFreeOrNot.setFillColor(sf::Color{ 255, 0, 0, 150 });
			CaseFreeOrNot.setPosition((int)CasePos.x * 64, (int)CasePos.y * 64);
		}
	}
	else if (hud->Selection == 20)
	{
		if (Tableau[(int)CasePos.y][(int)CasePos.x + 1] == 0 && Tableau[(int)CasePos.y][(int)CasePos.x + 2] == 0 && Tableau[(int)CasePos.y][(int)CasePos.x + 3] == 0)
		{
			CaseFreeOrNot.setSize(sf::Vector2f{ 4 * 64, 64 });
			CaseFreeOrNot.setFillColor(sf::Color{ 0, 255, 0, 100 });
			CaseFreeOrNot.setPosition((int)CasePos.x * 64, (int)CasePos.y * 64);
		}
		else
		{
			CaseFreeOrNot.setSize(sf::Vector2f{ 4 * 64, 64 });
			CaseFreeOrNot.setFillColor(sf::Color{ 255, 0, 0, 100 });
			CaseFreeOrNot.setPosition((int)CasePos.x * 64, (int)CasePos.y * 64);
		}
	}
	else if (hud->Selection == 21)
	{
		if (Tableau[(int)CasePos.y + 1][(int)CasePos.x] == 0 && Tableau[(int)CasePos.y + 2][(int)CasePos.x] == 0 && Tableau[(int)CasePos.y + 3][(int)CasePos.x] == 0)
		{
			CaseFreeOrNot.setSize(sf::Vector2f{ 64, 4 * 64 });
			CaseFreeOrNot.setFillColor(sf::Color{ 0, 255, 0, 100 });
			CaseFreeOrNot.setPosition((int)CasePos.x * 64, (int)CasePos.y * 64);
		}
		else
		{
			CaseFreeOrNot.setSize(sf::Vector2f{ 64, 4 * 64 });
			CaseFreeOrNot.setFillColor(sf::Color{ 255, 0, 0, 100 });
			CaseFreeOrNot.setPosition((int)CasePos.x * 64, (int)CasePos.y * 64);
		}
	}
	else if (hud->Selection == 22)
	{
		if (Tableau[(int)CasePos.y + 1][(int)CasePos.x] == 0 && Tableau[(int)CasePos.y + 2][(int)CasePos.x] == 0)
		{
			CaseFreeOrNot.setSize(sf::Vector2f{ 64, 3 * 64 });
			CaseFreeOrNot.setFillColor(sf::Color{ 0, 255, 0, 100 });
			CaseFreeOrNot.setPosition((int)CasePos.x * 64, (int)CasePos.y * 64);
		}
		else
		{
			CaseFreeOrNot.setSize(sf::Vector2f{ 64, 3 * 64 });
			CaseFreeOrNot.setFillColor(sf::Color{ 255, 0, 0, 100 });
			CaseFreeOrNot.setPosition((int)CasePos.x * 64, (int)CasePos.y * 64);
		}
	}
	else if (hud->Selection == 23)
	{
		if (Tableau[(int)CasePos.y][(int)CasePos.x] == 0)
		{
			CaseFreeOrNot.setSize(sf::Vector2f{ 64, 64 });
			CaseFreeOrNot.setFillColor(sf::Color{ 0, 255, 0, 100 });
			CaseFreeOrNot.setPosition((int)CasePos.x * 64, (int)CasePos.y * 64);
		}
		else
		{
			CaseFreeOrNot.setSize(sf::Vector2f{ 64, 64 });
			CaseFreeOrNot.setFillColor(sf::Color{ 255, 0, 0, 150 });
			CaseFreeOrNot.setPosition((int)CasePos.x * 64, (int)CasePos.y * 64);
		}
	}
	else if (hud->Selection == 24)
	{
		if (Tableau[(int)CasePos.y + 1][(int)CasePos.x] >= 1 && Tableau[(int)CasePos.y + 1][(int)CasePos.x] <= 6)
		{
			CaseFreeOrNot.setSize(sf::Vector2f{ 64, 64 });
			CaseFreeOrNot.setFillColor(sf::Color{ 0, 255, 0, 100 });
			CaseFreeOrNot.setPosition((int)CasePos.x * 64, (int)CasePos.y * 64);
		}
		else
		{
			CaseFreeOrNot.setSize(sf::Vector2f{ 64, 64 });
			CaseFreeOrNot.setFillColor(sf::Color{ 255, 0, 0, 150 });
			CaseFreeOrNot.setPosition((int)CasePos.x * 64, (int)CasePos.y * 64);
		}
	}
	else if (hud->Selection == 25)
	{
		if (Tableau[(int)CasePos.y + 1][(int)CasePos.x] >= 1 && Tableau[(int)CasePos.y + 1][(int)CasePos.x] <= 6)
		{
			CaseFreeOrNot.setSize(sf::Vector2f{ 64, 64 });
			CaseFreeOrNot.setFillColor(sf::Color{ 0, 255, 0, 100 });
			CaseFreeOrNot.setPosition((int)CasePos.x * 64, (int)CasePos.y * 64);
		}
		else
		{
			CaseFreeOrNot.setSize(sf::Vector2f{ 64, 64 });
			CaseFreeOrNot.setFillColor(sf::Color{ 255, 0, 0, 150 });
			CaseFreeOrNot.setPosition((int)CasePos.x * 64, (int)CasePos.y * 64);
		}
	}
	else if (hud->Selection == 26)
	{
		if (Tableau[(int)CasePos.y + 1][(int)CasePos.x] >= 1 && Tableau[(int)CasePos.y + 1][(int)CasePos.x] <= 6)
		{
			CaseFreeOrNot.setSize(sf::Vector2f{ 64, 64 });
			CaseFreeOrNot.setFillColor(sf::Color{ 0, 255, 0, 100 });
			CaseFreeOrNot.setPosition((int)CasePos.x * 64, (int)CasePos.y * 64);
		}
		else
		{
			CaseFreeOrNot.setSize(sf::Vector2f{ 64, 64 });
			CaseFreeOrNot.setFillColor(sf::Color{ 255, 0, 0, 150 });
			CaseFreeOrNot.setPosition((int)CasePos.x * 64, (int)CasePos.y * 64);
		}
	}

	m_actualWindow->draw(CaseFreeOrNot);
}

//sf::Vector2f LevelEditor::CheckPointManager()
//{
//	for (int y = 0; y < Size_Y; y++)
//	{
//		for (int x = (_LastCheckPos.x + 1920) / 64; x < (_LastCheckPos.x + 3840) / 64; x++)
//		{
//			if (Tableau[y][x] >= 1 && Tableau[y][x] <= 6 && Tableau[y - 1][x] == 0)
//			{
//				return sf::Vector2f(x * 64, y * 64);
//			}
//		}
//	}
//	return sf::Vector2f();
//}

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

	if (isNewLevel == false)
		GameManager::Instance()->m_ActualScene = new SaveEditor(Size_X, Size_Y, Save, SelectionBackground, false, "");

	else if (isNewLevel == true)
		PopUpActivated = 3;
}

void LevelEditor::SaveIt()
{
	std::ofstream SaveFile;

	SaveFile.open("Ressources/Sauvegardes/" + LevelName + ".txt", std::ios_base::out);

	SaveFile << Size_X << "\n";
	SaveFile << Size_Y << "\n";
	SaveFile << SelectionBackground << "\n";
	SaveFile << Save;

	SaveFile.close();

	GameManager::Instance()->LoadScene(e_Enum::e_Scene::OPENLEVELEDITOR);
}

void LevelEditor::BackgroundChoice()
{
	if (SelectionBackground == 1)
		spBackground.setTexture(*ResourceManager::Instance()->GetTexture("Thème1"));
	else if (SelectionBackground == 2)
		spBackground.setTexture(*ResourceManager::Instance()->GetTexture("Thème2"));

	spFlèches[0].setPosition(70, 230);
	spFlèches[1].setPosition(310, 230);
	spBackground.setPosition(105, 200);

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

void LevelEditor::AnimTiles()
{
	if (AnimBoostClock.getElapsedTime().asMilliseconds() > 50)
	{
		if (FrameIndexBoost < 10)
		{
			FrameIndexBoost++;
		}
		else
			FrameIndexBoost = 0;

		AnimBoostClock.restart();
	}

	if (AnimCollectClock.getElapsedTime().asMilliseconds() > 50)
	{
		if (FrameIndexCollect < 17)
		{
			FrameIndexCollect++;
		}
		else
			FrameIndexCollect = 0;

		AnimCollectClock.restart();
	}

	if (AnimElectClock.getElapsedTime().asMilliseconds() > 50)
	{
		if (FrameIndexElect < 8)
		{
			FrameIndexElect++;
		}
		else
			FrameIndexElect = 0;

		AnimElectClock.restart();
	}
}
