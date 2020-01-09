#include "Jeu.h"
#include "GameManager.h"
#include "ResourceManager.h"

Jeu::Jeu()
{
}

Jeu::Jeu(std::string _LevelName, int skinSelectedJ1, int skinSelectedJ2)
{
	m_actualWindow = GameManager::Instance()->GetWindow();

	GameManager::Instance()->music.stop();

	LevelName = _LevelName;

	if (LevelName == "Niveau1")
	{
		if (!musicNiveau.openFromFile("Ressources/Music/I_got_Rythm.ogg"))
			std::cout << "Erreur music" << std::endl; // erreur
		musicNiveau.setVolume(GameManager::Instance()->VolumeMusique);
		musicNiveau.play();
		musicNiveau.setLoop(true);
	}

	if (LevelName == "Niveau2")
	{
		if (!musicNiveau.openFromFile("Ressources/Music/The_Old_Man.ogg"))
			std::cout << "Erreur music" << std::endl; // erreur
		musicNiveau.setVolume(GameManager::Instance()->VolumeMusique);
		musicNiveau.play();
		musicNiveau.setLoop(true);
	}

	skinJ1 = skinSelectedJ1;
	skinJ2 = skinSelectedJ2;

	map = new Map(_LevelName);
	//cam
	//hud

	//collects = new Collects();
	///missile = new Missile();

	voiture.setBuffer(*ResourceManager::Instance()->GetSoundBuffer("Voiture"));
	voiture.setVolume(GameManager::Instance()->VolumeFX);
	voiture.play();
	voiture.setLoop(true);

	Player1 = new Player(1, sf::Vector2f(600, 800), map, skinJ1);
	Player2 = new Player(2, sf::Vector2f(200, 800), map, skinJ2);

	caméra = new Caméra(Player1, Player2);
	hud = new HUD();

	transition = new Transition({ 0, 0 }, { 0, 1080 / 2 });
	timerStart = new TimerStart();
	scoreScreen = new Level_Finished();

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

	spFirstOrSecond[0].setTexture(*ResourceManager::Instance()->GetTexture("First"));
	spFirstOrSecond[1].setTexture(*ResourceManager::Instance()->GetTexture("Second"));
	spFirstOrSecond[0].setOrigin(spFirstOrSecond[0].getGlobalBounds().width / 2, spFirstOrSecond[0].getGlobalBounds().height / 2);
	spFirstOrSecond[1].setOrigin(spFirstOrSecond[1].getGlobalBounds().width / 2, spFirstOrSecond[1].getGlobalBounds().height / 2);
	spFirstOrSecond[0].setPosition(570, 100);
	spFirstOrSecond[1].setPosition(1920 - 570, 100);
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

				if (Player1->Boost == true && Player1->Boosted == false)
				{
					BoostEffect* newFx = new BoostEffect(1, Player1->GetPos());
					FXs.push_back(newFx);
					Player1->Boosted = true;
				}
				if (Player2->Boost == true && Player2->Boosted == false)
				{
					BoostEffect* newFx = new BoostEffect(2, Player2->GetPos());
					FXs.push_back(newFx);
					Player2->Boosted = true;
				}

				if (Player1->GetPos().x > Player2->GetPos().x)
				{
					if (Player1->PlayerFirstTimer.getElapsedTime().asMilliseconds() > 500 && Player1->IsAlive() == true)
					{
						Player1->Score += 8; /// FACTOR_DIVIDE;
						Player1->PlayerFirstTimer.restart();
					}

					spFirstOrSecond[0].setPosition(570, 100);
					spFirstOrSecond[1].setPosition(1920 - 570, 100);
				}
				else if (Player2->GetPos().x > Player1->GetPos().x)
				{
					if (Player2->PlayerFirstTimer.getElapsedTime().asSeconds() > 1 && Player2->IsAlive() == true)
					{
						Player2->Score += 8; /// FACTOR_DIVIDE;
						Player2->PlayerFirstTimer.restart();
					}
					spFirstOrSecond[0].setPosition(1920 - 570, 100);
					spFirstOrSecond[1].setPosition(570, 100);
				}

				map->Update(ElapsedTime, caméra);
			}
			else
			{
				timerStart->UpdateRect();
				if (caméra->GetSizeCamera().x < 1920 * 1.8)
				{
					caméra->UpdateZoom(ElapsedTime, map, Player1, Player2);
				}

				if (isPlayerAnimStart)
				{
					Player1->SetAnimClockRestart();
					Player2->SetAnimClockRestart();
					isPlayerAnimStart = false;
				}
				else
				{
					if (!Player1->isAnimStartEnd || !Player2->isAnimStartEnd)
					{
						Player1->SetAnimWheelStart();
						Player2->SetAnimWheelStart();
					}
				}
			}
		}
		else
			transition->UpdateBack();

		CollectiblesManager();

		if (Player1->Hasfinished == false && Player2->Hasfinished == false)
			caméra->Update(ElapsedTime, timerStart, Player1, Player2, map);
		else if (Player1->Hasfinished == true || Player2->Hasfinished == false)
		{
			caméra->Update(ElapsedTime, timerStart, Player1, Player2, map);
			Player1->scoreIsArrivedFirst = 200; /// FACTOR_DIVIDE;
			Player2->scoreIsArrivedFirst = 0;
		}
		else if (Player1->Hasfinished == false || Player2->Hasfinished == true)
		{
			caméra->Update(ElapsedTime, timerStart, Player1, Player2, map);
			Player2->scoreIsArrivedFirst = 200; /// FACTOR_DIVIDE;
			Player1->scoreIsArrivedFirst = 0;
		}
		/*else if (Player1->Hasfinished == true || Player2->Hasfinished == true)
			caméra->Update(ElapsedTime, timerStart, Player1, Player2, map);*/



		hud->Update(caméra->GetCameraCenter(), caméra->GetSizeCamera(), Player1->GetPos(), Player2->GetPos());

		if (Player1->Hasfinished == true && Player2->Hasfinished == true)
		{
			transition->Update();
			if (transition->GetIsTransitionDone())
			{
				voiture.stop();
				musicNiveau.stop();
				transition->ResetTransition();
				GameManager::Instance()->m_ActualScene = new Level_Finished(Player1->Score, Player2->Score, Player1, Player2, skinJ1, skinJ2, LevelName);
			}
		}
	}

	LastFrameTime = CurrentTime;
}

