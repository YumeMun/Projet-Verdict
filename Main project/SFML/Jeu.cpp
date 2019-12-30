#include "Jeu.h"
#include "GameManager.h"
#include "ResourceManager.h"

Jeu::Jeu()
{
	std::cout << "Jeu constructor" << std::endl;

	m_actualWindow = GameManager::Instance()->GetWindow();

	map = new Map();
	caméra = new Caméra();
	hud = new HUD();

	//collects = new Collects();
	///missile = new Missile();

	Player1 = new Player(1, sf::Vector2f(400, 800));
	Player2 = new Player(2, sf::Vector2f(400, 800));

	transition = new Transition({ 0, 0 }, { 0, 1080 / 2 });
	timerStart = new TimerStart();

	for (int i = 0; i < 6; i++)
	{
		MenuIGText[i].setFont(*ResourceManager::Instance()->GetFont("Font"));
		MenuIGText[i].setCharacterSize(35);
		MenuIGText[i].setFillColor(sf::Color::White);

		MenuIGText[0].setString("Reprendre");
		MenuIGText[1].setString("Recommencer");
		MenuIGText[2].setString("Quitter");

		MenuIGText[4].setString("Oui");
		MenuIGText[5].setString("Non");
	}
}

Jeu::~Jeu()
{
}

void Jeu::Update()
{
	CurrentTime = (float)clock() / CLOCKS_PER_SEC;
	ElapsedTime = CurrentTime - LastFrameTime;

	if (MenuIG_Activated == false)
	{
		if (Clock.getElapsedTime().asSeconds() > 1)
		{
			if (sf::Joystick::isButtonPressed(0, 7))
			{
				ID = 0;
				MenuIG(0);
				MenuIG_Activated = true;
			}
			else if (sf::Joystick::isButtonPressed(1, 7))
			{
				ID = 1;
				MenuIG(1);
				MenuIG_Activated = true;
			}
		}

		if (transition->GetIsTransitionBackDone())
		{
			if (timerStart->GetIsTimerEnd())
			{
				Player1->Update(ElapsedTime, map, caméra, Player2->GetPos());
				Player2->Update(ElapsedTime, map, caméra, Player1->GetPos());

				Shockwave* newShock = new Shockwave(1, Player1->GetPos());

				Collectibles.push_back(newShock);

				/*if (Player1->newMissile != NULL)
					Player1->newMissile->Update(ElapsedTime, map);

				if (Player2->newMissile != NULL)
					Player2->newMissile->Update(ElapsedTime, map);*/

				if (Player1->GetPos().x > Player2->GetPos().x)
				{
					if (Player1->PlayerFirstTimer.getElapsedTime().asSeconds() > 1 && Player1->IsAlive() == true)
					{
						Player1->Score++;
						Player1->PlayerFirstTimer.restart();
					}
				}
				else if (Player2->GetPos().x > Player1->GetPos().x)
				{
					if (Player2->PlayerFirstTimer.getElapsedTime().asSeconds() > 1 && Player2->IsAlive() == true)
					{
						Player2->Score++;
						Player2->PlayerFirstTimer.restart();
					}
				}

				map->Update(ElapsedTime, caméra);
			}
			else
				timerStart->UpdateRect();
		}
		else
			transition->UpdateBack();

		for (int i = 0; i < Collectibles.size(); i++)
		{
			Collectibles[i]->Update(Player1->GetSprite(), Player2->GetSprite(), ElapsedTime);

			if (Collectibles[i]->IsAlive() == false)
				Collectibles.erase(Collectibles.begin() + i);
		}

		caméra->Update(ElapsedTime, timerStart);

		//collects->Update(missile);

		hud->Update(caméra->GetCameraCenter(), caméra->GetSizeCamera(), Player1->GetPos(), Player2->GetPos());

		if (Player1->Hasfinished == true && Player2->Hasfinished == true)
		{
			transition->Update();

			if (transition->GetIsTransitionDone())
			{
				transition->ResetTransition();
				GameManager::Instance()->m_ActualScene = new Level_Finished(Player1->Score, Player2->Score);
			}	
		}
	}

	LastFrameTime = CurrentTime;
}

