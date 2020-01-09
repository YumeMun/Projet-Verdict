#include "GameManager.h"

GameManager::GameManager()
{
}

//Création de la fenêtre et chargement de scène
void GameManager::Start()
{
	if (!music.openFromFile("Ressources/Music/Cruise_Around.ogg"))
	music.setVolume(GameManager::Instance()->VolumeMusique);
	music.play();
	music.setLoop(true);
	m_Window.create(sf::VideoMode(1920, 1080), "Projet Runner", sf::Style::Fullscreen);
	LoadScene(e_Enum::INTRO);
}

//Boucle de jeu
void GameManager::Update()
{
	music.setVolume(GameManager::Instance()->VolumeMusique);
	while (m_Window.pollEvent(m_Event))
	{
		//Fermeture du programme
		if (m_Event.type == sf::Event::Closed ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			m_Window.close();
		}
		else
		{
			//Appel de l'event manager de chaque scène
			m_ActualScene->EventManager(m_Event);
		}
	}

	//Appel de l'update de chaque scène
	m_ActualScene->Update();
}

void GameManager::Display()
{
	//Affichage de chaque scène et display
	m_Window.setMouseCursorVisible(false);
	m_Window.setVerticalSyncEnabled(true);
	m_Window.clear();
	m_ActualScene->Display();
	m_Window.display();
}

//Chargement de scene
void GameManager::LoadScene(e_Enum::e_Scene sceneEnum)
{
	switch (sceneEnum)
	{
	case e_Enum::e_Scene::INTRO:
		m_ActualScene = new Intro();
		break;
	case e_Enum::e_Scene::CHARGEMENT:
		m_ActualScene = new Chargement();
		break;
	case e_Enum::e_Scene::MENU:
		if (music.getStatus() == 1 || music.getStatus() == 0)
		{
			music.play();
		}
		m_ActualScene = new Menu();
		break;
	case e_Enum::e_Scene::COMMANDES:
		m_ActualScene = new Commandes();
		break;
	case e_Enum::e_Scene::OPTIONS:
		m_ActualScene = new Options();
		break;
	case e_Enum::e_Scene::CREDITS:
		music.pause();
		m_ActualScene = new Credits();
		break;
	case e_Enum::e_Scene::JEU:
		//music.stop();
		m_ActualScene = new Jeu();
		break;
	case e_Enum::e_Scene::CHOOSELEVELEDITOR:
		if (music.getStatus() == 1 || music.getStatus() == 0)
		{
			music.play();
		}
		m_ActualScene = new ChooseLevelEditor();
		break;
	case e_Enum::e_Scene::OPENLEVELEDITOR:
		m_ActualScene = new OpenLevelEditor();
		break;
	case e_Enum::e_Scene::SIZEEDITOR:
		m_ActualScene = new SizeEditor();
		break;
	case e_Enum::e_Scene::LEVELEDITOR:
		music.stop();
		m_ActualScene = new LevelEditor();
		break;
	case e_Enum::e_Scene::SAVEEDITOR:
		m_ActualScene = new SaveEditor();
		break;
	case e_Enum::e_Scene::LEVELSELECTOR:
		if (music.getStatus() == 1 || music.getStatus() == 0)
		{
			music.play();
		}
		m_ActualScene = new LevelSelector();
		break;
	case e_Enum::e_Scene::PLAYERSELECTOR:
		m_ActualScene = new PlayerSelector();
		break;
	case e_Enum::e_Scene::LEVELFINISHED:
		m_ActualScene = new Level_Finished();
		break;
	default:
		break;
	}
	m_SceneName = &sceneEnum;
}

sf::RenderWindow* GameManager::GetWindow()
{
	return &m_Window;
}