void Jeu::Display()
{
	m_actualWindow->clear(sf::Color::White);
	m_actualWindow->setView(*caméra->GetCamera());
	map->Display();

	Player2->Display(m_actualWindow);
	Player1->Display(m_actualWindow);

	for (int i = 0; i < Collectibles.size(); i++)
	{
		Collectibles[i]->Display(m_actualWindow);
	}

	for (int i = 0; i < FXs.size(); i++)
	{
		FXs[i]->Display(m_actualWindow);
	}

	map->FirstPlanDisplay();

	m_actualWindow->setView(m_actualWindow->getDefaultView());
	hud->Display(Player1, Player2);

	for (int i = 0; i < 2; i++)
	{
		m_actualWindow->draw(spFirstOrSecond[i]);
	}

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

void Jeu::CollectiblesManager()
{
	if (Player1->CollectibleUsed() == true)
	{
		if (Player1->GetCollectID() == e_Enum::e_Collects::ROCKET)
		{
			Rocket* newCollect = new Rocket(1, Player1->GetAimDir(), Player1->GetPos());
			Collectibles.push_back(newCollect);
			Player1->SetCollectID(0);
		}
		else if (Player1->GetCollectID() == e_Enum::e_Collects::SHOCKWAVE)
		{
			m_Shockwave.setBuffer(*ResourceManager::Instance()->GetSoundBuffer("Onde de Choc"));
			m_Shockwave.setVolume(GameManager::Instance()->VolumeFX);
			m_Shockwave.play();

			Shockwave* newCollect = new Shockwave(1, Player1->GetPos());
			Collectibles.push_back(newCollect);
			Player1->SetCollectID(0);
		}
		else if (Player1->GetCollectID() == e_Enum::e_Collects::OILFLAKE)
		{
			m_oil.setBuffer(*ResourceManager::Instance()->GetSoundBuffer("Mousse"));
			m_oil.setVolume(GameManager::Instance()->VolumeFX);
			m_oil.play();

			Oilflake* newCollect = new Oilflake(1, Player1->GetPos());
			Collectibles.push_back(newCollect);
			Player1->SetCollectID(0);
		}
		else if (Player1->GetCollectID() == e_Enum::e_Collects::LEVITATION)
		{
			m_levitation.setBuffer(*ResourceManager::Instance()->GetSoundBuffer("Invincibilite"));
			m_levitation.setVolume(GameManager::Instance()->VolumeFX);
			m_levitation.play();

			Invicibility* newCollect = new Invicibility(1, Player1->GetPos());
			Collectibles.push_back(newCollect);
			Player1->InvincibleTime.restart();
			Player1->Invincible = true;
			Player1->SetCollectID(0);
		}
		else if (Player1->GetCollectID() == e_Enum::e_Collects::SWAP)
		{

			if (Player2->GetCollectID() != 0)
			{
				Alteration.setBuffer(*ResourceManager::Instance()->GetSoundBuffer("Alteration"));
				Alteration.setVolume(GameManager::Instance()->VolumeFX*0.5);
				Alteration.play();

				m_magnet.setBuffer(*ResourceManager::Instance()->GetSoundBuffer("Magnetisme"));
				m_magnet.setVolume(GameManager::Instance()->VolumeFX);
				m_magnet.play();

				Player1->HasCollectible = false;
				Player1->SetCollectID(Player2->GetCollectID());
				Player2->SetCollectID(0);
			}
			else
				Player1->SetCollectID(0);
		}
		else if (Player1->GetCollectID() == e_Enum::e_Collects::BUMPER)
		{
			Bumper* newCollect = new Bumper(1, Player1->GetAimDir(), Player1->GetPos());
			Collectibles.push_back(newCollect);
			Player1->SetCollectID(0);
		}
	}

	if (Player2->CollectibleUsed() == true)
	{
		if (Player2->GetCollectID() == e_Enum::e_Collects::ROCKET)
		{
			Rocket* newCollect = new Rocket(2, Player2->GetAimDir(), Player2->GetPos());
			Collectibles.push_back(newCollect);
			Player2->SetCollectID(0);
		}
		else if (Player2->GetCollectID() == e_Enum::e_Collects::SHOCKWAVE)
		{
			m_Shockwave.setBuffer(*ResourceManager::Instance()->GetSoundBuffer("Onde de Choc"));
			m_Shockwave.setVolume(GameManager::Instance()->VolumeFX);
			m_Shockwave.play();

			Shockwave* newCollect = new Shockwave(2, Player2->GetPos());
			Collectibles.push_back(newCollect);
			Player2->SetCollectID(0);
		}
		else if (Player2->GetCollectID() == e_Enum::e_Collects::OILFLAKE)
		{
			Oilflake* newCollect = new Oilflake(2, Player2->GetPos());
			Collectibles.push_back(newCollect);
			Player2->SetCollectID(0);
		}
		else if (Player2->GetCollectID() == e_Enum::e_Collects::LEVITATION)
		{
			m_levitation.setBuffer(*ResourceManager::Instance()->GetSoundBuffer("Invincibilite"));
			m_levitation.setVolume(GameManager::Instance()->VolumeFX);
			m_levitation.play();

			Invicibility* newCollect = new Invicibility(1, Player2->GetPos());
			Collectibles.push_back(newCollect);
			Player2->InvincibleTime.restart();
			Player2->Invincible = true;
			Player2->SetCollectID(0);
		}
		else if (Player2->GetCollectID() == e_Enum::e_Collects::SWAP)
		{

			if (Player1->GetCollectID() != 0)
			{
				Alteration.setBuffer(*ResourceManager::Instance()->GetSoundBuffer("Alteration"));
				Alteration.setVolume(GameManager::Instance()->VolumeFX*0.5);
				Alteration.play();

				m_magnet.setBuffer(*ResourceManager::Instance()->GetSoundBuffer("Magnetisme"));
				m_magnet.setVolume(GameManager::Instance()->VolumeFX);
				m_magnet.play();

					Player2->HasCollectible = false;
					Player2->SetCollectID(Player1->GetCollectID());
				Player1->SetCollectID(0);
			}
			else
				Player2->SetCollectID(0);
		}
		else if (Player2->GetCollectID() == e_Enum::e_Collects::BUMPER)
		{
			Bumper* newCollect = new Bumper(2, Player2->GetAimDir(), Player2->GetPos());
			Collectibles.push_back(newCollect);
			Player2->SetCollectID(0);
		}
	}

	for (int i = 0; i < Collectibles.size(); i++)
	{
		Collectibles[i]->Update(Player1, Player2, map, ElapsedTime, caméra);
		Collectibles[i]->AddFxs(FXs);

		if (Collectibles[i]->IsAlive() == false)
		{
			Collectibles.erase(Collectibles.begin() + i);
		}
	}

	for (int i = 0; i < FXs.size(); i++)
	{
		FXs[i]->Update(ElapsedTime, Player1, Player2);

		if (FXs[i]->IsAlive() == false)
			FXs.erase(FXs.begin() + i);
	}
}

float Jeu::GetElapsed()
{
	return ElapsedTime;
}

void Jeu::MenuIG(int ID)
{
	if (ID == 0)
	{
		voiture.stop();
		spMenuIG.setTexture(*ResourceManager::Instance()->GetTexture("MenuIG J1"));
		spMenuIG.setOrigin(spMenuIG.getGlobalBounds().width / 2, spMenuIG.getGlobalBounds().height / 2);
		spMenuIG.setPosition(960, 540);
	}
	else if (ID == 1)
	{
		voiture.stop();
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
			if (sf::Joystick::getAxisPosition(ID, sf::Joystick::Axis::X) >= 50 || sf::Joystick::getAxisPosition(ID, sf::Joystick::Axis::Y) >= 50)
			{
				if (SelectionMenuIG < 3)
					SelectionMenuIG++;
				sound.setBuffer(*ResourceManager::Instance()->GetSoundBuffer("Curseur menu"));
				sound.setVolume(GameManager::Instance()->VolumeFX);
				sound.play();
				Clock.restart();
			}
			else if (sf::Joystick::getAxisPosition(ID, sf::Joystick::Axis::X) <= -50 || sf::Joystick::getAxisPosition(ID, sf::Joystick::Axis::Y) <= -50)
			{
				if (SelectionMenuIG > 1)
					SelectionMenuIG--;
				sound.setBuffer(*ResourceManager::Instance()->GetSoundBuffer("Curseur menu"));
				sound.setVolume(GameManager::Instance()->VolumeFX);
				sound.play();
				Clock.restart();
			}

			if (sf::Joystick::isButtonPressed(ID, 0))
			{
				Valider.setBuffer(*ResourceManager::Instance()->GetSoundBuffer("Valider"));
				Valider.setVolume(GameManager::Instance()->VolumeFX);
				Valider.play();
				if (SelectionMenuIG == 1)
				{
					voiture.play();
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
				sound.setBuffer(*ResourceManager::Instance()->GetSoundBuffer("Curseur menu"));
				sound.setVolume(GameManager::Instance()->VolumeFX);
				sound.play();
				Clock.restart();
			}
			else if (sf::Joystick::getAxisPosition(ID, sf::Joystick::Axis::X) <= -50)
			{
				if (SelectionMenuIG > 1)
					SelectionMenuIG--;
				sound.setBuffer(*ResourceManager::Instance()->GetSoundBuffer("Curseur menu"));
				sound.setVolume(GameManager::Instance()->VolumeFX);
				sound.play();
				Clock.restart();
			}

			if (sf::Joystick::isButtonPressed(ID, 0))
			{
				Valider.setBuffer(*ResourceManager::Instance()->GetSoundBuffer("Valider"));
				Valider.setVolume(GameManager::Instance()->VolumeFX);
				Valider.play();
				if (SelectionMenuIG == 1)
				{
					musicNiveau.stop();
					musicNiveau.setVolume(GameManager::Instance()->VolumeMusique);
					musicNiveau.play();
					GameManager::Instance()->m_ActualScene = new Jeu(LevelName, skinJ1, skinJ2);
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
				sound.setBuffer(*ResourceManager::Instance()->GetSoundBuffer("Curseur menu"));
				sound.setVolume(GameManager::Instance()->VolumeFX);
				sound.play();
				Clock.restart();
			}
			else if (sf::Joystick::getAxisPosition(ID, sf::Joystick::Axis::X) <= -50)
			{
				if (SelectionMenuIG > 1)
					SelectionMenuIG--;
				sound.setBuffer(*ResourceManager::Instance()->GetSoundBuffer("Curseur menu"));
				sound.setVolume(GameManager::Instance()->VolumeFX);
				sound.play();
				Clock.restart();
			}

			if (sf::Joystick::isButtonPressed(ID, 0))
			{
				Valider.setBuffer(*ResourceManager::Instance()->GetSoundBuffer("Valider"));
				Valider.setVolume(GameManager::Instance()->VolumeFX);
				Valider.play();
				if (SelectionMenuIG == 1)
				{
					voiture.stop();
					musicNiveau.stop();
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