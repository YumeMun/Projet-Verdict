#include "HudEditor.h"
#include "GameManager.h"
#include "ResourceManager.h"

HudEditor::HudEditor()
{
	std::cout << "HUD constructor" << std::endl;

	m_actualWindow = GameManager::Instance()->GetWindow();

	spBandeau.setTexture(*ResourceManager::Instance()->GetTexture("Bandeau"));

	SelectionShape.setSize(sf::Vector2f{ 51.2, 51.2 });
	SelectionShape.setFillColor(sf::Color::Transparent);
	SelectionShape.setOutlineColor(sf::Color::Green);
	SelectionShape.setOutlineThickness(4);

	for (int i = 0; i < 60; i++)
	{
		spTile[i].setTexture(*ResourceManager::Instance()->GetTexture("Tileset"));

		spTile[0].setTextureRect(sf::IntRect{ 0 * 64, 0 * 64, 64, 64 });
		spTile[1].setTextureRect(sf::IntRect{ 1 * 64, 0 * 64, 64, 64 });
		spTile[2].setTextureRect(sf::IntRect{ 2 * 64, 0 * 64, 64, 64 });
		spTile[3].setTextureRect(sf::IntRect{ 0 * 64, 1 * 64, 64, 64 });
		spTile[4].setTextureRect(sf::IntRect{ 1 * 64, 1 * 64, 64, 64 });
		spTile[5].setTextureRect(sf::IntRect{ 2 * 64, 1 * 64, 64, 64 });
		spTile[6].setTextureRect(sf::IntRect{ 0 * 64, 2 * 64, 64, 64 });
		spTile[7].setTextureRect(sf::IntRect{ 1 * 64, 2 * 64, 64, 64 });
		spTile[8].setTextureRect(sf::IntRect{ 2 * 64, 2 * 64, 64, 64 });
		spTile[9].setTextureRect(sf::IntRect{ 0 * 64, 3 * 64, 64, 64 });
		spTile[10].setTextureRect(sf::IntRect{ 1 * 64, 3 * 64, 64, 64 });
		spTile[11].setTextureRect(sf::IntRect{ 2 * 64, 3 * 64, 64, 64 });
		spTile[12].setTextureRect(sf::IntRect{ 3 * 64, 3 * 64, 64, 64 });
		spTile[13].setTextureRect(sf::IntRect{ 0 * 64, 4 * 64, 64, 64 });
		spTile[14].setTextureRect(sf::IntRect{ 1 * 64, 4 * 64, 64, 64 });
		spTile[15].setTextureRect(sf::IntRect{ 2 * 64, 4 * 64, 64, 64 });
		spTile[16].setTextureRect(sf::IntRect{ 3 * 64, 4 * 64, 64, 64 });
		spTile[17].setTextureRect(sf::IntRect{ 0 * 64, 5 * 64, 64, 64 });
		spTile[18].setTextureRect(sf::IntRect{ 1 * 64, 5 * 64, 64, 64 });
		spTile[19].setTextureRect(sf::IntRect{ 0 * 64, 6 * 64, 64, 64 });
		spTile[20].setTextureRect(sf::IntRect{ 1 * 64, 6 * 64, 64, 64 });
		spTile[21].setTextureRect(sf::IntRect{ 2 * 64, 6 * 64, 64, 64 });
		spTile[22].setTextureRect(sf::IntRect{ 3 * 64, 6 * 64, 64, 64 });
		spTile[23].setTextureRect(sf::IntRect{ 0 * 64, 7 * 64, 64, 64 });
		spTile[24].setTextureRect(sf::IntRect{ 1 * 64, 7 * 64, 64, 64 });
		spTile[25].setTextureRect(sf::IntRect{ 2 * 64, 7 * 64, 64, 64 });
		spTile[26].setTextureRect(sf::IntRect{ 3 * 64, 7 * 64, 64, 64 });
		spTile[27].setTextureRect(sf::IntRect{ 0 * 64, 8 * 64, 64, 64 });
		spTile[28].setTextureRect(sf::IntRect{ 1 * 64, 8 * 64, 64, 64 });
		spTile[29].setTextureRect(sf::IntRect{ 0 * 64, 9 * 64, 64, 64 });
		spTile[30].setTextureRect(sf::IntRect{ 1 * 64, 9 * 64, 64, 64 });
		spTile[31].setTextureRect(sf::IntRect{ 2 * 64, 9 * 64, 64, 64 });
		spTile[32].setTextureRect(sf::IntRect{ 0 * 64, 10 * 64, 64, 64 });
		spTile[33].setTextureRect(sf::IntRect{ 1 * 64, 10 * 64, 64, 64 });
		spTile[34].setTextureRect(sf::IntRect{ 2 * 64, 10 * 64, 64, 64 });

		spTile[i].setScale(0.8, 0.8);
	}

	Selection = 1;
}

HudEditor::~HudEditor()
{
}

void HudEditor::Display()
{
	m_actualWindow->setView(m_actualWindow->getDefaultView());
	m_actualWindow->draw(spBandeau);

	for (int i = 0; i < 35; i++)
	{
		if (i < 27)
			spTile[i].setPosition((i * 70) + 23, 10);
		else
			spTile[i].setPosition(((i - 27) * 70) + 20, 80);

		m_actualWindow->draw(spTile[i]);
	}

	SelectionShape.setPosition(((Selection - 1) * 70) + 23, 10);
	m_actualWindow->draw(SelectionShape);
}

void HudEditor::EventManager(sf::Event p_pollingEvent)
{
	if (sf::Joystick::isConnected(0))
	{
		if (sf::Joystick::isButtonPressed(0, 4) && KeyPress == false)
		{
			if (Selection > 1)
				Selection--;

			KeyPress = true;
		}
		else if (sf::Joystick::isButtonPressed(0, 5) && KeyPress == false)
		{
			if (Selection < 8)
				Selection++;

			KeyPress = true;
		}
		else if (!sf::Joystick::isButtonPressed(0, 4) && !sf::Joystick::isButtonPressed(0, 5))
			KeyPress = false;
	}
}