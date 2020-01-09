#include "Credits.h"
#include "GameManager.h"
#include "ResourceManager.h"

Credits::Credits()
{
	m_actualWindow = GameManager::Instance()->GetWindow();

	spBackground.setTexture(*ResourceManager::Instance()->GetTexture("Background credits"));

	if (!music.openFromFile("Ressources/Music/Cool_Catz.ogg"))
		std::cout << "Impossible de charger la musique" << std::endl;

	music.play();
	music.setVolume(GameManager::Instance()->VolumeMusique);
	music.setLoop(true);
}

Credits::~Credits()
{
}

void Credits::Update()
{
	if (sf::Joystick::isButtonPressed(0, 1))
	{
		Retour.setBuffer(*ResourceManager::Instance()->GetSoundBuffer("Retour"));
		Retour.setVolume(GameManager::Instance()->VolumeFX);
		Retour.play();
		music.stop();
		GameManager::Instance()->LoadScene(e_Enum::e_Scene::MENU);
	}
}

void Credits::Display()
{
	if (spBackground.getPosition().y > -3376)
		spBackground.move(0, -3);

	m_actualWindow->draw(spBackground);

	if (spBackground.getPosition().y <= -3376)
		m_actualWindow->draw(spBoutonRetour);
}

void Credits::EventManager(sf::Event p_pollingEvent)
{
}
