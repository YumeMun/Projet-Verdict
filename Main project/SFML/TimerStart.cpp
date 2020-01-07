#include "TimerStart.h"
#include "ResourceManager.h"

TimerStart::TimerStart()
{
	std::cout << "timer start constructor" << std::endl;
	Setup();
}

TimerStart::~TimerStart()
{
}

void TimerStart::Setup()
{
	m_actualWindow = GameManager::Instance()->GetWindow();

	for (int i = 0; i < 4; i++)
	{
		posPointX[i] = 1;
		posPointY[i] = 1;
	}

	SetupRect(); //setup rect haut droit
}

void TimerStart::SetupRect()
{
	for (int i = 0; i < 4; i++)
	{
		shape[i].setPointCount(4);
		shape[i].setPoint(0, { (1920 / 2), (1080 / 2) });
		shape[i].setFillColor(sf::Color(122, 122, 122, 122));
	}

	shape[0].setPoint(1, { (1920 / 2), 0 }); //point qui bouge en x puis en y
	shape[0].setPoint(2, { (1920 / 2), 0 }); //point qui bouge en x
	shape[0].setPoint(3, { (1920 / 2), 0 });

	shape[1].setPoint(1, { 1920, (1080 / 2) });
	shape[1].setPoint(2, { 1920, (1080 / 2) });
	shape[1].setPoint(3, { 1920, (1080 / 2) });

	shape[2].setPoint(1, { (1920 / 2), 1080 });
	shape[2].setPoint(2, { (1920 / 2), 1080 });
	shape[2].setPoint(3, { (1920 / 2), 1080 });

	shape[3].setPoint(1, { 0, (1080 / 2) });
	shape[3].setPoint(2, { 0, (1080 / 2) });
	shape[3].setPoint(3, { 0, (1080 / 2) });

	/*_shape.setPointCount(4);
	_shape.setPoint(0, _posPoint0);
	_shape.setPoint(1, _posPoint1); //point qui bouge en x puis en y
	_shape.setPoint(2, _posPoint2); //point qui bouge en x
	_shape.setPoint(3, _posPoint3);
	_shape.setFillColor(sf::Color::Green);*/

	SetupText();
}

void TimerStart::SetupText()
{
	textCountdown.setFont(*ResourceManager::Instance()->GetFont("arial"));
	textCountdown.setCharacterSize(400);
	textCountdown.setString(std::to_string(numberCount));
	textCountdown.setFillColor(sf::Color::Black);
	textCountdown.setPosition(sf::Vector2f((1920 / 2) - (textCountdown.getGlobalBounds().width / 2), (1080 / 2) - (textCountdown.getGlobalBounds().height / 2)));
}

void TimerStart::UpdateRect()
{
	textCountdown.setString(std::to_string(numberCount));

	if (!rect0IsDone) //remplis le rect haut droit
	{
		if (posPointX[0] < 1920 / 2)
			posPointX[0] += RECT_SPEED_X;
		else
		{
			if (posPointY[0] < 1080 / 2)
				posPointY[0] += RECT_SPEED_Y;
			else
			{
				posPointY[0] = 1080 / 2;
				rect0IsDone = true;
			}
		}
		shape[0].setPoint(2, { (1920 / 2) + posPointX[0], 0 });
		shape[0].setPoint(1, { (1920 / 2) + posPointX[0], 0 + posPointY[0] });
	}

	if (!rect1IsDone && rect0IsDone) //remplis le rect bas droit
	{
		if (posPointY[1] < 1080)
			posPointY[1] += RECT_SPEED_Y;
		else
		{
			if (posPointX[1] < 1920 / 2)
				posPointX[1] += RECT_SPEED_X;
			else
				rect1IsDone = true;
		}
		shape[1].setPoint(2, { 1920, (1080 / 2) + posPointY[1] });
		shape[1].setPoint(1, { 1920 - posPointX[1], (1080 / 2) + posPointY[1] });
	}

	if (!rect2IsDone && rect1IsDone) //remplis le rect bas gauche
	{
		if (posPointX[2] < 1920 / 2)
			posPointX[2] += RECT_SPEED_X;
		else
		{
			if (posPointY[2] < 1080 / 2)
				posPointY[2] += RECT_SPEED_Y;
			else
			{
				posPointY[2] = 1080 / 2;
				rect2IsDone = true;
			}
		}
		shape[2].setPoint(2, { (1920 / 2) - posPointX[2], 1080 });
		shape[2].setPoint(1, { (1920 / 2) - posPointX[2], 1080 - posPointY[2] });
	}

	if (!rect3IsDone && rect2IsDone) //remplis le rect haut gauche
	{
		if (posPointY[3] < 1080)
			posPointY[3] += RECT_SPEED_Y;
		else
		{
			if (posPointX[3] < 1920 / 2)
				posPointX[3] += RECT_SPEED_X;
			else
				rect3IsDone = true;
		}
		shape[3].setPoint(2, { 0, (1080 / 2) - posPointY[3] });
		shape[3].setPoint(1, { 0 + posPointX[3], (1080 / 2) - posPointY[3] });
	}

	if (rect3IsDone)
	{
		numberCount--;
		ResetPosPoint();
		rect3IsDone = false;
		rect2IsDone = false;
		rect1IsDone = false;
		rect0IsDone = false;
	}

	if (numberCount < 1)
	{
		std::cout << "timer end lancement partie" << std::endl;
		isTimerEnd = true;
		numberCount = 3;
	}
	if (numberCount <= 3)
	{
		TimerSound();
	}
}

void TimerStart::DrawRect()
{
	for (int i = 0; i < 4; i++)
	{
		m_actualWindow->draw(shape[i]);
	}

	m_actualWindow->draw(textCountdown);
}

void TimerStart::ResetPosPoint()
{
	shape[0].setPoint(1, { (1920 / 2), 0 });
	shape[0].setPoint(2, { (1920 / 2), 0 });

	shape[1].setPoint(1, { 1920, (1080 / 2) });
	shape[1].setPoint(2, { 1920, (1080 / 2) });

	shape[2].setPoint(1, { (1920 / 2), 1080 });
	shape[2].setPoint(2, { (1920 / 2), 1080 });

	shape[3].setPoint(1, { 0, (1080 / 2) });
	shape[3].setPoint(2, { 0, (1080 / 2) });

	for (int i = 0; i < 4; i++)
	{
		posPointX[i] = 0;
		posPointY[i] = 0;
	}
}

int TimerStart::GetNumberCount()
{
	return numberCount;
}

bool TimerStart::GetIsTimerEnd()
{
	return isTimerEnd;
}

void TimerStart::ResetNumberCount()
{
	numberCount = 3;
}

void TimerStart::TimerSound()
{
	if (i >= numberCount)
	{
		Countdown.setBuffer(*ResourceManager::Instance()->GetSoundBuffer("Countdown"));
		Countdown.play();
		i--;
	}
	if (m_Clock.getElapsedTime().asSeconds() >= 1.7)
	{
		if (i == 0)
		{
			Countdown.stop();
			Depart.setBuffer(*ResourceManager::Instance()->GetSoundBuffer("Depart Course"));
			Depart.play();
		}
		m_Clock.restart();
	}
}
