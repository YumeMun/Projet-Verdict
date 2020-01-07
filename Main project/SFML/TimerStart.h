#pragma once
#include "GameManager.h"
#include "Scene.h"

#define RECT_SPEED_X 120*(16/9)
#define RECT_SPEED_Y 120

class TimerStart
{
public :
	TimerStart();
	~TimerStart();
	void Setup();
	void SetupRect();
	void SetupText();

	void UpdateRect();
	void DrawRect();

	int GetNumberCount();
	bool GetIsTimerEnd();

	void ResetPosPoint();
	void ResetNumberCount();

	void TimerSound();

private:
	sf::ConvexShape shape[4];
	float posPointX[4]; //facteur load en x
	float posPointY[4]; //facteur load en y apres x

	bool rect0IsDone = false;
	bool rect1IsDone = false;
	bool rect2IsDone = false;
	bool rect3IsDone = false;
	sf::Sound Countdown;
	sf::Sound Depart;
	sf::Clock m_Clock;
	int numberCount = 3;
	bool isTimerEnd = false;
	sf::Text textCountdown;
	int i = 3;
	sf::RenderWindow* m_actualWindow;
};

