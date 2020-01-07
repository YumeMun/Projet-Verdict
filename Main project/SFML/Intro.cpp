#include "Intro.h"

Intro::Intro()
{
	m_actualWindow = GameManager::Instance()->GetWindow();

	Setup();
}

Intro::~Intro()
{
}

void Intro::Setup()
{
	BackgroundTexture[0].loadFromFile("Ressources/Textures/Background_Intro1.png");
	BackgroundTexture[1].loadFromFile("Ressources/Textures/Background_Intro2.png");

	spBackground[0].setTexture(BackgroundTexture[0]);
	spBackground[1].setTexture(BackgroundTexture[1]);

	spBackground[1].setPosition(1920, 0);
}

void Intro::Update()
{
	if (spBackground[1].getPosition().x > -3000)
		spBackground[1].move(-40, 0);
	else
		GameManager::Instance()->LoadScene(e_Enum::e_Scene::CHARGEMENT);
}

void Intro::Display()
{
	m_actualWindow->clear(sf::Color{ 170, 64, 65, 255 });
	m_actualWindow->draw(spBackground[1]);
	m_actualWindow->draw(spBackground[0]);
}

void Intro::EventManager(sf::Event p_pollingEvent)
{
}