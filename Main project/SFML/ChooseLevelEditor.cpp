#include "ChooseLevelEditor.h"
#include "GameManager.h"
#include "ResourceManager.h"

ChooseLevelEditor::ChooseLevelEditor()
{
	m_actualWindow = GameManager::Instance()->GetWindow();

	spBackground.setTexture(*ResourceManager::Instance()->GetTexture("Background interface"));
	spBackground.setColor(sf::Color{ 100, 100, 100, 255 });

	for (int i = 0; i < 2; i++)
	{
		spChoiceIcon[i].setTexture(*ResourceManager::Instance()->GetTexture("Editeur bouton non sélectionné"));
		spChoiceIcon[i].setOrigin(spChoiceIcon[i].getGlobalBounds().width / 2, spChoiceIcon[i].getGlobalBounds().height / 2);
		spChoiceIcon[i].setPosition(650 + i * 700, 540);

		ChoiceText[i].setFont(*ResourceManager::Instance()->GetFont("Font"));
		ChoiceText[i].setCharacterSize(60);
		ChoiceText[i].setFillColor(sf::Color{ 132, 39, 21, 255});
		ChoiceText[i].setPosition(550 + i * 670, 500);

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
		sound.setBuffer(*ResourceManager::Instance()->GetSoundBuffer("Curseur menu"));
		sound.play();
		SelectionTimer.restart();
	}
	else if (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X) <= -50 && SelectionTimer.getElapsedTime().asMilliseconds() > 300)
	{
		if (ChoiceSelected > 1)
			ChoiceSelected--;
		sound.setBuffer(*ResourceManager::Instance()->GetSoundBuffer("Curseur menu"));
		sound.play();
		SelectionTimer.restart();
	}

	if (ChoiceSelected == 1)
	{
		spChoiceIcon[0].setTexture(*ResourceManager::Instance()->GetTexture("Editeur bouton sélectionné"));

		spChoiceIcon[1].setTexture(*ResourceManager::Instance()->GetTexture("Editeur bouton non sélectionné"));
	}
	else if (ChoiceSelected == 2)
	{
		spChoiceIcon[0].setTexture(*ResourceManager::Instance()->GetTexture("Editeur bouton non sélectionné"));

		spChoiceIcon[1].setTexture(*ResourceManager::Instance()->GetTexture("Editeur bouton sélectionné"));
	}

	if (sf::Joystick::isButtonPressed(0, 0) && SelectionTimer.getElapsedTime().asMilliseconds() > 300)
	{
		Valider.setBuffer(*ResourceManager::Instance()->GetSoundBuffer("Valider"));
		Valider.play();
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
		retour.setBuffer(*ResourceManager::Instance()->GetSoundBuffer("Retour"));
		retour.play();
		GameManager::Instance()->LoadScene(e_Enum::e_Scene::MENU);
	}
}

void ChooseLevelEditor::Display()
{
	m_actualWindow->draw(spBackground);

	for (int i = 0; i < 2; i++)
	{
		m_actualWindow->draw(spChoiceIcon[i]);
		m_actualWindow->draw(ChoiceText[i]);
	}

	m_actualWindow->draw(spBoutonRetour);
}

void ChooseLevelEditor::EventManager(sf::Event p_pollingEvent)
{
}