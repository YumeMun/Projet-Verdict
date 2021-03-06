#pragma once
#include "Scene.h"
#define SPEED_PODIUM 4
#define FACTOR_DIVIDE 3

class Level_Finished :
	public Scene
{
public:
	Level_Finished();
	Level_Finished(int _J1Score, int _J2Score, class Player* _player1, class Player* _player2, int _skinJ1, int _skinJ2, std::string _LevelName);
	~Level_Finished();
	virtual void Update();
	virtual void Display();
	virtual void EventManager(sf::Event p_pollingEvent);

	void GetScoreValue(class Player* _player1, class Player* _player2);
	void UpdatePodium();

private:
	sf::Sprite spBackground;
	sf::Sprite spContour;
	sf::Sprite spLight;
	sf::Sprite spFl�che;

	sf::Sprite spButton[3];
	sf::Text ButtonText[3];
	sf::Sound sound;
	sf::Sound Valider;
	sf::Sound Foule;
	sf::Sound Victoire;
	sf::Sound FouleDebut;
	sf::Sound ScoreEnMoins;
	sf::Sound ScoreEnPlus;
	int Selection = 1;
	sf::Clock m_Clock;

	int J1Score;
	int J2Score;

	sf::Text WinText;
	sf::Text ScoreText[2];
	sf::Text isPlayerText[2];

	sf::Sprite spPlayer[2];
	sf::IntRect rectPlayer[2];
	sf::Sprite spPodium[2];
	sf::Vector2f posElement[2];
	sf::Vector2f originElement;

	sf::Sprite spLogo;
	sf::IntRect rectLogo;
	sf::Vector2f posLogo[3];

	float scoreTimeFirst[2];
	float scoreIsArrivedFirst[2];
	float scoreFall[2];
	float scoreHitTrap[2];
	int scoreFinal[2];
	int scoreFinalDivide[2];

	bool isScoreStep[4];
	bool isUpdatable = false;
	bool isScoreEnd = false;
	sf::Clock countdownStart;
	sf::Clock timerPause;
	sf::Clock timerLogo;
	int frameIndex = 0;
	//std::vector<float>

	class Transition* transition;

	sf::Clock AnimLogo;
	int FrameIndexLogo = 0;

	std::string LevelName;
	int SkinJ1;
	int SkinJ2;
};