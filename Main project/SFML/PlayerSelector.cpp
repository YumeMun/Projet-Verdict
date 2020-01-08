#include "PlayerSelector.h"
#include "GameManager.h"
#include "ResourceManager.h"

PlayerSelector::PlayerSelector()
{
}

PlayerSelector::PlayerSelector(std::string _LevelName)
{
	std::cout << "PlayerSelector constructor" << std::endl;

	m_actualWindow = GameManager::Instance()->GetWindow();

	spBackground.setTexture(*ResourceManager::Instance()->GetTexture("Background interface"));
	spBackground.setColor(sf::Color{ 100, 100, 100, 255 });

	LevelName = _LevelName;
}

PlayerSelector::~PlayerSelector()
{
}

void PlayerSelector::Setup()
{



	for (int i = 0; i < 2; i++)
	{
		PlayerSelector* newSelector = new PlayerSelector();

		newSelector->rectPlayer = { 0, 0, 372, 150 };
		newSelector->spPlayer.setTextureRect(newSelector->rectPlayer);
		newSelector->spPlayer.setTexture(*ResourceManager::Instance()->GetTexture("Player" + std::to_string(i+1) + "_Colo1"));

		newSelector->spBc.setTexture(*ResourceManager::Instance()->GetTexture("Background sélection niveau"));
		newSelector->spBc.setScale(sf::Vector2f(0.45, 0.45));

		newSelector->player.setSize(sf::Vector2f(375, 200));
		newSelector->player.setFillColor(sf::Color(250, 194, 73));
		newSelector->player.setOutlineColor(sf::Color(80, 80, 80));
		newSelector->player.setOutlineThickness(7);

		newSelector->spFader.setTexture(*ResourceManager::Instance()->GetTexture("Player_Cache1"));
		newSelector->spFader.setColor(sf::Color(0, 0, 0, 200));

		newSelector->spArrow[0].setTexture(*ResourceManager::Instance()->GetTexture("Selection niveau flèche gauche"));
		newSelector->spArrow[1].setTexture(*ResourceManager::Instance()->GetTexture("Selection niveau flèche droite"));
		//newSelector->spArrow[0].setOrigin(spArrow[0].getGlobalBounds().width / 2, spArrow[0].getGlobalBounds().height / 2);
		//newSelector->spArrow[1].setOrigin(spArrow[1].getGlobalBounds().width / 2, spArrow[1].getGlobalBounds().height / 2);

		newSelector->spCadre[0].setTexture(*ResourceManager::Instance()->GetTexture("cadre_skin"));
		newSelector->spCadre[0].setPosition(1920 / 2 + 150, 1080 / 2 - 150 );
		newSelector->spCadre[1].setTexture(*ResourceManager::Instance()->GetTexture("cadre_skin"));
		newSelector->spCadre[1].setPosition(((1920 / 2) - 150) - newSelector->spCadre[0].getGlobalBounds().width, 1080 / 2 - 150);

		newSelector->timerSwitchSkin.restart();

		listSelector.push_back(newSelector);
	}

	

	listSelector[0]->rectPlayer = { 0, 0, 360, 135 };
	listSelector[0]->spPlayer.setTextureRect(listSelector[0]->rectPlayer);
	listSelector[0]->player.setPosition(sf::Vector2f(1920 / 2 - 525, 1080 / 2 - 150));

	listSelector[0]->spBc.setPosition(sf::Vector2f(1920 / 2 - 550, 1080 / 2 - 150));
	listSelector[0]->spPlayer.setPosition(listSelector[0]->spBc.getPosition().x + 30, listSelector[0]->spBc.getPosition().y + 30);
	listSelector[0]->spFader.setPosition(listSelector[0]->spBc.getPosition().x + 30, listSelector[0]->spBc.getPosition().y + 30);

	//listSelector[0]->spCadre.setPosition(1920 / 2 + 150, 1080 / 2 - 150);
	//listSelector[1]->spCadre.setPosition(1920 / 2 - 150, 1080 / 2 - 150);

	listSelector[1]->player.setFillColor(sf::Color(201, 65, 65));
	listSelector[1]->player.setPosition(sf::Vector2f(1920 / 2 + 150, 1080 / 2 - 150));

	listSelector[1]->spBc.setPosition(sf::Vector2f(1920 / 2 + 125, 1080 / 2 - 150));
	listSelector[1]->spPlayer.setPosition(listSelector[1]->spBc.getPosition().x + 25, listSelector[1]->spBc.getPosition().y + 25);
	listSelector[1]->spFader.setTexture(*ResourceManager::Instance()->GetTexture("Player_Cache2"));
	listSelector[1]->spFader.setPosition(listSelector[1]->spBc.getPosition().x + 25, listSelector[1]->spBc.getPosition().y + 25);

	listSelector[0]->spArrow[0].setPosition(listSelector[0]->spBc.getPosition().x - 65, listSelector[0]->spBc.getPosition().y + (listSelector[0]->spBc.getGlobalBounds().height / 2) - (listSelector[0]->spArrow[0].getGlobalBounds().height / 2));
	listSelector[0]->spArrow[1].setPosition(listSelector[0]->spBc.getPosition().x + 435, listSelector[0]->spBc.getPosition().y + (listSelector[0]->spBc.getGlobalBounds().height / 2) - (listSelector[0]->spArrow[0].getGlobalBounds().height / 2));
	listSelector[1]->spArrow[0].setPosition(listSelector[1]->spBc.getPosition().x - 65, listSelector[1]->spBc.getPosition().y + (listSelector[0]->spBc.getGlobalBounds().height / 2) - (listSelector[0]->spArrow[0].getGlobalBounds().height / 2));
	listSelector[1]->spArrow[1].setPosition(listSelector[1]->spBc.getPosition().x + 435, listSelector[1]->spBc.getPosition().y + (listSelector[0]->spBc.getGlobalBounds().height / 2) - (listSelector[0]->spArrow[0].getGlobalBounds().height / 2));

	spReady.setTexture(*ResourceManager::Instance()->GetTexture("Petit bouton non sélectionné"));
	spReady.setPosition((1920 / 2), 800);
	spReady.setOrigin(spReady.getGlobalBounds().width / 2, spReady.getGlobalBounds().height / 2);
	spReady.setScale(sf::Vector2f(1.5, 1.5));

	strSkinSelect[0] = "Lancer la course";
	strSkinSelect[1] = "Choisissez votre vehicule";
	strSkinSelect[2] = "Cette couleur est déjà prise";

	for (int i = 0; i < 3; i++)
	{
		textSkinSelect[i].setFont(*ResourceManager::Instance()->GetFont("Font"));
		textSkinSelect[i].setString(strSkinSelect[i]);
		textSkinSelect[i].setCharacterSize(40);
		textSkinSelect[i].setFillColor(sf::Color::White);
		textSkinSelect[i].setOrigin(textSkinSelect[i].getGlobalBounds().width / 2, textSkinSelect[i].getGlobalBounds().height / 2);

	}

	textSkinSelect[0].setPosition(spReady.getPosition());
	textSkinSelect[1].setPosition(spReady.getPosition().x, spReady.getPosition().y - 550);
	textSkinSelect[2].setPosition(spReady.getPosition().x, spReady.getPosition().y - 150);

	timerAnim.restart();
	listSelector[0]->timerArrow.restart();
	listSelector[1]->timerArrow.restart();

	transition = new Transition();
}

