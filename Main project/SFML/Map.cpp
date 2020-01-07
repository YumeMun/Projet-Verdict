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

	CheckPos = sf::Vector2f(0, 0);

	for (int i = 0; i < 5; i++)
	{
		if (i >= 1)
		{
			Plan[i].setTexture(*ResourceManager::Instance()->GetTexture("Plan" + std::to_string(i)));
			Plan2[i].setTexture(*ResourceManager::Instance()->GetTexture("Plan" + std::to_string(i)));
		}

		Plan2[i].setPosition(Plan[i].getGlobalBounds().width, 0);

		//Plan[i].setScale(2, 2);
		//Plan2[i].setScale(2, 2);
	}

	for (int i = 0; i < 8; i++)
	{
		spTile[i].setTexture(*ResourceManager::Instance()->GetTexture("Case" + std::to_string(i + 1)));
	}

	//for (int i = 0; i < 2; i++)
	//{
	//	Plan1[i].setTexture(*ResourceManager::Instance()->GetTexture("Plan1_" + std::to_string(i)));
	//	//Plan1[i].setScale(2, 2);
	//	Plan1[i].setPosition(Plan1[i].getGlobalBounds().width * i, 0);
	//}

	for (int i = 0; i < 30; i++)
	{
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

			spTile[27].setTextureRect(sf::IntRect{ 0 * 64, 21 * 64, 318, 318 });
			spTile[28].setTextureRect(sf::IntRect{ 0 * 64, (21 * 64) + (1 * 318), 318, 318 });
			spTile[29].setTextureRect(sf::IntRect{ 0 * 64, (21 * 64) + (2 * 318), 318, 318 });
		}
	}

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

	for (int y = 0; y < Size_Y; y++)
	{
		for (int x = 0; x < Size_X; x++)
		{
			if (Tableau[y][x] == 26)
				Tableau[y][x] = 0;
		}
	}

	LoadFile.close();

	timerLazer.restart();
}

Map::~Map()
{
}

void Map::Update(float _Elapsed, Caméra* _Cam)
{
	for (int y = 0; y < Size_Y; y++)
	{
		for (int x = 0; x < Size_X; x++)
		{
			if (Tableau[y][x] >= 1 && Tableau[y][x] <= 6 && Tableau[y - 1][x] == 0)
			{
				if (x >= (CheckPos.x + 1920) / 64 && x <= (CheckPos.x + 4800) / 64)
				{
					Tableau[y - 1][x] = 26;
					CheckPos = sf::Vector2f(x * 64, (y - 1) * 64);
				}
			}
		}
	}

	if (timerLazer.getElapsedTime().asSeconds() > 2)
	{
		if (isLazerOn == 3)
		{
			isLazerOn = 0;
		}
		else
			isLazerOn = 1;

		timerLazer.restart();
	}

	/*for (int i = 0; i < 2; i++)
	{
		if (Plan1[i].getPosition().x + Plan1[i].getGlobalBounds().width <= _Cam->GetCameraCenter().x - _Cam->GetSizeCamera().x / 2)
		{
			Plan1[i].setTexture(*ResourceManager::Instance()->GetTexture("Plan1_" + std::to_string(Plan1[0].getPosition().x / Plan1[0].getGlobalBounds().width)));
			Plan1[i].setPosition(Plan1[i].getPosition().x + Plan1[i].getGlobalBounds().width * 2, 0);
		}
	}*/

	Plan[0].move(_Cam->GetCamSpeed() * -0.05 * _Elapsed, 0);
	Plan2[0].move(_Cam->GetCamSpeed() * -0.05 * _Elapsed, 0);

	Plan[1].move(_Cam->GetCamSpeed() * 0.1 * _Elapsed, 0);
	Plan2[1].move(_Cam->GetCamSpeed() * 0.1 * _Elapsed, 0);

	Plan[2].move(_Cam->GetCamSpeed() * 0.3 * _Elapsed, 0);
	Plan2[2].move(_Cam->GetCamSpeed() * 0.3 * _Elapsed, 0);

	Plan[3].move(_Cam->GetCamSpeed() * 0.55 * _Elapsed, 0);
	Plan2[3].move(_Cam->GetCamSpeed() * 0.55 * _Elapsed, 0);

	Plan[4].move(_Cam->GetCamSpeed() * _Elapsed, 0);
	Plan2[4].move(_Cam->GetCamSpeed() * _Elapsed, 0);

	for (int i = 0; i < 5; i++)
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

void Map::Display(Caméra _Cam)
{
	m_actualWindow->draw(Plan[5]);

	for (int i = 4; i > 0; i--)
	{
		m_actualWindow->draw(Plan[i]);
		m_actualWindow->draw(Plan2[i]);
	}

	/*for (int i = 0; i < 2; i++)
	{
		m_actualWindow->draw(Plan1[i]);
	}*/

	AnimTiles();

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
				spTile[19].setTextureRect(sf::IntRect{ FrameIndexElect * (4 * 64), 13 * 64, 4 * 64, 64 });
				spTile[19].setPosition(CasePos);
				m_actualWindow->draw(spTile[19]);
				break;
			case 21:
				spTile[20].setTextureRect(sf::IntRect{ FrameIndexElect * 64, 14 * 64, 64, 4 * 64 });
				spTile[20].setPosition(CasePos);
				m_actualWindow->draw(spTile[20]);
				break;
			case 22:
				spTile[21].setTextureRect(sf::IntRect{ FrameIndexLaser * 64, 18 * 64, 64, 3 * 64 });
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
			case 35:
				if (AnimCaisseClock.getElapsedTime().asMilliseconds() > 50)
				{
					if (FrameIndexCaisse < 8)
					{
						FrameIndexCaisse++;
					}
					else
					{
						FrameIndexCaisse = 0;
						Tableau[y][x] = 0;
					}

					AnimCaisseClock.restart();
				}

				spTile[27].setTextureRect(sf::IntRect{ FrameIndexCaisse * 318, 21 * 64, 318, 318 });
				spTile[27].setOrigin(spTile[27].getGlobalBounds().width / 2, spTile[27].getGlobalBounds().height / 2);
				spTile[27].setPosition(CasePos);
				m_actualWindow->draw(spTile[27]);
				break;
			case 36:
				if (AnimCaisseClock.getElapsedTime().asMilliseconds() > 50)
				{
					if (FrameIndexCaisse < 8)
					{
						FrameIndexCaisse++;
					}
					else
					{
						FrameIndexCaisse = 0;
						Tableau[y][x] = 0;
					}

					AnimCaisseClock.restart();
				}
				spTile[28].setTextureRect(sf::IntRect{ FrameIndexCaisse * 318, (21 * 64) + (1 * 318), 318, 318 });
				spTile[28].setOrigin(spTile[28].getGlobalBounds().width / 2, spTile[28].getGlobalBounds().height / 2);
				spTile[28].setPosition(CasePos);
				m_actualWindow->draw(spTile[28]);
				break;
			case 37:
				if (AnimCaisseClock.getElapsedTime().asMilliseconds() > 50)
				{
					if (FrameIndexCaisse < 8)
					{
						FrameIndexCaisse++;
					}
					else
					{
						FrameIndexCaisse = 0;
						Tableau[y][x] = 0;
					}

					AnimCaisseClock.restart();
				}
				spTile[29].setTextureRect(sf::IntRect{ FrameIndexCaisse * 318, (21 * 64) + (2 * 318), 318, 318 });
				spTile[29].setOrigin(spTile[29].getGlobalBounds().width / 2, spTile[29].getGlobalBounds().height / 2);
				spTile[29].setPosition(CasePos);
				m_actualWindow->draw(spTile[29]);
				break;
			}
		}
	}
}

