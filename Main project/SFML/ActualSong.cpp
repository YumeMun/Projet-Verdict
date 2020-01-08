#include "ActualSong.h"
#include "ResourceManager.h"

ActualSong::ActualSong()
{
	Setup();
}

ActualSong::~ActualSong()
{
}

void ActualSong::Setup()
{
	posCadre = {1920 - 250, 1080 - 100};
	spCadre.setTexture(*ResourceManager::Instance()->GetTexture("petit_bouton_retour"));
	spCadre.setPosition(posCadre);

	strActualSong[0] = "musique 0";
	strActualSong[1] = "musique 1";

	txtActualSong.setFont(*ResourceManager::Instance()->GetFont("Font"));
	txtActualSong.setCharacterSize(30);
	txtActualSong.setFillColor(sf::Color::White);
}

void ActualSong::SetActualSong()
{
	txtActualSong.setString(strActualSong[0]);
}

void ActualSong::Display()
{
	if (isCadreDrawable)
	{
		m_actualWindow->draw(spCadre);
		m_actualWindow->draw(txtActualSong);
	}
}
