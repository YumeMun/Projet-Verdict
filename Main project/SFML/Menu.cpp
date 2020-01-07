#include "Menu.h"
#include "GameManager.h"
#include "ResourceManager.h"

Menu::Menu()
{
	std::cout << "Menu constructor" << std::endl;

	m_actualWindow = GameManager::Instance()->GetWindow();

	m_NewGame.setFont(*ResourceManager::Instance()->GetFont("Font"));
	m_NewGame.setCharacterSize(50);
	m_NewGame.setFillColor(sf::Color::White);
	m_NewGame.setString("Jouer");
	m_NewGame.setPosition(45, 345);

	m_LevelEditor.setFont(*ResourceManager::Instance()->GetFont("Font"));
	m_LevelEditor.setCharacterSize(50);
	m_LevelEditor.setFillColor(sf::Color::White);
	m_LevelEditor.setString("Éditeur de niveau");
	m_LevelEditor.setPosition(45, 445);

	m_Option.setFont(*ResourceManager::Instance()->GetFont("Font"));
	m_Option.setCharacterSize(50);
	m_Option.setFillColor(sf::Color::White);
	m_Option.setString("Contrôles");
	m_Option.setPosition(45, 545);

	m_Commande.setFont(*ResourceManager::Instance()->GetFont("Font"));
	m_Commande.setCharacterSize(50);
	m_Commande.setFillColor(sf::Color::White);
	m_Commande.setString("Options");
	m_Commande.setPosition(45, 645);

	m_Quit.setFont(*ResourceManager::Instance()->GetFont("Font"));
	m_Quit.setCharacterSize(50);
	m_Quit.setFillColor(sf::Color::White);
	m_Quit.setString("Quitter");
	m_Quit.setPosition(45, 745);

	m_Credits.setFont(*ResourceManager::Instance()->GetFont("Font"));
	m_Credits.setCharacterSize(50);
	m_Credits.setFillColor(sf::Color::White);
	m_Credits.setString("Crédits");
	m_Credits.setPosition(1598, 895);

	spBackground.setTexture(*ResourceManager::Instance()->GetTexture("Background Menu"));
	spPoster.setTexture(*ResourceManager::Instance()->GetTexture("Poster Menu"));
	spPoster.setPosition(862, 113);
	spBordurePanneau.setTexture(*ResourceManager::Instance()->GetTexture("Bordure Panneau Menu"));
	spBordurePanneau.setPosition(815, 40);
	spLumières.setTexture(*ResourceManager::Instance()->GetTexture("Lumières Menu"));
	spLumières.setPosition(807, 48);
	spRampe.setTexture(*ResourceManager::Instance()->GetTexture("Rampe Menu"));
	spRampe.setPosition(0, 520);
	spTram.setTexture(*ResourceManager::Instance()->GetTexture("Tram Menu"));
	spTram.setPosition(-5000, 522);
	spBras.setTexture(*ResourceManager::Instance()->GetTexture("Bras Menu"));
	spBras.setPosition(1283, 800);
	spBras.setOrigin(50, spBras.getGlobalBounds().height - 50);
	spPanneau.setTexture(*ResourceManager::Instance()->GetTexture("Panneau Menu"));
	spPanneau.setPosition(423, 243);

	spFlèche.setTexture(*ResourceManager::Instance()->GetTexture("Flèche menu"));
	spCreditsButton.setTexture(*ResourceManager::Instance()->GetTexture("Petit bouton non sélectionné"));
	spCreditsButton.setPosition(1593, 900);

	for (int i = 0; i < 5; i++)
	{
		spButton[i].setTexture(*ResourceManager::Instance()->GetTexture("Menu bouton non sélectionné"));
		spButton[i].setPosition(40, 350 + i * 100);
	}

	rectLogo = { 0, 0, 872, 396 };
	spLogo.setTextureRect(rectLogo);
	spLogo.setTexture(*ResourceManager::Instance()->GetTexture("Logo"));
	spLogo.setPosition(sf::Vector2f(1470, 150));
	spLogo.setScale(sf::Vector2f(0.5, 0.5));

	timerAnimLogo.restart();
}

