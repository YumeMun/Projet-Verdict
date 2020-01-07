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


		newSelector->player.setSize(sf::Vector2f(350, 200));
		newSelector->player.setFillColor(sf::Color(250, 194, 73));
		newSelector->player.setOutlineColor(sf::Color(80, 80, 80));
		newSelector->player.setOutlineThickness(7);

		newSelector->spFader.setTexture(*ResourceManager::Instance()->GetTexture("Player_Cache2"));
		newSelector->spFader.setColor(sf::Color(0, 0, 0, 200));

		newSelector->timerSwitchSkin.restart();

		listSelector.push_back(newSelector);
	}

	listSelector[0]->player.setPosition(sf::Vector2f(1920 / 2 - 500, 1080 / 2 - 150));
	listSelector[0]->spPlayer.setPosition(listSelector[0]->player.getPosition());
	listSelector[0]->spFader.setPosition(listSelector[0]->player.getPosition());

	listSelector[1]->player.setFillColor(sf::Color(201, 65, 65));
	listSelector[1]->player.setPosition(sf::Vector2f(1920 / 2 + 150, 1080 / 2 - 150));
	listSelector[1]->spPlayer.setPosition(listSelector[1]->player.getPosition());
	listSelector[1]->spFader.setPosition(listSelector[1]->player.getPosition());

	spReady.setTexture(*ResourceManager::Instance()->GetTexture("Petit bouton non sélectionné"));
	spReady.setPosition((1920 / 2), 800);
	spReady.setOrigin(spReady.getGlobalBounds().width / 2, spReady.getGlobalBounds().height / 2);
	spReady.setScale(sf::Vector2f(1.5, 1.5));

	strSkinSelect[0] = "Les pates sont cuites";
	strSkinSelect[1] = "Choisissez la couleur de votre vehicule";
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
			std::cout << "is taunt" << std::endl;

			if (timerAnim.getElapsedTime().asMilliseconds() > 60)
			{
				if (FrameIndex < 11)
					FrameIndex++;
				else
				{
					FrameIndex = 0;
					listSelector[i]->rectPlayer.top = 0;
					listSelector[i]->isTaunt = false;
					std::cout << "is no longer taunt" << std::endl;
				}

				listSelector[i]->rectPlayer.left = FrameIndex * listSelector[i]->rectPlayer.width;
				listSelector[i]->spPlayer.setTextureRect(listSelector[i]->rectPlayer);

				timerAnim.restart();
			}
		}
		/*else
			FrameIndex = 0;*/
	}

	if (isGameStart)
	{
		transition->Update();
	}
}

void PlayerSelector::Display()
{
	m_actualWindow->draw(spBackground);
	for (int i = 0; i < 2; i++)
	{
		m_actualWindow->draw(listSelector[i]->player);
		m_actualWindow->draw(listSelector[i]->spPlayer);

		if (listSelector[i]->isFadeDrawable)
			m_actualWindow->draw(listSelector[i]->spFader);
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
					if (sf::Joystick::getAxisPosition(i, sf::Joystick::X) > 66.f)
					{
						if (listSelector[i]->SkinSelector != NB_SKIN+1)
							listSelector[i]->SkinSelector += 1;
						else
							listSelector[i]->SkinSelector = 1;

						listSelector[i]->timerSwitchSkin.restart();
					}
					else if (sf::Joystick::getAxisPosition(i, sf::Joystick::X) < -66.f)
					{
						if (listSelector[i]->SkinSelector != 0)
							listSelector[i]->SkinSelector -= 1;
						else
							listSelector[i]->SkinSelector = NB_SKIN + 1;

						listSelector[i]->timerSwitchSkin.restart();
					}
				}

				if (sf::Joystick::isButtonPressed(i, 0))
				{
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

				if (listSelector[0]->isSkinValidate && listSelector[1]->isSkinValidate)
				{
					if (sf::Joystick::isButtonPressed(i, 7))
					{
						GameManager::Instance()->LoadScene(e_Enum::JEU);
					}
				}

				if (listSelector[0]->isSkinValidate)
				{
					spReady.setTexture(*ResourceManager::Instance()->GetTexture("Petit bouton sélectionné"));
				}
				else
					spReady.setTexture(*ResourceManager::Instance()->GetTexture("Petit bouton non sélectionné"));
			}

			/*if (sf::Joystick::isButtonPressed(0, 1))
			{
				GameManager::Instance()->LoadScene(e_Enum::e_Scene::LEVELSELECTOR);
				Retour.setBuffer(*ResourceManager::Instance()->GetSoundBuffer("Retour"));
				Retour.play();
			}
			}*/
		}

		if (sf::Joystick::isButtonPressed(0, 7))
		{
			isGameStart = true;
		}

		if (isGameStart && transition->GetIsTransitionDone())
		{
			GameManager::Instance()->m_ActualScene = new Jeu(LevelName, GetSkinNumberJ1(), GetSkinNumberJ2());
			isGameStart = false;
		}
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