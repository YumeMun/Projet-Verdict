#include "Options.h"
#include "GameManager.h"
#include "ResourceManager.h"

Options::Options()
{
	std::cout << "Options constructor" << std::endl;

	m_actualWindow = GameManager::Instance()->GetWindow();

	spBackground.setTexture(*ResourceManager::Instance()->GetTexture("Background interface"));
	spFlèche.setTexture(*ResourceManager::Instance()->GetTexture("Flèche menu"));

	for (int i = 0; i < 2; i++)
	{
		OptionsText[i].setFont(*ResourceManager::Instance()->GetFont("Font"));
		OptionsText[i].setCharacterSize(50);
		OptionsText[i].setFillColor(sf::Color::White);
		OptionsText[i].setPosition(500, 250 + i * 350);
		OptionsText[0].setString("Volume de la musique");
		OptionsText[1].setString("Volume des effets sonores");

		VolumeRect[i].width = 241, VolumeRect[i].height = 158;

		spIconeVolume[i].setTexture(*ResourceManager::Instance()->GetTexture("Icone volume"));
		spIconeVolume[i].setPosition(750, 400 + i * 350);

		spVolume[i].setTexture(*ResourceManager::Instance()->GetTexture("Volume"));
		spVolume[i].setPosition(850, 350 + i * 350);
		spVolume[i].setTextureRect(VolumeRect[i]);

		spButton[i].setTexture(*ResourceManager::Instance()->GetTexture("Options bouton non sélectionné"));
		spButton[i].setPosition(500, 250 + i * 350);
	}

	if (GameManager::Instance()->VolumeMusique == 0)
		VolumeRect[0].left = 0;
	else if(GameManager::Instance()->VolumeMusique == 20)
		VolumeRect[0].left = 1 * VolumeRect[0].width;
	else if (GameManager::Instance()->VolumeMusique == 40)
		VolumeRect[0].left = 2 * VolumeRect[0].width;
	else if (GameManager::Instance()->VolumeMusique == 60)
		VolumeRect[0].left = 3 * VolumeRect[0].width;
	else if (GameManager::Instance()->VolumeMusique == 80)
		VolumeRect[0].left = 4 * VolumeRect[0].width;
	else if (GameManager::Instance()->VolumeMusique == 100)
		VolumeRect[0].left = 5 * VolumeRect[0].width;

	if (GameManager::Instance()->VolumeFX == 0)
		VolumeRect[1].left = 0;
	else if (GameManager::Instance()->VolumeFX == 20)
		VolumeRect[1].left = 1 * VolumeRect[1].width;
	else if (GameManager::Instance()->VolumeFX == 40)
		VolumeRect[1].left = 2 * VolumeRect[1].width;
	else if (GameManager::Instance()->VolumeFX == 60)
		VolumeRect[1].left = 3 * VolumeRect[1].width;
	else if (GameManager::Instance()->VolumeFX == 80)
		VolumeRect[1].left = 4 * VolumeRect[1].width;
	else if (GameManager::Instance()->VolumeFX == 100)
		VolumeRect[1].left = 5 * VolumeRect[1].width;

	spVolume[0].setTextureRect(VolumeRect[0]);
	spVolume[1].setTextureRect(VolumeRect[1]);
}

Options::~Options()
{
}