void PlayerSelector::Update()
{
	if (!isSetup)
	{
		Setup();
		std::cout << "setup player selector" << std::endl;
		isSetup = true;
	}

	for (int y = 0; y < NB_SKIN; y++)
	{
		if (listSelector[0]->SkinSelector == y + 1)
		{
			listSelector[0]->spPlayer.setTexture(*ResourceManager::Instance()->GetTexture("Player1_Colo" + std::to_string(y + 1)));
		}
		else if (listSelector[1]->SkinSelector == y + 1)
		{
			listSelector[1]->spPlayer.setTexture(*ResourceManager::Instance()->GetTexture("Player2_Colo" + std::to_string(y + 1)));
		}
	}

	for (int i = 0; i < 2; i++)
	{
		if (listSelector[i]->isSkinValidate)
			listSelector[i]->player.setOutlineColor(sf::Color::Green);
		else
			listSelector[i]->player.setOutlineColor(sf::Color::Black);
	}

	if (listSelector[0]->isSkinValidate)
	{
		if (listSelector[1]->SkinSelector == listSelector[0]->SkinSelector)
			listSelector[1]->isFadeDrawable = true;
		else
			listSelector[1]->isFadeDrawable = false;
	}
	else if (listSelector[1]->isSkinValidate)
	{
		if (listSelector[0]->SkinSelector == listSelector[1]->SkinSelector)
			listSelector[0]->isFadeDrawable = true;
		else
			listSelector[0]->isFadeDrawable = false;
	}
	else
	{
		listSelector[0]->isFadeDrawable = false;
		listSelector[1]->isFadeDrawable = false;
	}

	if (timerAlreadyUse.getElapsedTime().asSeconds() > 2.5)
	{
		isAlreadyUseDrawable = false;
	}

	for (int i = 0; i < 2; i++)
	{
		if (listSelector[i]->isTaunt)
		{
			listSelector[i]->rectPlayer.top = 4 * listSelector[i]->rectPlayer.height;

			if (timerAnim.getElapsedTime().asMilliseconds() > 60)
			{
				if (FrameIndex < 11)
					FrameIndex++;
				else
				{
					FrameIndex = 0;
					listSelector[i]->rectPlayer.top = 0;
					listSelector[i]->isTaunt = false;
				}

				listSelector[i]->rectPlayer.left = FrameIndex * listSelector[i]->rectPlayer.width;
				listSelector[i]->spPlayer.setTextureRect(listSelector[i]->rectPlayer);

				timerAnim.restart();
			}
		}

		if (sf::Joystick::isButtonPressed(i, 4))
		{
			listSelector[i]->spArrow[0].setScale(sf::Vector2f(0.9, 0.9));
			std::cout << "AAA" << std::endl;
		}
		else if (sf::Joystick::isButtonPressed(i, 5))
		{
			listSelector[i]->spArrow[1].setScale(sf::Vector2f(0.9, 0.9));
			std::cout << "BBB" << std::endl;
		}
		else
		{
			listSelector[i]->spArrow[0].setScale(sf::Vector2f(0.75, 0.75));
			listSelector[i]->spArrow[1].setScale(sf::Vector2f(0.75, 0.75));
		}
	}

	if (isGameStart)
	{
		transition->Update();
	}
}