Menu::~Menu()
{
}

void Menu::Update()
{
	spTram.move(50, 0);

	if(spTram.getPosition().x >= 20000)
		spTram.setPosition(-1000, 522);

	if (AnimPanneau.getElapsedTime().asSeconds() > 0 && AnimPanneau.getElapsedTime().asSeconds() < 1.5)
	{
		spPanneau.move(0, 0.3);
	}
	else if (AnimPanneau.getElapsedTime().asSeconds() > 1.5 && AnimPanneau.getElapsedTime().asSeconds() < 3)
	{
		spPanneau.move(0, -0.3);
	}
	else if (AnimPanneau.getElapsedTime().asSeconds() > 3)
		AnimPanneau.restart();


	if (AnimBras.getElapsedTime().asSeconds() > 0 && AnimBras.getElapsedTime().asSeconds() < 1.5)
	{
		if (RotationBras < 12)
			RotationBras += 0.1;
	}
	else if (AnimBras.getElapsedTime().asSeconds() > 1.5)
	{
		if (RotationBras > 0)
			RotationBras -= 0.1;
		else
			AnimBras.restart();
	}


	spBras.setRotation(RotationBras);

	for (int i = 0; i < 5; i++)
	{
		if (i == m_MenuChoice - 1)
		{
			spButton[i].setTexture(*ResourceManager::Instance()->GetTexture("Menu bouton sélectionné"));
			spFlèche.setPosition(spButton[i].getPosition().x + 10, spButton[i].getPosition().y + 7);
		}
		else if (m_MenuChoice == 6)
		{
			spFlèche.setPosition(spCreditsButton.getPosition().x + 10, spCreditsButton.getPosition().y + 7);
			spCreditsButton.setTexture(*ResourceManager::Instance()->GetTexture("Petit bouton sélectionné"));
		}
		else
		{
			spButton[i].setTexture(*ResourceManager::Instance()->GetTexture("Menu bouton non sélectionné"));
			spCreditsButton.setTexture(*ResourceManager::Instance()->GetTexture("Petit bouton non sélectionné"));
		}
	}

	if (m_MenuChoice == 1)
	{
		m_NewGame.setPosition(120, 345);
		m_LevelEditor.setPosition(45, 445);
		m_Option.setPosition(45, 545);
		m_Commande.setPosition(45, 645);
		m_Quit.setPosition(45, 745);
		m_Credits.setPosition(1598, 895);
	}
	else if (m_MenuChoice == 2)
	{
		m_NewGame.setPosition(45, 345);
		m_LevelEditor.setPosition(120, 445);
		m_Option.setPosition(45, 545);
		m_Commande.setPosition(45, 645);
		m_Quit.setPosition(45, 745);
		m_Credits.setPosition(1598, 895);
	}
	else if (m_MenuChoice == 3)
	{
		m_NewGame.setPosition(45, 345);
		m_LevelEditor.setPosition(45, 445);
		m_Option.setPosition(120, 545);
		m_Commande.setPosition(45, 645);
		m_Quit.setPosition(45, 745);
		m_Credits.setPosition(1598, 895);
	}
	else if (m_MenuChoice == 4)
	{
		m_NewGame.setPosition(45, 345);
		m_LevelEditor.setPosition(45, 445);
		m_Option.setPosition(45, 545);
		m_Commande.setPosition(120, 645);
		m_Quit.setPosition(45, 745);
		m_Credits.setPosition(1598, 895);
	}
	else if (m_MenuChoice == 5)
	{
		m_NewGame.setPosition(45, 345);
		m_LevelEditor.setPosition(45, 445);
		m_Option.setPosition(45, 545);
		m_Commande.setPosition(45, 645);
		m_Quit.setPosition(120, 745);
		m_Credits.setPosition(1598, 895);
	}
	else if (m_MenuChoice == 6)
	{
		m_NewGame.setPosition(45, 345);
		m_LevelEditor.setPosition(45, 445);
		m_Option.setPosition(45, 545);
		m_Commande.setPosition(45, 645);
		m_Quit.setPosition(45, 745);
		m_Credits.setPosition(1673, 895);
	}

	if (!isRestart)
	{
		if (timerAnimLogo.getElapsedTime().asSeconds() >= 0.04)
		{
			rectLogo.left += 872;
			spLogo.setTextureRect(rectLogo);
			animCount++;
			timerAnimLogo.restart();
		}

		if (animCount == 16)
		{
			rectLogo.left = 0;
			rectLogo.top = 396;
			spLogo.setTextureRect(rectLogo);
			isRestart = true;
			timerLogoRestart.restart();
		}
	}
	else
	{
		if (timerLogoRestart.getElapsedTime().asSeconds() <= 15)
		{
			rectLogo.left = 0;
			rectLogo.top = 396;
			spLogo.setTextureRect(rectLogo);
		}
		else
		{
			animCount = 0;
			isRestart = false;

			rectLogo.left = 0;
			rectLogo.top = 0;
			spLogo.setTextureRect(rectLogo);
		}
	}
}

