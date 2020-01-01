#include "Map.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include <fstream>

Map::Map()
{
}

Map::Map(std::string _LevelName)
{
	std::cout << "Map constructor" << std::endl;

	m_actualWindow = GameManager::Instance()->GetWindow();

	for (int i = 0; i < 4; i++)
	{
		Plan[i].setTexture(*ResourceManager::Instance()->GetTexture("Plan" + std::to_string(i + 1)));
		Plan2[i].setTexture(*ResourceManager::Instance()->GetTexture("Plan" + std::to_string(i + 1)));

		Plan2[i].setPosition(1920 * 2, 0);

		Plan[i].setScale(2, 2);
		Plan2[i].setScale(2, 2);
	}

	for (int i = 0; i < 8; i++)
	{
		spTile[i].setTexture(*ResourceManager::Instance()->GetTexture("Case" + std::to_string(i + 1)));
	}

	for (int i = 0; i < 2; i++)
	{
		Plan1[i].setTexture(*ResourceManager::Instance()->GetTexture("Plan1_" + std::to_string(i)));
		Plan1[i].setScale(2, 2);
		Plan1[i].setPosition(Plan1[i].getGlobalBounds().width * i, 0);
	}

	Collectible.setRadius(30);
	Collectible.setFillColor(sf::Color::Green);

	std::cout << _LevelName << std::endl;

	std::ifstream LoadFile;

	if (_LevelName == "Niveau1" || _LevelName == "Niveau2")
		LoadFile.open("Ressources/Sauvegardes/0" + _LevelName + ".txt", std::ios_base::in);
	else
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

Map::~Map()
{
}

void Map::Update(float _Elapsed, Caméra * _Cam)
{
	for (int i = 1; i < 4; i++)
	{
		Plan[i].move((320 + (190 * (i - 1))) * _Elapsed, 0);

		Plan2[i].move((320 + (190 * (i - 1))) * _Elapsed, 0);
	}

	//std::cout << Plan1[0].getPosition().x / Plan1[0].getGlobalBounds().width << std::endl;

	for (int i = 0; i < 2; i++)
	{
		if (Plan1[i].getPosition().x + Plan1[i].getGlobalBounds().width <= _Cam->GetCameraCenter().x - _Cam->GetSizeCamera().x / 2)
		{
			Plan1[i].setTexture(*ResourceManager::Instance()->GetTexture("Plan1_" + std::to_string(Plan1[0].getPosition().x / Plan1[0].getGlobalBounds().width)));
			Plan1[i].setPosition(Plan1[i].getPosition().x + Plan1[i].getGlobalBounds().width * 2, 0);
		}
	}

	for (int i = 0; i < 4; i++)
	{
		if (Plan[i].getPosition().x + Plan[i].getGlobalBounds().width < _Cam->GetCamera()->getCenter().x - _Cam->GetCamera()->getSize().x / 2)
		{
			Plan[i].setPosition(Plan2[i].getPosition().x + Plan2[i].getGlobalBounds().width, 0);
		}

		if (Plan2[i].getPosition().x + Plan2[i].getGlobalBounds().width < _Cam->GetCamera()->getCenter().x - _Cam->GetCamera()->getSize().x / 2)
		{
			Plan2[i].setPosition(Plan[i].getPosition().x + Plan[i].getGlobalBounds().width, 0);
		}
	}
}

void Map::Display()
{
	/*for (int i = 3; i > -1; i--)
	{
		m_actualWindow->draw(Plan[i]);
		m_actualWindow->draw(Plan2[i]);
	}*/

	/*for (int i = 0; i < 2; i++)
	{
		m_actualWindow->draw(Plan1[i]);
	}*/

	for (int y = 0; y < Size_Y; y++)
	{
		for (int x = 0; x < Size_X; x++)
		{
			CasePos.x = (float)x * 64;
			CasePos.y = (float)y * 64;

			switch (Tableau[y][x])
			{
			case 0:
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
				Collectible.setPosition(CasePos);
				m_actualWindow->draw(Collectible);
				break;
			}
		}
	}
}

int Map::GetTile(int _X, int _Y)
{
	return Tableau[_Y / 64][_X / 64];
}

void Map::SetTile(int _X, int _Y, int _Tile)
{
	Tableau[_Y / 64][_X / 64] = _Tile;
}

sf::Vector2f Map::GetPos()
{
	return sf::Vector2f();
}

sf::Vector2f Map::GetCheckPoint(sf::Vector2f _Pos)
{
	for (int y = 0; y < Size_Y; y++)
	{
		for (int x = 0; x < Size_X; x++)
		{
			if (Tableau[y][x] == 8 && x > (_Pos.x / 64))
			{
				XList.push_back(x);
			}
		}
	}

	for (int i = 0; i < XList.size(); i++)
	{
		for (int y = 0; y < XList.size(); y++)
		{
			if (XList[i] < XList[y])
				XList.erase(XList.begin() + y);
			else
				XList.erase(XList.begin() + i);
		}
	}

	for (int y = 0; y < Size_Y; y++)
	{
		for (int x = 0; x < XList[0] + 1; x++)
		{
			if (Tableau[y][x] == 8 && x == XList[0] && x > (_Pos.x / 64))
			{
				CasePos.x = (float)x * 64;
				CasePos.y = (float)y * 64;
				return CasePos;
			}
		}
	}
}

sf::Vector2f Map::GetNextTile(int _Type, sf::Vector2f _Pos)
{
	for (int y = (_Pos.y) / 64; y < Size_Y; y++)
	{
		for (int x = (_Pos.x - 100) / 64; x < (_Pos.x + 200) / 64; x++)
		{
			if (Tableau[y][x] == _Type)
			{
				CasePos.x = (float)x * 64;
				CasePos.y = (float)y * 64;

				return CasePos;
			}
		}
	}
}