void PlayerSelector::Display()
{
	m_actualWindow->draw(spBackground);
	m_actualWindow->draw(listSelector[0]->spCadre[0]);
	m_actualWindow->draw(listSelector[0]->spCadre[1]);
	for (int i = 0; i < 2; i++)
	{
		//m_actualWindow->draw(listSelector[i]->player);
		//m_actualWindow->draw(listSelector[i]->spBc);
		
		m_actualWindow->draw(listSelector[i]->spPlayer);

		if (listSelector[i]->isFadeDrawable)
			m_actualWindow->draw(listSelector[i]->spFader);
	}

	for (int i = 0; i < 2; i++)
	{
		for (int y = 0; y < 2; y++)
		{
			m_actualWindow->draw(listSelector[i]->spArrow[y]);
		}
	}

	m_actualWindow->draw(spReady);
	//m_actualWindow->draw(textReady);

	/*for (int i = 0; i == 2;)
	{
		m_actualWindow->draw(textSkinSelect[i]);
	}*/

	m_actualWindow->draw(textSkinSelect[0]);
	m_actualWindow->draw(textSkinSelect[1]);

	if (isAlreadyUseDrawable)
		m_actualWindow->draw(textSkinSelect[2]);

	if (isGameStart)
		transition->DrawTransition();

	m_actualWindow->draw(spBoutonRetour);
}

