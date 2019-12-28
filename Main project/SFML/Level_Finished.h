#pragma once
#include "Scene.h"

class Level_Finished :
	public Scene
{
public:
	Level_Finished();
	Level_Finished(int _J1Score, int _J2Score);
	~Level_Finished();
	virtual void Update();
	virtual void Display();
	virtual void EventManager(sf::Event p_pollingEvent);

private:
	int J1Score;
	int J2Score;

	sf::Text WinText;
	sf::Text ScoreText[2];

	class Transition* transition;
};