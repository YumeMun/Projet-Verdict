#include "SizeEditor.h"
#include "GameManager.h"
#include "ResourceManager.h"

SizeEditor::SizeEditor()
{

	m_actualWindow = GameManager::Instance()->GetWindow();

	spBackground.setTexture(*ResourceManager::Instance()->GetTexture("Background interface"));
	spBackground.setColor(sf::Color{ 100, 100, 100, 255 });

	spFlèche.setTexture(*ResourceManager::Instance()->GetTexture("Flèche menu"));
	spFlèche.setPosition(70, 90);

	LevelSelected = 1;

	spButton.setTexture(*ResourceManager::Instance()->GetTexture("Menu bouton non sélectionné"));
	spButton.setScale(1.8, 1);
	spButton.setOrigin(spButton.getGlobalBounds().width / 2, spButton.getGlobalBounds().height / 2);
	spButton.setPosition(1400, 105);

	EnterSizeText.setFont(*ResourceManager::Instance()->GetFont("Font"));
	EnterSizeText.setFillColor(sf::Color::White);
	EnterSizeText.setCharacterSize(50);
	EnterSizeText.setString("Choisissez une taille pour votre niveau");
	EnterSizeText.setPosition(sf::Vector2f{ 120, 75 });

	spInfosRect.setTexture(*ResourceManager::Instance()->GetTexture("Fenêtre popup"));
	spInfosRect.setOrigin(spInfosRect.getGlobalBounds().width / 2, spInfosRect.getGlobalBounds().height / 2);
	spInfosRect.setPosition(960, 800);

	InfosText.setFont(*ResourceManager::Instance()->GetFont("Font"));
	InfosText.setCharacterSize(35);
	InfosText.setFillColor(sf::Color::White);
	InfosText.setPosition(spInfosRect.getPosition().x - 230, spInfosRect.getPosition().y - 50);

	for (int i = 0; i < 3; i++)
	{
		spLevelIcon[i].setTexture(*ResourceManager::Instance()->GetTexture("Editeur bouton non sélectionné"));
		spLevelIcon[i].setScale(0.7, 0.7);
		spLevelIcon[i].setPosition(350 + i * 400, 300);

		LevelNumero[i].setFont(*ResourceManager::Instance()->GetFont("Font"));
		LevelNumero[i].setCharacterSize(60);
		LevelNumero[i].setFillColor(sf::Color{ 132, 39, 21, 255 });
		LevelNumero[0].setString("1");
		LevelNumero[1].setString("2");
		LevelNumero[2].setString("3");
		LevelNumero[i].setPosition(540 + i * 400, 380);
	}
}

SizeEditor::~SizeEditor()
{
}

void SizeEditor::Update()
{
	if (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X) >= 50 && SelectionTimer.getElapsedTime().asMilliseconds() > 300)
	{
		if(LevelSelected < 3)
		LevelSelected++;
		sound.setBuffer(*ResourceManager::Instance()->GetSoundBuffer("Curseur menu"));
		sound.setVolume(GameManager::Instance()->VolumeFX);
		sound.play();
		SelectionTimer.restart();
	}
	else if (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X) <= -50 && SelectionTimer.getElapsedTime().asMilliseconds() > 300)
	{
		if(LevelSelected > 1)
		LevelSelected--;
		sound.setBuffer(*ResourceManager::Instance()->GetSoundBuffer("Curseur menu"));
		sound.setVolume(GameManager::Instance()->VolumeFX);
		sound.play();
		SelectionTimer.restart();
	}

	if (LevelSelected == 1)
	{
		spLevelIcon[0].setTexture(*ResourceManager::Instance()->GetTexture("Editeur bouton sélectionné"));

		spLevelIcon[1].setTexture(*ResourceManager::Instance()->GetTexture("Editeur bouton non sélectionné"));

		spLevelIcon[2].setTexture(*ResourceManager::Instance()->GetTexture("Editeur bouton non sélectionné"));

		InfosText.setString("Longueur : Courte\nDurée estimée : 40 secondes");
	}
	else if (LevelSelected == 2)
	{
		spLevelIcon[0].setTexture(*ResourceManager::Instance()->GetTexture("Editeur bouton non sélectionné"));

		spLevelIcon[1].setTexture(*ResourceManager::Instance()->GetTexture("Editeur bouton sélectionné"));

		spLevelIcon[2].setTexture(*ResourceManager::Instance()->GetTexture("Editeur bouton non sélectionné"));

		InfosText.setString("Longueur : Moyenne\nDurée estimée : 1 minute");
	}
	else if (LevelSelected == 3)
	{
		spLevelIcon[0].setTexture(*ResourceManager::Instance()->GetTexture("Editeur bouton non sélectionné"));

		spLevelIcon[1].setTexture(*ResourceManager::Instance()->GetTexture("Editeur bouton non sélectionné"));

		spLevelIcon[2].setTexture(*ResourceManager::Instance()->GetTexture("Editeur bouton sélectionné"));

		InfosText.setString("Longueur : Grande\nDurée estimée : 1 minute 30");
	}

	if (sf::Joystick::isButtonPressed(0, 0) && SelectionTimer.getElapsedTime().asMilliseconds() > 300)
	{
		Valider.setBuffer(*ResourceManager::Instance()->GetSoundBuffer("Valider"));
		Valider.setVolume(GameManager::Instance()->VolumeFX);
		Valider.play();
		if (LevelSelected == 1)
		{
			GameManager::Instance()->m_ActualScene = new LevelEditor(600, 17, "", false);
		}
		else if (LevelSelected == 2)
		{
			GameManager::Instance()->m_ActualScene = new LevelEditor(900, 17, "", false);
		}
		else if (LevelSelected == 3)
		{
			GameManager::Instance()->m_ActualScene = new LevelEditor(1200, 17, "", false);
		}
	}
	else if (sf::Joystick::isButtonPressed(0, 1) && SelectionTimer.getElapsedTime().asMilliseconds() > 300)
	{
		retour.setBuffer(*ResourceManager::Instance()->GetSoundBuffer("Retour"));
		retour.setVolume(GameManager::Instance()->VolumeFX);
		retour.play();
		GameManager::Instance()->LoadScene(e_Enum::e_Scene::CHOOSELEVELEDITOR);
	}
}

void SizeEditor::Display()
{
	m_actualWindow->draw(spBackground);
	m_actualWindow->draw(spButton);
	m_actualWindow->draw(spFlèche);

	m_actualWindow->draw(EnterSizeText);
	m_actualWindow->draw(spInfosRect);
	m_actualWindow->draw(InfosText);

	for (int i = 0; i < 3; i++)
	{
		m_actualWindow->draw(spLevelIcon[i]);
		m_actualWindow->draw(LevelNumero[i]);
	}

	m_actualWindow->draw(spBoutonRetour);
}

void SizeEditor::EventManager(sf::Event p_pollingEvent)
{
}