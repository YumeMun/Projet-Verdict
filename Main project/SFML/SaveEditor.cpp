#include "SaveEditor.h"
#include "ResourceManager.h"
#include "GameManager.h"
#include <fstream>
#include "dirent.h"

SaveEditor::SaveEditor()
{
}

SaveEditor::SaveEditor(int _SizeX, int _SizeY, std::string _Save, int _SelectionBackground, bool _RenameLevel, std::string _LastLevelName)
{
	m_actualWindow = GameManager::Instance()->GetWindow();

	RenameLevel = _RenameLevel;
	LevelName = _LastLevelName;
	LastLevelName = _LastLevelName;

	spBackground.setTexture(*ResourceManager::Instance()->GetTexture("Background interface"));
	spBackground.setColor(sf::Color{ 100, 100, 100, 255 });

	SaveText.setFont(*ResourceManager::Instance()->GetFont("Font"));
	SaveText.setCharacterSize(40);
	SaveText.setFillColor(sf::Color::White);

	NameText.setFont(*ResourceManager::Instance()->GetFont("Font"));
	NameText.setCharacterSize(40);
	NameText.setFillColor(sf::Color::White);

	Save = _Save;
	Size_X = _SizeX;
	Size_Y = _SizeY;
	SelectionBackground = _SelectionBackground;

	if (RenameLevel == true)
	{
		std::ifstream LoadFile;

		LoadFile.open("Ressources/Sauvegardes/" + LastLevelName + ".txt", std::ios_base::in);

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

		std::string Temp = "Ressources/Sauvegardes/" + LastLevelName + ".txt";
		remove(Temp.c_str());

		for (int y = 0; y < Size_Y; y++)
		{
			for (int x = 0; x < Size_X; x++)
			{
				Save += std::to_string(Tableau[y][x]) + " ";
			}

			Save += "\n";
		}
	}

	for (int i = 0; i < 2; i++)
	{
		spButtons[i].setTexture(*ResourceManager::Instance()->GetTexture("Menu bouton non sélectionné"));
		spButtons[i].setOrigin(spButtons[i].getGlobalBounds().width / 2, spButtons[i].getGlobalBounds().height / 2);
		spButtons[i].setPosition(1010, 450 + i * 200);
	}

	KeyRect.setOutlineColor(sf::Color::White);
	KeyRect.setOutlineThickness(2);

	for (int i = 0; i < 60; i++)
	{
		KeyText[i].setFont(*ResourceManager::Instance()->GetFont("Font"));
		KeyText[i].setCharacterSize(30);
		KeyText[i].setFillColor(sf::Color::White);
	}

	for (int i = 0; i < 4; i++)
	{
		Key[0].setTexture(*ResourceManager::Instance()->GetTexture("Key1"));
		Key[1].setTexture(*ResourceManager::Instance()->GetTexture("Key2"));
		Key[2].setTexture(*ResourceManager::Instance()->GetTexture("Key3"));
		Key[3].setTexture(*ResourceManager::Instance()->GetTexture("Key4"));

		Key[i].setColor(sf::Color{ 255, 255, 255, 255 });
	}


	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 12; x++)
		{
			Keyboard[y][x] = BASICKEY;
			Keyboard[1][10] = BACK;
			Keyboard[1][11] = NONE;
			Keyboard[2][10] = ENTER;
			Keyboard[2][11] = NONE;
			Keyboard[3][0] = BACK;
			Keyboard[3][1] = NONE;
			Keyboard[3][11] = NONE;
			Keyboard[4][2] = SPACE;
			Keyboard[4][3] = NONE;
			Keyboard[4][4] = NONE;
			Keyboard[4][5] = NONE;
			Keyboard[4][6] = NONE;
			Keyboard[4][7] = NONE;
			Keyboard[4][8] = NONE;
			Keyboard[4][9] = NONE;

			Keyboard[1][0] = BASICKEY_SELECTED;
		}
	}

	Last_X = 0;
	Last_Y = 1;

	X = 0;
	Y = 1;

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

	ObjSeparator = ".txt";
	LoadLevels();
}