void Jeu::Display()
{
	m_actualWindow->setView(*caméra->GetCamera());
	map->Display();

	//collects->Display();
	Player2->Display(m_actualWindow);
	Player1->Display(m_actualWindow);

	if (Player1->CollectibleUsed() == true)
		std::cout << Player1->GetCollectID() << std::endl;

	for (int i = 0; i < Collectibles.size(); i++)
	{
		Collectibles[i]->Display(m_actualWindow);
	}

	/*if (Player1->newMissile != NULL)
		m_actualWindow->draw(Player1->newMissile->GetMissile());

	if (Player2->newMissile != NULL)
		m_actualWindow->draw(Player2->newMissile->GetMissile());*/

	m_actualWindow->setView(m_actualWindow->getDefaultView());
	hud->Display(Player1->HasCollectible, Player2->HasCollectible);

	if (!timerStart->GetIsTimerEnd())
	{
		timerStart->DrawRect();
	}

	if (!transition->GetIsTransitionBackDone())
	{
		transition->DrawTransition();
	}

	if (MenuIG_Activated == true)
	{
		MenuIG(ID);
		m_actualWindow->draw(spMenuIG);

		if (StateMenuIG == 0)
		{
			m_actualWindow->draw(MenuIGText[0]);
			m_actualWindow->draw(MenuIGText[1]);
			m_actualWindow->draw(MenuIGText[2]);
		}
		else if (StateMenuIG != 0)
		{
			m_actualWindow->draw(MenuIGText[3]);
			m_actualWindow->draw(MenuIGText[4]);
			m_actualWindow->draw(MenuIGText[5]);
		}
	}

	if (Player1->Hasfinished == true && Player2->Hasfinished == true)
	{
		transition->DrawTransition();
	}
}

void Jeu::EventManager(sf::Event p_pollingEvent)
{
}

