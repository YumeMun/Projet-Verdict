#pragma once
#include "Scene.h"
#define SPEED_PODIUM 1
#define FACTOR_DIVIDE 2

class Level_Finished :
	public Scene
{
public:
	Level_Finished();
	Level_Finished(int _J1Score, int _J2Score, class Player* _player1, class Player* _player2, int _skinJ1, int _skinJ2);
	~Level_Finished();
	virtual void Update();
	virtual void Display();
	virtual void EventManager(sf::Event p_pollingEvent);

	void GetScoreValue(class Player* _player1, class Player* _player2);
	void UpdatePodium();

private:
	int J1Score;
	int J2Score;

	sf::Text WinText;
	sf::Text ScoreText[2];

	sf::Sprite spPlayer[2];
	sf::IntRect rectPlayer[2];
	sf::Sprite spPodium[2];
	sf::Vector2f posElement[2];
	sf::Vector2f originElement;

	float scoreTimeFirst[2];
	float scoreIsArrivedFirst[2];
	float scoreFall[2];
	float scoreHitTrap[2];
	float scoreFinal[2];

	bool isScoreStep[4];
	sf::Clock countdownStart;
	//std::vector<float>

	class Transition* transition;
};