#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Singleton.h"
#include "Enum.h"
#include "Chargement.h"
#include "Menu.h"
#include "Jeu.h"
#include "SizeEditor.h"
#include "LevelEditor.h"
#include "SaveEditor.h"
#include "LevelSelector.h"
#include "PlayerSelector.h"
#include "ChooseLevelEditor.h"
#include "OpenLevelEditor.h"
#include "Level_Finished.h"

class GameManager : public Singleton<GameManager>
{
	friend class Singleton<GameManager>;

private:
	GameManager();

	sf::RenderWindow m_Window;
	sf::Event m_Event;

	e_Enum::e_Scene* m_SceneName;

public:
	void Start();
	void Update();
	void Display();
	void LoadScene(e_Enum::e_Scene sceneEnum);

	Scene* m_ActualScene;

	sf::RenderWindow* GetWindow();
};