SaveEditor::~SaveEditor()
{
}

void SaveEditor::Update()
{
	SaveText.setString("Donnez un nom à votre niveau : ");
	SaveText.setOrigin(SaveText.getGlobalBounds().width / 2, 0);
	SaveText.setPosition(960, 420);

	NameText.setString(LevelName);
	NameText.setOrigin(NameText.getGlobalBounds().width / 2, 0);
	NameText.setPosition(960, 620);

	if (PopUpActivated == 1)
	{
		PopUpText[0].setString("	Voulez-vous vraiment appeler\n		votre niveau « " + LevelName + " » ?");
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
		PopUpText[0].setString("Niveau sauvegardé avec succès !");
		PopUpText[0].setPosition(640, 510);

		if (SelectionTimer.getElapsedTime().asSeconds() > 1.5)
		{
			SaveIt();
		}
	}

	if (PopUpActivated == 3)
	{
		PopUpText[0].setString("Vous ne pouvez pas utiliser le nom\n		d'un niveau déjà existant");
		PopUpText[0].setPosition(640, 510);

		if (sf::Joystick::isButtonPressed(0, 0) && SelectionTimer.getElapsedTime().asMilliseconds() > 500)
		{
			PopUpActivated = 0;
			SelectionTimer.restart();
		}
	}
}

