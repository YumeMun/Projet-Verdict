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

	rectPlay.setPosition(sf::Vector2f(1920 / 2, 1080 / 2 + 200));
	rectPlay.setSize(sf::Vector2f(300, 100));
	rectPlay.setFillColor(sf::Color::Yellow);

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
		newSelector->spPlayer.setOrigin(spPlayer.getGlobalBounds().width / 2, spPlayer.getGlobalBounds().height / 2);
		newSelector->spPlayer.setTexture(*ResourceManager::Instance()->GetTexture("Player1"));
		newSelector->timerSwitchSkin.restart();

		listSelector.push_back(newSelector);
	}

	listSelector[0]->player.setPosition(sf::Vector2f(1920 / 2 - 300, 1080 / 2));
	listSelector[0]->player.setSize(sf::Vector2f(200, 100));
	listSelector[0]->player.setFillColor(sf::Color::Green);
	listSelector[0]->player.setOutlineColor(sf::Color::Black);
	listSelector[0]->player.setOutlineThickness(5);

	listSelector[1]->player.setPosition(sf::Vector2f(1920 / 2 + 300, 1080 / 2));
	listSelector[1]->player.setSize(sf::Vector2f(200, 100));
	listSelector[1]->player.setFillColor(sf::Color::Red);
	listSelector[1]->player.setOutlineColor(sf::Color::Black);
	listSelector[1]->player.setOutlineThickness(5);

	listSelector[0]->spPlayer.setPosition(sf::Vector2f(1920 / 2 - 300, 1080 / 2));

	listSelector[1]->spPlayer.setPosition(sf::Vector2f(1920 / 2 + 300, 1080 / 2));

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

	for (int y = 0; y < 2; y++)
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
		if (listSelector[i]->SkinSelector == 1)
		{
			listSelector[i]->player.setFillColor(sf::Color::Magenta);
		}
		else if (listSelector[i]->SkinSelector == 2)
		{
			listSelector[i]->player.setFillColor(sf::Color::Cyan);
		}
		else if (listSelector[i]->SkinSelector == 3)
		{
			listSelector[i]->player.setFillColor(sf::Color::Yellow);
		}

		if (listSelector[i]->isSkinValidate)
		{
			listSelector[i]->player.setOutlineColor(sf::Color::Green);
		}
		else
			listSelector[i]->player.setOutlineColor(sf::Color::Black);
	}

	if (isGameStart)
	{
		transition->Update();
	}
}

void PlayerSelector::Display()
{
	m_actualWindow->draw(spBackground);
	//m_actualWindow->draw(rectPlay);
	for (int i = 0; i < 2; i++)
	{
		m_actualWindow->draw(listSelector[i]->player);
		m_actualWindow->draw(listSelector[i]->spPlayer);
	}

	if (isGameStart)
	{
		transition->DrawTransition();
	}

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
				if (listSelector[i]->timerSwitchSkin.getElapsedTime().asMilliseconds() > 150)
				{
					if (sf::Joystick::getAxisPosition(i, sf::Joystick::X) > 66.f)
					{
						if (listSelector[i]->SkinSelector != 3)
							listSelector[i]->SkinSelector += 1;
						else
							listSelector[i]->SkinSelector = 3;

						listSelector[i]->timerSwitchSkin.restart();
					}
					else if (sf::Joystick::getAxisPosition(i, sf::Joystick::X) < -66.f)
					{
						if (listSelector[i]->SkinSelector != 1)
							listSelector[i]->SkinSelector -= 1;
						else
							listSelector[i]->SkinSelector = 1;

						listSelector[i]->timerSwitchSkin.restart();
					}
				}

				if (sf::Joystick::isButtonPressed(i, 0))
				{
					listSelector[i]->isSkinValidate = true;
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
			}

			if (sf::Joystick::isButtonPressed(0, 1))
			{
				GameManager::Instance()->LoadScene(e_Enum::e_Scene::LEVELSELECTOR);
				Retour.setBuffer(*ResourceManager::Instance()->GetSoundBuffer("Retour"));
				Retour.play();
			}
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