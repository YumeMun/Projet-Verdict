#include "Credits.h"
#include "GameManager.h"
#include "ResourceManager.h"

Credits::Credits()
{
	std::cout << "Credits constructor" << std::endl;

	m_actualWindow = GameManager::Instance()->GetWindow();

	spBackground.setTexture(*ResourceManager::Instance()->GetTexture("Background credits"));
}

Credits::~Credits()
{
}

void Credits::Update()
{
	if (sf::Joystick::isButtonPressed(0, 1))
	{
		Retour.setBuffer(*ResourceManager::Instance()->GetSoundBuffer("Retour"));
		Retour.play();
		GameManager::Instance()->LoadScene(e_Enum::e_Scene::MENU);
	}
}

void Credits::Display()
{
	if (spBackground.getPosition().y > -3219)
		spBackground.move(0, -3);

	m_actualWindow->draw(spBackground);

	if (spBackground.getPosition().y <= -3219)
		m_actualWindow->draw(spBoutonRetour);
}

void Credits::EventManager(sf::Event p_pollingEvent)
{
}