void Options::Update()
{
	if (sf::Joystick::isButtonPressed(0, 1))
	{
		GameManager::Instance()->LoadScene(e_Enum::e_Scene::MENU);
	}

	if (sf::Joystick::getAxisPosition(0, sf::Joystick::Y) >= 50)
	{
		if (Selection == 1)
			Selection = 2;
	}
	else if (sf::Joystick::getAxisPosition(0, sf::Joystick::Y) <= -50)
	{
		if (Selection == 2)
			Selection = 1;
	}

	if (Selection == 1)
	{
		spFlèche.setPosition(510, 260);
		OptionsText[0].setPosition(580, OptionsText[0].getPosition().y);
		OptionsText[1].setPosition(500, OptionsText[1].getPosition().y);
		spButton[0].setTexture(*ResourceManager::Instance()->GetTexture("Options bouton sélectionné"));
		spButton[1].setTexture(*ResourceManager::Instance()->GetTexture("Options bouton non sélectionné"));

		if (SelectionTimer.getElapsedTime().asMilliseconds() > 200)
		{
			if (sf::Joystick::getAxisPosition(0, sf::Joystick::X) >= 50)
			{
				if (VolumeRect[0].left < 5 * VolumeRect[0].width)
				{
					VolumeRect[0].left += VolumeRect[0].width;
				}
				SelectionTimer.restart();
			}
			else if (sf::Joystick::getAxisPosition(0, sf::Joystick::X) <= -50)
			{
				if (VolumeRect[0].left > 0)
				{
					VolumeRect[0].left -= VolumeRect[0].width;
				}
				
				SelectionTimer.restart();
			}
		}

		spVolume[0].setTextureRect(VolumeRect[0]);
	}
	else if (Selection == 2)
	{
		spFlèche.setPosition(510, 610);
		OptionsText[0].setPosition(500, OptionsText[0].getPosition().y);
		OptionsText[1].setPosition(580, OptionsText[1].getPosition().y);
		spButton[0].setTexture(*ResourceManager::Instance()->GetTexture("Options bouton non sélectionné"));
		spButton[1].setTexture(*ResourceManager::Instance()->GetTexture("Options bouton sélectionné"));

		if (SelectionTimer.getElapsedTime().asMilliseconds() > 200)
		{
			if (sf::Joystick::getAxisPosition(0, sf::Joystick::X) >= 50)
			{
				if (VolumeRect[1].left < 5 * VolumeRect[1].width)
				{
					VolumeRect[1].left += VolumeRect[1].width;
				}
				SelectionTimer.restart();
			}
			else if (sf::Joystick::getAxisPosition(0, sf::Joystick::X) <= -50)
			{
				if (VolumeRect[1].left > 0)
				{
					VolumeRect[1].left -= VolumeRect[1].width;
				}

				SelectionTimer.restart();
			}
		}

		spVolume[1].setTextureRect(VolumeRect[1]);
	}

	if (VolumeRect[0].left == 0)
		GameManager::Instance()->VolumeMusique = 0;
	else if (VolumeRect[0].left == 1 * VolumeRect[0].width)
		GameManager::Instance()->VolumeMusique = 20;
	else if (VolumeRect[0].left == 2 * VolumeRect[0].width)
		GameManager::Instance()->VolumeMusique = 40;
	else if (VolumeRect[0].left == 3 * VolumeRect[0].width)
		GameManager::Instance()->VolumeMusique = 60;
	else if (VolumeRect[0].left == 4 * VolumeRect[0].width)
		GameManager::Instance()->VolumeMusique = 80;
	else if (VolumeRect[0].left == 5 * VolumeRect[0].width)
		GameManager::Instance()->VolumeMusique = 100;

	if (VolumeRect[1].left == 0)
		GameManager::Instance()->VolumeFX = 0;
	else if (VolumeRect[1].left == 1 * VolumeRect[1].width)
		GameManager::Instance()->VolumeFX = 20;
	else if (VolumeRect[1].left == 2 * VolumeRect[1].width)
		GameManager::Instance()->VolumeFX = 40;
	else if (VolumeRect[1].left == 3 * VolumeRect[1].width)
		GameManager::Instance()->VolumeFX = 60;
	else if (VolumeRect[1].left == 4 * VolumeRect[1].width)
		GameManager::Instance()->VolumeFX = 80;
	else if (VolumeRect[1].left == 5 * VolumeRect[1].width)
		GameManager::Instance()->VolumeFX = 100;

	std::cout << "Volume musique : " << GameManager::Instance()->VolumeMusique << std::endl;
	std::cout << "Volume fx : " << GameManager::Instance()->VolumeFX << std::endl;
}

void Options::Display()
{
	m_actualWindow->draw(spBackground);
	for (int i = 0; i < 2; i++)
	{
		m_actualWindow->draw(spIconeVolume[i]);
		m_actualWindow->draw(spVolume[i]);
		m_actualWindow->draw(spButton[i]);
		m_actualWindow->draw(OptionsText[i]);
	}
	m_actualWindow->draw(spFlèche);
}

void Options::EventManager(sf::Event p_pollingEvent)
{
}
