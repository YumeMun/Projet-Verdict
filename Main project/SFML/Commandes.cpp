#include "Commandes.h"
#include "GameManager.h"
#include "ResourceManager.h"

Commandes::Commandes()
{
	std::cout << "Commandes constructor" << std::endl;

	m_actualWindow = GameManager::Instance()->GetWindow();

	spBackground.setTexture(*ResourceManager::Instance()->GetTexture("Background interface"));
	spBackground.setColor(sf::Color{ 100, 100, 100, 255 });
	spCommandes.setTexture(*ResourceManager::Instance()->GetTexture("Commandes jeu"));
	spCommandes.setOrigin(spCommandes.getGlobalBounds().width / 2, spCommandes.getGlobalBounds().height / 2);

	spTouches[0].setTexture(*ResourceManager::Instance()->GetTexture("LB"));
	spTouches[0].setPosition(520, 250);
	spTouches[1].setTexture(*ResourceManager::Instance()->GetTexture("RB"));
	spTouches[1].setPosition(1220, 250);

	ControlsText.setFont(*ResourceManager::Instance()->GetFont("Font"));
	ControlsText.setCharacterSize(45);
	ControlsText.setFillColor(sf::Color::White);
}

Commandes::~Commandes()
{
}

void Commandes::Update()
{
	if (sf::Joystick::isButtonPressed(0, 1))
	{
		Retour.setBuffer(*ResourceManager::Instance()->GetSoundBuffer("Retour"));
		Retour.setVolume(GameManager::Instance()->VolumeFX);
		Retour.play();
		GameManager::Instance()->LoadScene(e_Enum::e_Scene::MENU);
	}

	if (sf::Joystick::isButtonPressed(0, 4) && KeyPress == false)
	{
		if (Selection == 1)
			Selection = 2;
		else if(Selection == 2)
			Selection = 1;

		spTouches[0].setTexture(*ResourceManager::Instance()->GetTexture("LB Press"));
		KeyPress = true;
	}
	else if (sf::Joystick::isButtonPressed(0, 5) && KeyPress == false)
	{
		if (Selection == 1)
			Selection = 2;
		else if (Selection == 2)
			Selection = 1;

		spTouches[1].setTexture(*ResourceManager::Instance()->GetTexture("RB Press"));
		KeyPress = true;
	}
	else if (!sf::Joystick::isButtonPressed(0, 4) && !sf::Joystick::isButtonPressed(0, 5))
	{
		spTouches[0].setTexture(*ResourceManager::Instance()->GetTexture("LB"));
		spTouches[1].setTexture(*ResourceManager::Instance()->GetTexture("RB"));
		KeyPress = false;
	}

	if (Selection == 1)
	{
		ControlsText.setString("Commandes en jeu : ");
		ControlsText.setOrigin(ControlsText.getGlobalBounds().width / 2, ControlsText.getGlobalBounds().height / 2);
		ControlsText.setPosition(960, 150);

		spCommandes.setTexture(*ResourceManager::Instance()->GetTexture("Commandes jeu"));
		spCommandes.setPosition(930, 600);
	}
	else if (Selection == 2)
	{
		ControlsText.setString("Commandes dans l'éditeur : ");
		ControlsText.setOrigin(ControlsText.getGlobalBounds().width / 2, ControlsText.getGlobalBounds().height / 2);
		ControlsText.setPosition(960, 150);
		spCommandes.setTexture(*ResourceManager::Instance()->GetTexture("Commandes éditeur"));
		spCommandes.setPosition(930, 600);
	}
}

void Commandes::Display()
{
	m_actualWindow->draw(spBackground);
	m_actualWindow->draw(spCommandes);

	m_actualWindow->draw(ControlsText);

	m_actualWindow->draw(spTouches[0]);
	m_actualWindow->draw(spTouches[1]);

	m_actualWindow->draw(spBoutonRetour);
}

void Commandes::EventManager(sf::Event p_pollingEvent)
{
}