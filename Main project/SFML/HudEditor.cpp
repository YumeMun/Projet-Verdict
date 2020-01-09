#include "HudEditor.h"
#include "GameManager.h"
#include "ResourceManager.h"

HudEditor::HudEditor()
{
	m_actualWindow = GameManager::Instance()->GetWindow();

	spBandeau.setTexture(*ResourceManager::Instance()->GetTexture("Bandeau"));

	spInfoTileRect.setTexture(*ResourceManager::Instance()->GetTexture("Info tile"));
	spInfoTileRect.setOrigin(spInfoTileRect.getGlobalBounds().width / 2, spInfoTileRect.getGlobalBounds().height / 2);
	spInfoTileRect.setPosition(960, 1080 - (75 / 2));

	InfoTileText.setFont(*ResourceManager::Instance()->GetFont("Font"));
	InfoTileText.setFillColor(sf::Color::White);
	InfoTileText.setCharacterSize(35);

	SelectionShape.setSize(sf::Vector2f{ 51.2, 51.2 });
	SelectionShape.setFillColor(sf::Color::Transparent);
	SelectionShape.setOutlineColor(sf::Color::Green);
	SelectionShape.setOutlineThickness(4);

	spTouches[0].setTexture(*ResourceManager::Instance()->GetTexture("LB"));
	spTouches[1].setTexture(*ResourceManager::Instance()->GetTexture("RB"));

	spTouches[0].setPosition(10, 45);
	spTouches[1].setPosition(1770, 45);

	for (int i = 0; i < 30; i++)
	{
		spTile[i].setTexture(*ResourceManager::Instance()->GetTexture("Tileset"));
		spTile[i].setScale(0.8, 0.8);

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

		spTile[19].setScale(0.2, 0.2);
		spTile[19].setTextureRect(sf::IntRect{ 0 * 64, 13 * 64, 4 * 64, 64 });

		spTile[20].setScale(0.2, 0.2);
		spTile[20].setTextureRect(sf::IntRect{ 0 * 64, 14 * 64, 64, 4 * 64 });

		spTile[21].setScale(0.28, 0.28);
		spTile[21].setTextureRect(sf::IntRect{ 14 * 64, 18 * 64, 64, 3 * 64 });

		spTile[22].setTextureRect(sf::IntRect{ 9 * 64, 12 * 64, 64, 64 });

		spTile[23].setTextureRect(sf::IntRect{ 0 * 64, 11 * 64, 64, 64 });
		spTile[24].setTextureRect(sf::IntRect{ 1 * 64, 11 * 64, 64, 64 });
		spTile[25].setTextureRect(sf::IntRect{ 2 * 64, 11 * 64, 64, 64 });
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

	for (int i = 0; i < 26; i++)
	{
		if (i < 23)
			spTile[i].setPosition((i * 70) + 162, 12);
		else
			spTile[i].setPosition(((i - 23) * 70) + 162, 82);

		spTile[19].setPosition((i * 70) + 162, 23);
		spTile[20].setPosition((i * 70) + 185, 10);
		spTile[21].setPosition((i * 70) + 180, 10);

		m_actualWindow->draw(spTile[i]);
	}

	if (Selection < 24)
		SelectionShape.setPosition(((Selection - 1) * 70) + 162, 12);
	else
		SelectionShape.setPosition(((Selection - 24) * 70) + 162, 82);

	m_actualWindow->draw(SelectionShape);

	for (int i = 0; i < 2; i++)
	{
		m_actualWindow->draw(spTouches[i]);
	}

	TileName();

	m_actualWindow->draw(spInfoTileRect);
	m_actualWindow->draw(InfoTileText);
}

void HudEditor::EventManager(sf::Event p_pollingEvent)
{
	if (sf::Joystick::isButtonPressed(0, 4) && SelectionTimer.getElapsedTime().asMilliseconds() > 100)
	{
		if (Selection > 1)
			Selection--;
		else
			Selection = 26;

		SelectionTimer.restart();
	}
	if (sf::Joystick::isButtonPressed(0, 5) && SelectionTimer.getElapsedTime().asMilliseconds() > 100)
	{
		if (Selection < 26)
			Selection++;
		else
			Selection = 1;

		SelectionTimer.restart();
	}

	if (sf::Joystick::isButtonPressed(0, 4))
		spTouches[0].setTexture(*ResourceManager::Instance()->GetTexture("LB Press"));
	else if (sf::Joystick::isButtonPressed(0, 5))
		spTouches[1].setTexture(*ResourceManager::Instance()->GetTexture("RB Press"));
	else if (!sf::Joystick::isButtonPressed(0, 4) && !sf::Joystick::isButtonPressed(0, 5))
	{
		spTouches[0].setTexture(*ResourceManager::Instance()->GetTexture("LB"));
		spTouches[1].setTexture(*ResourceManager::Instance()->GetTexture("RB"));
	}
}

void HudEditor::TileName()
{
	if (Selection == 1)
		InfoTileText.setString("Route 1");
	else if (Selection == 2)
		InfoTileText.setString("Route 2");
	else if (Selection == 3)
		InfoTileText.setString("Route 3");
	else if (Selection == 4)
		InfoTileText.setString("Route 4");
	else if (Selection == 5)
		InfoTileText.setString("Route 5");
	else if (Selection == 6)
		InfoTileText.setString("Route 6");
	else if (Selection == 7)
		InfoTileText.setString("Pente 1");
	else if (Selection == 8)
		InfoTileText.setString("Pente 2");
	else if (Selection == 9)
		InfoTileText.setString("Pente 3");
	else if (Selection == 10)
		InfoTileText.setString("Pente 4");
	else if (Selection == 11)
		InfoTileText.setString("Boost 1");
	else if (Selection == 12)
		InfoTileText.setString("Boost 2");
	else if (Selection == 13)
		InfoTileText.setString("Boost 3");
	else if (Selection == 14)
		InfoTileText.setString("Boost 4");
	else if (Selection == 15)
		InfoTileText.setString("Boost 5");
	else if (Selection == 16)
		InfoTileText.setString("Pillier 1");
	else if (Selection == 17)
		InfoTileText.setString("Caisse 1");
	else if (Selection == 18)
		InfoTileText.setString("Caisse 2");
	else if (Selection == 19)
	{
		InfoTileText.setCharacterSize(35);
		InfoTileText.setString("Caisse 3");
	}
	else if (Selection == 20)
	{
		InfoTileText.setCharacterSize(30);
		InfoTileText.setString("   Champ\nélectrique 1");
	}
	else if (Selection == 21)
	{
		InfoTileText.setCharacterSize(30);
		InfoTileText.setString("   Champ\nélectrique 2");
	}
	else if (Selection == 22)
	{
		InfoTileText.setCharacterSize(35);
		InfoTileText.setString("Laser");
	}
	else if (Selection == 23)
		InfoTileText.setString("Collectible");
	else if (Selection == 24)
		InfoTileText.setString("Départ");
	else if (Selection == 25)
		InfoTileText.setString("Arrivée");
	else if (Selection == 26)
		InfoTileText.setString("Checkpoint");

	InfoTileText.setOrigin(InfoTileText.getGlobalBounds().width / 2, InfoTileText.getGlobalBounds().height / 2);
	InfoTileText.setPosition(960, 1030);
}