void SaveEditor::Display()
{
	m_actualWindow->draw(spBackground);

	for (int i = 0; i < 2; i++)
	{
		m_actualWindow->draw(spButtons[i]);
	}

	m_actualWindow->draw(SaveText);
	m_actualWindow->draw(NameText);

	if (PopUpActivated == 0)
		VirtualKeyboard();

	m_actualWindow->draw(spBoutonRetour);

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

void SaveEditor::EventManager(sf::Event p_pollingEvent)
{
	if (RenameLevel == false)
	{
		if (sf::Joystick::isButtonPressed(0, 1))
		{
			std::ofstream TempSave;

			TempSave.open("Ressources/Sauvegardes/TempSave.txt", std::ios_base::out);

			TempSave << Save;

			TempSave.close();

			GameManager::Instance()->m_ActualScene = new LevelEditor(Size_X, Size_Y, "", false);
		}
	}
	else if (RenameLevel == true)
	{
		if (sf::Joystick::isButtonPressed(0, 1))
		{
			GameManager::Instance()->LoadScene(e_Enum::e_Scene::OPENLEVELEDITOR);
		}
	}
}

void SaveEditor::SaveIt()
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

void SaveEditor::VirtualKeyboard()
{
	if (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X) <= -50 && clock.getElapsedTime().asMilliseconds() > 200)
	{
		if (X > 0)
		{
			Last_X = X;
			Last_Y = Y;

			if (Y == 4 && X >= 2 && X <= 9)
				X = 1;
			else if (Y == 4 && X == 10)
				X = 2;
			else if (Y == 3 && X == 2)
				X = 0;
			else
				X--;


			if (Keyboard[Y][X] == BASICKEY)
				Keyboard[Y][X] = BASICKEY_SELECTED;
			else if (Keyboard[Y][X] == BACK)
				Keyboard[Y][X] = BACK_SELECTED;
			else if (Keyboard[Y][X] == ENTER)
				Keyboard[Y][X] = ENTER_SELECTED;
			else if (Keyboard[Y][X] == SPACE)
				Keyboard[Y][X] = SPACE_SELECTED;


			if (Keyboard[Last_Y][Last_X] == BASICKEY_SELECTED)
				Keyboard[Last_Y][Last_X] = BASICKEY;
			else if (Keyboard[Last_Y][Last_X] == BACK_SELECTED)
				Keyboard[Last_Y][Last_X] = BACK;
			else if (Keyboard[Last_Y][Last_X] == ENTER_SELECTED)
				Keyboard[Last_Y][Last_X] = ENTER;
			else if (Keyboard[Last_Y][Last_X] == SPACE_SELECTED)
				Keyboard[Last_Y][Last_X] = SPACE;
		}
		clock.restart();
	}
	else if (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X) >= 50 && clock.getElapsedTime().asMilliseconds() > 200)
	{
		if (X < 11)
		{
			Last_X = X;
			Last_Y = Y;

			if (Y == 4 && X >= 2 && X <= 9)
				X = 10;
			else if (Y == 3 && X == 0)
				X = 2;
			else if (Y == 2 && (X == 10 || X == 11))
				X = 10;
			else if (Y == 1 && (X == 10 || X == 11))
				X = 10;
			else
				X++;

			if (Keyboard[Last_Y][Last_X] == BASICKEY_SELECTED)
				Keyboard[Last_Y][Last_X] = BASICKEY;
			else if (Keyboard[Last_Y][Last_X] == BACK_SELECTED)
				Keyboard[Last_Y][Last_X] = BACK;
			else if (Keyboard[Last_Y][Last_X] == ENTER_SELECTED)
				Keyboard[Last_Y][Last_X] = ENTER;
			else if (Keyboard[Last_Y][Last_X] == SPACE_SELECTED)
				Keyboard[Last_Y][Last_X] = SPACE;

			if (Keyboard[Y][X] == BASICKEY)
				Keyboard[Y][X] = BASICKEY_SELECTED;
			else if (Keyboard[Y][X] == BACK)
				Keyboard[Y][X] = BACK_SELECTED;
			else if (Keyboard[Y][X] == ENTER)
				Keyboard[Y][X] = ENTER_SELECTED;
			else if (Keyboard[Y][X] == SPACE)
				Keyboard[Y][X] = SPACE_SELECTED;
		}
		clock.restart();
	}

	if (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y) <= -50 && clock.getElapsedTime().asMilliseconds() > 200)
	{
		if (Y > 0)
		{
			Last_X = X;
			Last_Y = Y;

			Y--;

			if (Y == 3 && X == 1)
				X = 0;

			if (Y == 3 && X == 11)
				X = 10;

			if (Keyboard[Y][X] == BASICKEY)
				Keyboard[Y][X] = BASICKEY_SELECTED;
			else if (Keyboard[Y][X] == BACK)
				Keyboard[Y][X] = BACK_SELECTED;
			else if (Keyboard[Y][X] == ENTER)
				Keyboard[Y][X] = ENTER_SELECTED;
			else if (Keyboard[Y][X] == SPACE)
				Keyboard[Y][X] = SPACE_SELECTED;


			if (Keyboard[Last_Y][Last_X] == BASICKEY_SELECTED)
				Keyboard[Last_Y][Last_X] = BASICKEY;
			else if (Keyboard[Last_Y][Last_X] == BACK_SELECTED)
				Keyboard[Last_Y][Last_X] = BACK;
			else if (Keyboard[Last_Y][Last_X] == ENTER_SELECTED)
				Keyboard[Last_Y][Last_X] = ENTER;
			else if (Keyboard[Last_Y][Last_X] == SPACE_SELECTED)
				Keyboard[Last_Y][Last_X] = SPACE;
		}
		clock.restart();
	}
	else if (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y) >= 50 && clock.getElapsedTime().asMilliseconds() > 200)
	{
		if (Y < 4)
		{
			Last_X = X;
			Last_Y = Y;

			Y++;

			if (Y == 4 && X >= 2 && X <= 9)
				X = 2;
			else if (Y == 3 && X == 1)
				X = 0;
			else if (Y == 1 && X == 11)
				X = 10;

			if (Keyboard[Y][X] == BASICKEY)
				Keyboard[Y][X] = BASICKEY_SELECTED;
			else if (Keyboard[Y][X] == BACK)
				Keyboard[Y][X] = BACK_SELECTED;
			else if (Keyboard[Y][X] == ENTER)
				Keyboard[Y][X] = ENTER_SELECTED;
			else if (Keyboard[Y][X] == SPACE)
				Keyboard[Y][X] = SPACE_SELECTED;


			if (Keyboard[Last_Y][Last_X] == BASICKEY_SELECTED)
				Keyboard[Last_Y][Last_X] = BASICKEY;
			else if (Keyboard[Last_Y][Last_X] == BACK_SELECTED)
				Keyboard[Last_Y][Last_X] = BACK;
			else if (Keyboard[Last_Y][Last_X] == ENTER_SELECTED)
				Keyboard[Last_Y][Last_X] = ENTER;
			else if (Keyboard[Last_Y][Last_X] == SPACE_SELECTED)
				Keyboard[Last_Y][Last_X] = SPACE;

		}
		clock.restart();
	}


	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 12; x++)
		{
			if (y == 0 || y == 2)
				KeyPos.x = (float)576 + x * 64;
			else if (y == 3)
				KeyPos.x = (float)630 + x * 64;
			else if (y == 1 || y == 4)
				KeyPos.x = (float)600 + x * 64;

			KeyPos.y = (float)750 + y * 64;

			switch (Keyboard[y][x])
			{
			case NONE:
				break;
			case BASICKEY:
				Key[0].setPosition(KeyPos);
				Key[0].setColor(sf::Color{ 255, 255, 255, 255 });
				m_actualWindow->draw(Key[0]);
				break;
			case BACK:
				Key[1].setPosition(KeyPos);
				Key[1].setColor(sf::Color{ 255, 255, 255, 255 });
				m_actualWindow->draw(Key[1]);
				break;
			case ENTER:
				Key[2].setPosition(KeyPos);
				Key[2].setColor(sf::Color{ 255, 255, 255, 255 });
				m_actualWindow->draw(Key[2]);
				break;
			case SPACE:
				Key[3].setPosition(KeyPos);
				Key[3].setColor(sf::Color{ 255, 255, 255, 255 });
				m_actualWindow->draw(Key[3]);
				break;
			case BASICKEY_SELECTED:
				Key[0].setPosition(KeyPos);
				Key[0].setColor(sf::Color{ 150, 150, 150, 255 });
				m_actualWindow->draw(Key[0]);
				break;
			case BACK_SELECTED:
				Key[1].setPosition(KeyPos);
				Key[1].setColor(sf::Color{ 150, 150, 150, 255 });
				m_actualWindow->draw(Key[1]);
				break;
			case ENTER_SELECTED:
				Key[2].setPosition(KeyPos);
				Key[2].setColor(sf::Color{ 150, 150, 150, 255 });
				m_actualWindow->draw(Key[2]);
				break;
			case SPACE_SELECTED:
				Key[3].setPosition(KeyPos);
				Key[3].setColor(sf::Color{ 150, 150, 150, 255 });
				m_actualWindow->draw(Key[3]);
				break;
			}
		}
	}

	for (int i = 0; i < 60; i++)
	{
		KeyText[0].setString("1");
		KeyText[0].setPosition(597 + 0 * 64, 760 + 0 * 64);

		KeyText[1].setString("2");
		KeyText[1].setPosition(597 + 1 * 64, 760 + 0 * 64);

		KeyText[2].setString("3");
		KeyText[2].setPosition(597 + 2 * 64, 760 + 0 * 64);

		KeyText[3].setString("4");
		KeyText[3].setPosition(597 + 3 * 64, 760 + 0 * 64);

		KeyText[4].setString("5");
		KeyText[4].setPosition(597 + 4 * 64, 760 + 0 * 64);

		KeyText[5].setString("6");
		KeyText[5].setPosition(597 + 5 * 64, 760 + 0 * 64);

		KeyText[6].setString("7");
		KeyText[6].setPosition(597 + 6 * 64, 760 + 0 * 64);

		KeyText[7].setString("8");
		KeyText[7].setPosition(597 + 7 * 64, 760 + 0 * 64);

		KeyText[8].setString("9");
		KeyText[8].setPosition(597 + 8 * 64, 760 + 0 * 64);

		KeyText[9].setString("0");
		KeyText[9].setPosition(597 + 9 * 64, 760 + 0 * 64);

		KeyText[10].setString("-");
		KeyText[10].setPosition(597 + 10 * 64, 760 + 0 * 64);

		KeyText[11].setString("+");
		KeyText[11].setPosition(597 + 11 * 64, 760 + 0 * 64);

		if (Maj == false)
		{
			KeyText[12].setString("a");
			KeyText[12].setPosition(621 + 0 * 64, 760 + 1 * 64);

			KeyText[13].setString("z");
			KeyText[13].setPosition(621 + 1 * 64, 760 + 1 * 64);

			KeyText[14].setString("e");
			KeyText[14].setPosition(621 + 2 * 64, 760 + 1 * 64);

			KeyText[15].setString("r");
			KeyText[15].setPosition(621 + 3 * 64, 760 + 1 * 64);

			KeyText[16].setString("t");
			KeyText[16].setPosition(621 + 4 * 64, 760 + 1 * 64);

			KeyText[17].setString("y");
			KeyText[17].setPosition(621 + 5 * 64, 760 + 1 * 64);

			KeyText[18].setString("u");
			KeyText[18].setPosition(621 + 6 * 64, 760 + 1 * 64);

			KeyText[19].setString("i");
			KeyText[19].setPosition(621 + 7 * 64, 760 + 1 * 64);

			KeyText[20].setString("o");
			KeyText[20].setPosition(621 + 8 * 64, 760 + 1 * 64);

			KeyText[21].setString("p");
			KeyText[21].setPosition(621 + 9 * 64, 760 + 1 * 64);
		}
		else if (Maj == true)
		{
			KeyText[12].setString("A");
			KeyText[12].setPosition(621 + 0 * 64, 760 + 1 * 64);

			KeyText[13].setString("Z");
			KeyText[13].setPosition(621 + 1 * 64, 760 + 1 * 64);

			KeyText[14].setString("E");
			KeyText[14].setPosition(621 + 2 * 64, 760 + 1 * 64);

			KeyText[15].setString("R");
			KeyText[15].setPosition(621 + 3 * 64, 760 + 1 * 64);

			KeyText[16].setString("T");
			KeyText[16].setPosition(621 + 4 * 64, 760 + 1 * 64);

			KeyText[17].setString("Y");
			KeyText[17].setPosition(621 + 5 * 64, 760 + 1 * 64);

			KeyText[18].setString("U");
			KeyText[18].setPosition(621 + 6 * 64, 760 + 1 * 64);

			KeyText[19].setString("I");
			KeyText[19].setPosition(621 + 7 * 64, 760 + 1 * 64);

			KeyText[20].setString("O");
			KeyText[20].setPosition(621 + 8 * 64, 760 + 1 * 64);

			KeyText[21].setString("P");
			KeyText[21].setPosition(621 + 9 * 64, 760 + 1 * 64);
		}

		KeyText[22].setString("Retour");
		KeyText[22].setPosition(617 + 10 * 64, 763 + 1 * 64);

		if (Maj == false)
		{
			KeyText[23].setString("q");
			KeyText[23].setPosition(597 + 0 * 64, 760 + 2 * 64);

			KeyText[24].setString("s");
			KeyText[24].setPosition(597 + 1 * 64, 760 + 2 * 64);

			KeyText[25].setString("d");
			KeyText[25].setPosition(597 + 2 * 64, 760 + 2 * 64);

			KeyText[26].setString("f");
			KeyText[26].setPosition(597 + 3 * 64, 760 + 2 * 64);

			KeyText[27].setString("g");
			KeyText[27].setPosition(597 + 4 * 64, 760 + 2 * 64);

			KeyText[28].setString("h");
			KeyText[28].setPosition(597 + 5 * 64, 760 + 2 * 64);

			KeyText[29].setString("j");
			KeyText[29].setPosition(597 + 6 * 64, 760 + 2 * 64);

			KeyText[30].setString("k");
			KeyText[30].setPosition(597 + 7 * 64, 760 + 2 * 64);

			KeyText[31].setString("l");
			KeyText[31].setPosition(597 + 8 * 64, 760 + 2 * 64);

			KeyText[32].setString("m");
			KeyText[32].setPosition(597 + 9 * 64, 760 + 2 * 64);
		}
		else if (Maj == true)
		{
			KeyText[23].setString("Q");
			KeyText[23].setPosition(597 + 0 * 64, 760 + 2 * 64);

			KeyText[24].setString("S");
			KeyText[24].setPosition(597 + 1 * 64, 760 + 2 * 64);

			KeyText[25].setString("D");
			KeyText[25].setPosition(597 + 2 * 64, 760 + 2 * 64);

			KeyText[26].setString("F");
			KeyText[26].setPosition(597 + 3 * 64, 760 + 2 * 64);

			KeyText[27].setString("G");
			KeyText[27].setPosition(597 + 4 * 64, 760 + 2 * 64);

			KeyText[28].setString("H");
			KeyText[28].setPosition(597 + 5 * 64, 760 + 2 * 64);

			KeyText[29].setString("J");
			KeyText[29].setPosition(597 + 6 * 64, 760 + 2 * 64);

			KeyText[30].setString("K");
			KeyText[30].setPosition(597 + 7 * 64, 760 + 2 * 64);

			KeyText[31].setString("L");
			KeyText[31].setPosition(597 + 8 * 64, 760 + 2 * 64);

			KeyText[32].setString("M");
			KeyText[32].setPosition(597 + 9 * 64, 760 + 2 * 64);
		}

		KeyText[33].setString("Entrée");
		KeyText[33].setPosition(605 + 10 * 64, 763 + 2 * 64);

		KeyText[34].setString("Shift");
		KeyText[34].setPosition(655 + 0 * 64, 763 + 3 * 64);

		if (Maj == false)
		{
			KeyText[35].setString("w");
			KeyText[35].setPosition(647 + 2 * 64, 760 + 3 * 64);

			KeyText[36].setString("x");
			KeyText[36].setPosition(647 + 3 * 64, 760 + 3 * 64);

			KeyText[37].setString("c");
			KeyText[37].setPosition(647 + 4 * 64, 760 + 3 * 64);

			KeyText[38].setString("v");
			KeyText[38].setPosition(647 + 5 * 64, 760 + 3 * 64);

			KeyText[39].setString("b");
			KeyText[39].setPosition(647 + 6 * 64, 760 + 3 * 64);

			KeyText[40].setString("n");
			KeyText[40].setPosition(647 + 7 * 64, 760 + 3 * 64);
		}
		else if (Maj == true)
		{
			KeyText[35].setString("W");
			KeyText[35].setPosition(647 + 2 * 64, 760 + 3 * 64);

			KeyText[36].setString("X");
			KeyText[36].setPosition(647 + 3 * 64, 760 + 3 * 64);

			KeyText[37].setString("C");
			KeyText[37].setPosition(647 + 4 * 64, 760 + 3 * 64);

			KeyText[38].setString("V");
			KeyText[38].setPosition(647 + 5 * 64, 760 + 3 * 64);

			KeyText[39].setString("B");
			KeyText[39].setPosition(647 + 6 * 64, 760 + 3 * 64);

			KeyText[40].setString("N");
			KeyText[40].setPosition(647 + 7 * 64, 760 + 3 * 64);
		}


		KeyText[41].setString(",");
		KeyText[41].setPosition(647 + 8 * 64, 760 + 3 * 64);

		KeyText[42].setString(".");
		KeyText[42].setPosition(647 + 9 * 64, 760 + 3 * 64);

		KeyText[43].setString("'");
		KeyText[43].setPosition(647 + 10 * 64, 760 + 3 * 64);

		KeyText[44].setString("(");
		KeyText[44].setPosition(621 + 0 * 64, 765 + 4 * 64);

		KeyText[45].setString(")");
		KeyText[45].setPosition(621 + 1 * 64, 765 + 4 * 64);

		KeyText[46].setString("Espace");
		KeyText[46].setPosition(621 + 5 * 64, 765 + 4 * 64);

		KeyText[47].setString(":");
		KeyText[47].setPosition(621 + 10 * 64, 765 + 4 * 64);

		KeyText[48].setString(";");
		KeyText[48].setPosition(621 + 11 * 64, 765 + 4 * 64);

		m_actualWindow->draw(KeyText[i]);
	}

	if (sf::Joystick::isButtonPressed(0, 0) && clock.getElapsedTime().asMilliseconds() > 300)
	{
		if (Keyboard[3][0] == BACK_SELECTED)
		{
			if (Maj == false)
				Maj = true;
			else if (Maj == true)
				Maj = false;
		}
		else if (Keyboard[1][10] == BACK_SELECTED)
		{
			if (LevelName.length() >= 1)
				LevelName.pop_back();
		}
		else if (Keyboard[2][10] == ENTER_SELECTED && SelectionTimer.getElapsedTime().asMilliseconds() > 300)
		{
			bool SameName = false;

			for (int i = 0; i < FilesNumber; i++)
			{
				if (LoadLevelNames[i] == LevelName)
				{
					SameName = true;
					PopUpActivated = 3;
					SelectionTimer.restart();
				}
			}
			if (SameName == false)
			{
				PopUpActivated = 1;
				SelectionTimer.restart();
			}
		}

		else if (Keyboard[0][0] == BASICKEY_SELECTED)
			LevelName += "1";
		else if (Keyboard[0][1] == BASICKEY_SELECTED)
			LevelName += "2";
		else if (Keyboard[0][2] == BASICKEY_SELECTED)
			LevelName += "3";
		else if (Keyboard[0][3] == BASICKEY_SELECTED)
			LevelName += "4";
		else if (Keyboard[0][4] == BASICKEY_SELECTED)
			LevelName += "5";
		else if (Keyboard[0][5] == BASICKEY_SELECTED)
			LevelName += "6";
		else if (Keyboard[0][6] == BASICKEY_SELECTED)
			LevelName += "7";
		else if (Keyboard[0][7] == BASICKEY_SELECTED)
			LevelName += "8";
		else if (Keyboard[0][8] == BASICKEY_SELECTED)
			LevelName += "9";
		else if (Keyboard[0][9] == BASICKEY_SELECTED)
			LevelName += "0";
		else if (Keyboard[0][10] == BASICKEY_SELECTED)
			LevelName += "-";
		else if (Keyboard[0][11] == BASICKEY_SELECTED)
			LevelName += "+";

		if (Maj == false)
		{
			if (Keyboard[1][0] == BASICKEY_SELECTED)
				LevelName += "a";
			else if (Keyboard[1][1] == BASICKEY_SELECTED)
				LevelName += "z";
			else if (Keyboard[1][2] == BASICKEY_SELECTED)
				LevelName += "e";
			else if (Keyboard[1][3] == BASICKEY_SELECTED)
				LevelName += "r";
			else if (Keyboard[1][4] == BASICKEY_SELECTED)
				LevelName += "t";
			else if (Keyboard[1][5] == BASICKEY_SELECTED)
				LevelName += "y";
			else if (Keyboard[1][6] == BASICKEY_SELECTED)
				LevelName += "u";
			else if (Keyboard[1][7] == BASICKEY_SELECTED)
				LevelName += "i";
			else if (Keyboard[1][8] == BASICKEY_SELECTED)
				LevelName += "o";
			else if (Keyboard[1][9] == BASICKEY_SELECTED)
				LevelName += "p";
			else if (Keyboard[2][0] == BASICKEY_SELECTED)
				LevelName += "q";
			else if (Keyboard[2][1] == BASICKEY_SELECTED)
				LevelName += "s";
			else if (Keyboard[2][2] == BASICKEY_SELECTED)
				LevelName += "d";
			else if (Keyboard[2][3] == BASICKEY_SELECTED)
				LevelName += "f";
			else if (Keyboard[2][4] == BASICKEY_SELECTED)
				LevelName += "g";
			else if (Keyboard[2][5] == BASICKEY_SELECTED)
				LevelName += "h";
			else if (Keyboard[2][6] == BASICKEY_SELECTED)
				LevelName += "j";
			else if (Keyboard[2][7] == BASICKEY_SELECTED)
				LevelName += "k";
			else if (Keyboard[2][8] == BASICKEY_SELECTED)
				LevelName += "l";
			else if (Keyboard[2][9] == BASICKEY_SELECTED)
				LevelName += "m";
			else if (Keyboard[3][2] == BASICKEY_SELECTED)
				LevelName += "w";
			else if (Keyboard[3][3] == BASICKEY_SELECTED)
				LevelName += "x";
			else if (Keyboard[3][4] == BASICKEY_SELECTED)
				LevelName += "c";
			else if (Keyboard[3][5] == BASICKEY_SELECTED)
				LevelName += "v";
			else if (Keyboard[3][6] == BASICKEY_SELECTED)
				LevelName += "b";
			else if (Keyboard[3][7] == BASICKEY_SELECTED)
				LevelName += "n";
		}
		else if (Maj == true)
		{
			if (Keyboard[1][0] == BASICKEY_SELECTED)
				LevelName += "A";
			else if (Keyboard[1][1] == BASICKEY_SELECTED)
				LevelName += "Z";
			else if (Keyboard[1][2] == BASICKEY_SELECTED)
				LevelName += "E";
			else if (Keyboard[1][3] == BASICKEY_SELECTED)
				LevelName += "R";
			else if (Keyboard[1][4] == BASICKEY_SELECTED)
				LevelName += "T";
			else if (Keyboard[1][5] == BASICKEY_SELECTED)
				LevelName += "Y";
			else if (Keyboard[1][6] == BASICKEY_SELECTED)
				LevelName += "U";
			else if (Keyboard[1][7] == BASICKEY_SELECTED)
				LevelName += "I";
			else if (Keyboard[1][8] == BASICKEY_SELECTED)
				LevelName += "O";
			else if (Keyboard[1][9] == BASICKEY_SELECTED)
				LevelName += "P";
			else if (Keyboard[2][0] == BASICKEY_SELECTED)
				LevelName += "Q";
			else if (Keyboard[2][1] == BASICKEY_SELECTED)
				LevelName += "S";
			else if (Keyboard[2][2] == BASICKEY_SELECTED)
				LevelName += "D";
			else if (Keyboard[2][3] == BASICKEY_SELECTED)
				LevelName += "F";
			else if (Keyboard[2][4] == BASICKEY_SELECTED)
				LevelName += "G";
			else if (Keyboard[2][5] == BASICKEY_SELECTED)
				LevelName += "H";
			else if (Keyboard[2][6] == BASICKEY_SELECTED)
				LevelName += "J";
			else if (Keyboard[2][7] == BASICKEY_SELECTED)
				LevelName += "K";
			else if (Keyboard[2][8] == BASICKEY_SELECTED)
				LevelName += "L";
			else if (Keyboard[2][9] == BASICKEY_SELECTED)
				LevelName += "M";
			else if (Keyboard[3][2] == BASICKEY_SELECTED)
				LevelName += "W";
			else if (Keyboard[3][3] == BASICKEY_SELECTED)
				LevelName += "X";
			else if (Keyboard[3][4] == BASICKEY_SELECTED)
				LevelName += "C";
			else if (Keyboard[3][5] == BASICKEY_SELECTED)
				LevelName += "V";
			else if (Keyboard[3][6] == BASICKEY_SELECTED)
				LevelName += "B";
			else if (Keyboard[3][7] == BASICKEY_SELECTED)
				LevelName += "N";
		}

		if (Keyboard[3][8] == BASICKEY_SELECTED)
			LevelName += ",";
		else if (Keyboard[3][9] == BASICKEY_SELECTED)
			LevelName += ".";
		else if (Keyboard[3][10] == BASICKEY_SELECTED)
			LevelName += "'";
		else if (Keyboard[4][0] == BASICKEY_SELECTED)
			LevelName += "(";
		else if (Keyboard[4][1] == BASICKEY_SELECTED)
			LevelName += ")";
		else if (Keyboard[4][2] == SPACE_SELECTED)
			LevelName += " ";
		else if (Keyboard[4][10] == BASICKEY_SELECTED)
			LevelName += ":";
		else if (Keyboard[4][11] == BASICKEY_SELECTED)
			LevelName += ";";

		clock.restart();
	}
}

void SaveEditor::LoadLevels()
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
		LoadLevelNames[i] = data;
		LoadNames.erase(0, pos + ObjSeparator.length());

		if (LoadLevelNames[i] != "")
		{
			FilesNumber++;
		}
	}
}