void PlayerSelector::EventManager(sf::Event p_pollingEvent)
{
	if (SelectionTimer.getElapsedTime().asMilliseconds() > 500)
	{
		for (int i = 0; i < 2; i++)
		{
			if (listSelector[i]->isSkinValidate == false)
			{
				if (listSelector[i]->timerSwitchSkin.getElapsedTime().asMilliseconds() > 125)
				{
					if (/*sf::Joystick::getAxisPosition(i, sf::Joystick::X) > 66.f ||*/ sf::Joystick::isButtonPressed(i, 5))
					{
						sound.setBuffer(*ResourceManager::Instance()->GetSoundBuffer("Curseur menu"));
						sound.play();

						if (listSelector[i]->SkinSelector < NB_SKIN)
							listSelector[i]->SkinSelector += 1;
						else if(listSelector[i]->SkinSelector >= NB_SKIN)
							listSelector[i]->SkinSelector = 1;

						listSelector[i]->timerSwitchSkin.restart();

						std::cout << "nb = " << listSelector[0]->SkinSelector << std::endl;
					}
					else if (/*sf::Joystick::getAxisPosition(i, sf::Joystick::X) < -66.f ||*/ sf::Joystick::isButtonPressed(i, 4))
					{
						sound.setBuffer(*ResourceManager::Instance()->GetSoundBuffer("Curseur menu"));
						sound.play();

						if (listSelector[i]->SkinSelector > 1)
							listSelector[i]->SkinSelector -= 1;
						else if(listSelector[i]->SkinSelector <= 1)
							listSelector[i]->SkinSelector = NB_SKIN;

						listSelector[i]->timerSwitchSkin.restart();

						std::cout << "nb = " << listSelector[0]->SkinSelector << std::endl;
					}
				}

				if (sf::Joystick::isButtonPressed(i, 0))
				{
					Valider.setBuffer(*ResourceManager::Instance()->GetSoundBuffer("Valider"));
					Valider.play();

					if (!listSelector[i]->isFadeDrawable)
					{
						listSelector[i]->isSkinValidate = true;
						listSelector[i]->isTaunt = true;
					}
					else
					{
						timerAlreadyUse.restart();
						isAlreadyUseDrawable = true;
					}
				}
			}
			else
			{

				if (sf::Joystick::isButtonPressed(i, 1))
				{
					listSelector[i]->isSkinValidate = false;
				}
			}

			/*for (int i = 0; i < 2; i++)
			{
				if (listSelector[i]->isSkinValidate)
				{
					
				}
				else
					
			}*/

			if (listSelector[0]->isSkinValidate && listSelector[1]->isSkinValidate)
			{
				spReady.setTexture(*ResourceManager::Instance()->GetTexture("Petit bouton sélectionné"));

				/*if (sf::Joystick::isButtonPressed(i, 7))
				{
					GameManager::Instance()->LoadScene(e_Enum::JEU);
				}*/
				if (sf::Joystick::isButtonPressed(i, 7))
					isGameStart = true;

				if (isGameStart && transition->GetIsTransitionDone())
				{
					GameManager::Instance()->m_ActualScene = new Jeu(LevelName, GetSkinNumberJ1(), GetSkinNumberJ2());
					isGameStart = false;
				}
			}
			else
				spReady.setTexture(*ResourceManager::Instance()->GetTexture("Petit bouton non sélectionné"));

			if (sf::Joystick::isButtonPressed(0, 1))
			{
				GameManager::Instance()->LoadScene(e_Enum::e_Scene::LEVELSELECTOR);
				Retour.setBuffer(*ResourceManager::Instance()->GetSoundBuffer("Retour"));
				Retour.play();
			
			}
		}

		///a retirer pour presentation
		/*for (int i = 0; i < 2; i++)
		{
			if (sf::Joystick::isButtonPressed(i, 7))
			{
				isGameStart = true;
			}
		}

		if (isGameStart && transition->GetIsTransitionDone())
		{
			GameManager::Instance()->m_ActualScene = new Jeu(LevelName, GetSkinNumberJ1(), GetSkinNumberJ2());
			isGameStart = false;
		}*/
		////
	}
}

int PlayerSelector::GetSkinNumberJ1()
{
	return listSelector[0]->SkinSelector;
}

int PlayerSelector::GetSkinNumberJ2()
{
	return listSelector[1]->SkinSelector;
}