void Map::FirstPlanDisplay()
{
	m_actualWindow->draw(Plan[0]);
	m_actualWindow->draw(Plan2[0]);
}

int Map::GetTile(int _X, int _Y)
{
	return Tableau[_Y / 64][_X / 64];
}

void Map::SetTile(int _X, int _Y, int _Tile)
{
	Tableau[_Y / 64][_X / 64] = _Tile;
}

int Map::GetSizeX()
{
	return Size_X;
}

int Map::GetSizeY()
{
	return Size_Y;
}

sf::Vector2f Map::GetStartPos()
{
	for (int y = 0; y < Size_Y; y++)
	{
		for (int x = 0; x < Size_X; x++)
		{
			if (Tableau[y][x] == 24)
			{
				XListStart.push_back(x);
			}
		}
	}

	for (int y = 0; y < Size_Y; y++)
	{
		for (int x = 0; x < XListStart[0] + 1; x++)
		{
			if (Tableau[y][x] == 24 && x == XListStart[0])
			{
				CasePos.x = (float)x * 64;
				CasePos.y = (float)y * 64;
				return CasePos;
			}
		}
	}
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
			if (Tableau[y][x] == 26 && x > (_Pos.x / 64) && x <= ((_Pos.x + 1920) / 64))
			{
				CasePos.x = (float)x * 64;
				CasePos.y = (float)y * 64;
				return CasePos;
			}
		}
	}

	/*for (int i = 0; i < XListCheckpoint.size() - 1; i++)
	{
		for (int y = 0; y < XListCheckpoint.size() - 1; y++)
		{
			if (XListCheckpoint.size() >= 2)
			{
				if (XListCheckpoint[i] <= XListCheckpoint[y])
					XListCheckpoint.erase(XListCheckpoint.begin() + y);
				else
					XListCheckpoint.erase(XListCheckpoint.begin() + i);
			}
		}
	}*/

	/*for (int i = 0; i < XListCheckpoint.size(); i++)
	{
		std::cout << XListCheckpoint[i] << std::endl;
	}*/

	/*for (int y = 0; y < Size_Y; y++)
	{
		for (int x = 0; x < XListCheckpoint[0] + 1; x++)
		{
			if (Tableau[y][x] == 26 && x == XListCheckpoint[0] && x > (_Pos.x / 64))
			{
				CasePos.x = (float)x * 64;
				CasePos.y = (float)y * 64;
				return CasePos;
			}
		}
	}*/
}

sf::Vector2f Map::GetEndFlag()
{
	for (int y = 0; y < Size_Y; y++)
	{
		for (int x = 0; x < Size_X; x++)
		{
			if (Tableau[y][x - 2] == 25)
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

int Map::GetIsLazerOn()
{
	return isLazerOn;
}

void Map::AnimTiles()
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

	if (AnimLaserClock.getElapsedTime().asMilliseconds() > 50)
	{
		if (isLazerOn == 0)
		{
			if (FrameIndexLaser < 14)
			{
				FrameIndexLaser++;
			}
			else
				FrameIndexLaser = 14;
		}
		else if (isLazerOn == 1)
		{
			if (FrameIndexLaser < 16)
			{
				FrameIndexLaser++;
			}
			else
			{
				FrameIndexLaser = 0;
				isLazerOn = 3;
			}
		}

		AnimLaserClock.restart();
	}
}