void Menu::Display()
{
	m_actualWindow->draw(spBackground);
	m_actualWindow->draw(spPoster);
	m_actualWindow->draw(spLogo);
	m_actualWindow->draw(spBras);
	m_actualWindow->draw(spBordurePanneau);
	m_actualWindow->draw(spPanneau);

	if (AnimLights.getElapsedTime().asSeconds() > 1 && AnimLights.getElapsedTime().asSeconds() < 1.5)
	{
		m_actualWindow->draw(spLumières);
	}
	else if (AnimLights.getElapsedTime().asSeconds() > 1.5)
		AnimLights.restart();

	m_actualWindow->draw(spRampe);
	m_actualWindow->draw(spTram);

	for (int i = 0; i < 5; i++)
	{
		m_actualWindow->draw(spButton[i]);
	}
	m_actualWindow->draw(spCreditsButton);
	m_actualWindow->draw(spFlèche);

	m_actualWindow->draw(m_NewGame);
	m_actualWindow->draw(m_LevelEditor);
	m_actualWindow->draw(m_Option);
	m_actualWindow->draw(m_Quit);
	m_actualWindow->draw(m_Commande);
	m_actualWindow->draw(m_Credits);
}

void Menu::EventManager(sf::Event p_pollingEvent)
{
	if (m_Clock.getElapsedTime().asSeconds() >= 0.3)
	{
		if (sf::Joystick::isButtonPressed(0, 0))
		{
			if (m_MenuChoice == 1)
				GameManager::Instance()->LoadScene(e_Enum::e_Scene::LEVELSELECTOR);
			else if (m_MenuChoice == 2)
				GameManager::Instance()->LoadScene(e_Enum::e_Scene::CHOOSELEVELEDITOR);
			else if (m_MenuChoice == 3)
				GameManager::Instance()->LoadScene(e_Enum::e_Scene::COMMANDES);
			else if (m_MenuChoice == 4)
				GameManager::Instance()->LoadScene(e_Enum::e_Scene::OPTIONS);
			else if (m_MenuChoice == 5)
				m_actualWindow->close();
			else if (m_MenuChoice == 6)
				GameManager::Instance()->LoadScene(e_Enum::e_Scene::CREDITS);
		}


		if (sf::Joystick::getAxisPosition(0, sf::Joystick::Y) < -50.f)
		{
			sound.setBuffer(*ResourceManager::Instance()->GetSoundBuffer("Curseur menu"));
			sound.play();
			if (m_MenuChoice != 1)
				m_MenuChoice = m_MenuChoice - 1;
			else
				m_MenuChoice = 6;
			m_Clock.restart();
		}
		if (sf::Joystick::getAxisPosition(0, sf::Joystick::Y) > 50.f)
		{
			sound.setBuffer(*ResourceManager::Instance()->GetSoundBuffer("Curseur menu"));
			sound.play();
			if (m_MenuChoice != 6)
				m_MenuChoice = m_MenuChoice + 1;
			else
				m_MenuChoice = 1;
			m_Clock.restart();
		}
	}
}