void Jeu::MenuIG(int ID)
{
	if (ID == 0)
	{
		spMenuIG.setTexture(*ResourceManager::Instance()->GetTexture("MenuIG J1"));
		spMenuIG.setOrigin(spMenuIG.getGlobalBounds().width / 2, spMenuIG.getGlobalBounds().height / 2);
		spMenuIG.setPosition(960, 540);
	}
	else if (ID == 1)
	{
		spMenuIG.setTexture(*ResourceManager::Instance()->GetTexture("MenuIG J1"));
		spMenuIG.setOrigin(spMenuIG.getGlobalBounds().width / 2, spMenuIG.getGlobalBounds().height / 2);
		spMenuIG.setPosition(960, 540);
	}

	if (StateMenuIG == 0)
	{
		MenuIGText[0].setPosition(spMenuIG.getPosition().x - 350, spMenuIG.getPosition().y - 50);
		MenuIGText[1].setPosition(spMenuIG.getPosition().x - 130, spMenuIG.getPosition().y - 20);
		MenuIGText[2].setPosition(spMenuIG.getPosition().x + 140, spMenuIG.getPosition().y + 20);

		if (SelectionMenuIG == 1)
		{
			MenuIGText[0].setFillColor(sf::Color{ 255, 156, 0, 255 });
			MenuIGText[1].setFillColor(sf::Color{ 255, 255, 255, 255 });
			MenuIGText[2].setFillColor(sf::Color{ 255, 255, 255, 255 });
		}
		else if (SelectionMenuIG == 2)
		{
			MenuIGText[0].setFillColor(sf::Color{ 255, 255, 255, 255 });
			MenuIGText[1].setFillColor(sf::Color{ 255, 156, 0, 255 });
			MenuIGText[2].setFillColor(sf::Color{ 255, 255, 255, 255 });
		}
		else if (SelectionMenuIG == 3)
		{
			MenuIGText[0].setFillColor(sf::Color{ 255, 255, 255, 255 });
			MenuIGText[1].setFillColor(sf::Color{ 255, 255, 255, 255 });
			MenuIGText[2].setFillColor(sf::Color{ 255, 156, 0, 255 });
		}

		if (Clock.getElapsedTime().asMilliseconds() > 300)
		{
			if (sf::Joystick::getAxisPosition(ID, sf::Joystick::Axis::X) >= 50)
			{
				if (SelectionMenuIG < 3)
					SelectionMenuIG++;

				Clock.restart();
			}
			else if (sf::Joystick::getAxisPosition(ID, sf::Joystick::Axis::X) <= -50)
			{
				if (SelectionMenuIG > 1)
					SelectionMenuIG--;

				Clock.restart();
			}

			if (sf::Joystick::isButtonPressed(ID, 0))
			{
				if (SelectionMenuIG == 1)
				{
					MenuIG_Activated = false;
					Clock.restart();
				}
				else if (SelectionMenuIG == 2)
				{
					StateMenuIG = 1;
					SelectionMenuIG = 1;
					Clock.restart();
				}
				else if (SelectionMenuIG == 3)
				{
					StateMenuIG = 2;
					SelectionMenuIG = 1;
					Clock.restart();
				}
			}
		}
	}
	else if (StateMenuIG == 1)
	{
		MenuIGText[3].setString("Voulez-vous vraiment\nrecommencer la partie ?");
		MenuIGText[3].setPosition(spMenuIG.getPosition().x - 220, spMenuIG.getPosition().y - 50);
		MenuIGText[4].setPosition(spMenuIG.getPosition().x - 150, spMenuIG.getPosition().y + 30);
		MenuIGText[5].setPosition(spMenuIG.getPosition().x + 110, spMenuIG.getPosition().y + 30);

		if (SelectionMenuIG == 1)
		{
			MenuIGText[4].setFillColor(sf::Color{ 255, 156, 0, 255 });
			MenuIGText[5].setFillColor(sf::Color{ 255, 255, 255, 255 });
		}
		else if (SelectionMenuIG == 2)
		{
			MenuIGText[4].setFillColor(sf::Color{ 255, 255, 255, 255 });
			MenuIGText[5].setFillColor(sf::Color{ 255, 156, 0, 255 });
		}

		if (Clock.getElapsedTime().asMilliseconds() > 300)
		{
			if (sf::Joystick::getAxisPosition(ID, sf::Joystick::Axis::X) >= 50)
			{
				if (SelectionMenuIG < 2)
					SelectionMenuIG++;

				Clock.restart();
			}
			else if (sf::Joystick::getAxisPosition(ID, sf::Joystick::Axis::X) <= -50)
			{
				if (SelectionMenuIG > 1)
					SelectionMenuIG--;

				Clock.restart();
			}

			if (sf::Joystick::isButtonPressed(ID, 0))
			{
				if (SelectionMenuIG == 1)
				{
					GameManager::Instance()->LoadScene(e_Enum::e_Scene::JEU);
					Clock.restart();
				}
				else if (SelectionMenuIG == 2)
				{
					StateMenuIG = 0;
					SelectionMenuIG = 1;
					Clock.restart();
				}
			}
		}
	}
	else if (StateMenuIG == 2)
	{
		MenuIGText[3].setString("	Voulez-vous vraiment\nquitter la partie en cours ?");
		MenuIGText[3].setPosition(spMenuIG.getPosition().x - 250, spMenuIG.getPosition().y - 50);
		MenuIGText[4].setPosition(spMenuIG.getPosition().x - 150, spMenuIG.getPosition().y + 30);
		MenuIGText[5].setPosition(spMenuIG.getPosition().x + 110, spMenuIG.getPosition().y + 30);

		if (SelectionMenuIG == 1)
		{
			MenuIGText[4].setFillColor(sf::Color{ 255, 156, 0, 255 });
			MenuIGText[5].setFillColor(sf::Color{ 255, 255, 255, 255 });
		}
		else if (SelectionMenuIG == 2)
		{
			MenuIGText[4].setFillColor(sf::Color{ 255, 255, 255, 255 });
			MenuIGText[5].setFillColor(sf::Color{ 255, 156, 0, 255 });
		}

		if (Clock.getElapsedTime().asMilliseconds() > 300)
		{
			if (sf::Joystick::getAxisPosition(ID, sf::Joystick::Axis::X) >= 50)
			{
				if (SelectionMenuIG < 2)
					SelectionMenuIG++;

				Clock.restart();
			}
			else if (sf::Joystick::getAxisPosition(ID, sf::Joystick::Axis::X) <= -50)
			{
				if (SelectionMenuIG > 1)
					SelectionMenuIG--;

				Clock.restart();
			}

			if (sf::Joystick::isButtonPressed(ID, 0))
			{
				if (SelectionMenuIG == 1)
				{
					GameManager::Instance()->LoadScene(e_Enum::e_Scene::MENU);
					Clock.restart();
				}
				else if (SelectionMenuIG == 2)
				{
					StateMenuIG = 0;
					SelectionMenuIG = 1;
					Clock.restart();
				}
			}
		}
	}
}