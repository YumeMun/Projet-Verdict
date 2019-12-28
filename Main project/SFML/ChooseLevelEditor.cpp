#include "ChooseLevelEditor.h"
#include "GameManager.h"
#include "ResourceManager.h"

ChooseLevelEditor::ChooseLevelEditor()
{
	m_actualWindow = GameManager::Instance()->GetWindow();

	spBackground.setTexture(*ResourceManager::Instance()->GetTexture("Background interface"));

	for (int i = 0; i < 2; i++)
	{
		ChoiceIcon[i].setRadius(120);
		ChoiceIcon[i].setFillColor(sf::Color::Black);
		ChoiceIcon[i].setOutlineColor(sf::Color::White);
		ChoiceIcon[i].setOutlineThickness(3);
		ChoiceIcon[i].setPosition(600 + i * 450, 450);

		ChoiceText[i].setFont(*ResourceManager::Instance()->GetFont("Font"));
		ChoiceText[i].setCharacterSize(40);
		ChoiceText[i].setFillColor(sf::Color::White);
		ChoiceText[i].setPosition(660 + i * 430, 540);

		ChoiceText[0].setString("Ouvrir");
		ChoiceText[1].setString("Nouveau");
	}

	ChoiceSelected = 1;
}

ChooseLevelEditor::~ChooseLevelEditor()
{
}

void ChooseLevelEditor::Update()
{
	if (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X) >= 50 && SelectionTimer.getElapsedTime().asMilliseconds() > 300)
	{
		if (ChoiceSelected < 2)
			ChoiceSelected++;

		SelectionTimer.restart();
	}
	else if (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X) <= -50 && SelectionTimer.getElapsedTime().asMilliseconds() > 300)
	{
		if (ChoiceSelected > 1)
			ChoiceSelected--;

		SelectionTimer.restart();
	}

	if (ChoiceSelected == 1)
	{
		ChoiceIcon[0].setOutlineColor(sf::Color::Red);
		ChoiceText[0].setFillColor(sf::Color::Red);

		ChoiceIcon[1].setOutlineColor(sf::Color::White);
		ChoiceText[1].setFillColor(sf::Color::White);
	}
	else if (ChoiceSelected == 2)
	{
		ChoiceIcon[0].setOutlineColor(sf::Color::White);
		ChoiceText[0].setFillColor(sf::Color::White);

		ChoiceIcon[1].setOutlineColor(sf::Color::Red);
		ChoiceText[1].setFillColor(sf::Color::Red);
	}

	if (sf::Joystick::isButtonPressed(0, 0) && SelectionTimer.getElapsedTime().asMilliseconds() > 300)
	{
		if (ChoiceSelected == 1)
		{
			GameManager::Instance()->LoadScene(e_Enum::e_Scene::OPENLEVELEDITOR);
		}
		else if (ChoiceSelected == 2)
		{
			GameManager::Instance()->LoadScene(e_Enum::e_Scene::SIZEEDITOR);
		}
	}
	else if (sf::Joystick::isButtonPressed(0, 1) && SelectionTimer.getElapsedTime().asMilliseconds() > 300)
	{
		GameManager::Instance()->LoadScene(e_Enum::e_Scene::MENU);
	}
}

void ChooseLevelEditor::Display()
{
	m_actualWindow->draw(spBackground);

	for (int i = 0; i < 2; i++)
	{
		m_actualWindow->draw(ChoiceIcon[i]);
		m_actualWindow->draw(ChoiceText[i]);
	}
}

void ChooseLevelEditor::EventManager(sf::Event p_pollingEvent)
{
}