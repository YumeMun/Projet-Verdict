#include "Transition.h"

Transition::Transition()
{
	Setup();
}

Transition::Transition(sf::Vector2f _posShape1, sf::Vector2f _posShape2)
{
	SetupBack(_posShape1, _posShape2);
}

Transition::~Transition()
{
}

void Transition::Setup()
{
	m_actualWindow = GameManager::Instance()->GetWindow();

	for (int i = 0; i < 2; i++)
	{
		shape[i].setPointCount(4);
		shape[i].setFillColor(sf::Color(122, 122, 122, 255));
	}

	shape[0].setPoint(0, { 0, 0 });
	shape[0].setPoint(1, {1920, 0});
	shape[0].setPoint(2, { 1920, 1080 / 2 }); // y a determiner
	shape[0].setPoint(3, {0, 1080/2}); // y a determiner
	posShape[0] = { 0, 0 - shape[0].getGlobalBounds().height };
	shape[0].setPosition(posShape[0]);

	shape[1].setPoint(0, { 0, 0 });
	shape[1].setPoint(1, { 1920, 0 });
	shape[1].setPoint(2, { 1920, 1080 / 2 }); // y a determiner
	shape[1].setPoint(3, { 0, 1080 / 2 }); // y a determiner
	posShape[1] = { 0, 1080};
	shape[1].setPosition(posShape[1]);

	/*shape[1].setPoint(0, {0, 1080/2});
	shape[1].setPoint(1, { 1920, 1080/2 });
	shape[1].setPoint(2, { 1920, 1080 }); //
	shape[1].setPoint(3, { 0, 1080 }); //
	posShape[1] = { 0, 1080 + shape[1].getGlobalBounds().height};
	shape[1].setPosition(posShape[1]);*/
}

void Transition::SetupBack(sf::Vector2f _posShape1, sf::Vector2f _posShape2)
{
	m_actualWindow = GameManager::Instance()->GetWindow();

	for (int i = 0; i < 2; i++)
	{
		shape[i].setPointCount(4);
		shape[i].setFillColor(sf::Color(122, 122, 122, 255));
	}

	shape[0].setPoint(0, { 0, 0 });
	shape[0].setPoint(1, { 1920, 0 });
	shape[0].setPoint(2, { 1920, 1080 / 2 }); // y a determiner
	shape[0].setPoint(3, { 0, 1080 / 2 }); // y a determiner
	posShape[0] = _posShape1;
	shape[0].setPosition(posShape[0]);

	/*shape[1].setPoint(0, { 0, 1080 });
	shape[1].setPoint(1, { 1920, 1080 });
	shape[1].setPoint(3, { 0, 1080 / 2 }); //
	shape[1].setPoint(2, { 1920, 1080 / 2 }); //*/

	shape[1].setPoint(0, { 0, 0 });
	shape[1].setPoint(1, { 1920, 0 });
	shape[1].setPoint(2, { 1920, 1080 / 2 }); // y a determiner
	shape[1].setPoint(3, { 0, 1080 / 2 }); // y a determiner
	posShape[1] = _posShape2;
	shape[1].setPosition(posShape[1]);
}

void Transition::Update()
{
	posShape[0].y += TRANSITION_SPEED;
	posShape[1].y -= TRANSITION_SPEED;
	shape[0].setPosition(posShape[0]);
	shape[1].setPosition(posShape[1]);

	if (posShape[0].y >= 0 || posShape[1].y <= 1080/2)
	{
		posShape[0].y = 0;
		posShape[1].y = 1080/2;
		shape[0].setPosition(posShape[0]);
		shape[1].setPosition(posShape[1]);

		isTransitionDone = true;
	}
}

void Transition::UpdateBack()
{
	posShape[0].y -= TRANSITION_SPEED;
	posShape[1].y += TRANSITION_SPEED;
	shape[0].setPosition(posShape[0]);
	shape[1].setPosition(posShape[1]);

	if (posShape[0].y <= 0 - shape[0].getGlobalBounds().height || posShape[1].y >= 1080/* + shape[1].getGlobalBounds().height*/)
	{
		posShape[0].y = 0 - shape[0].getGlobalBounds().height;
		posShape[1].y = 1080 /*+ shape[1].getGlobalBounds().height*/;
		shape[0].setPosition(posShape[0]);
		shape[1].setPosition(posShape[1]);

		isTransitionBackDone = true;
	}
}

void Transition::ResetTransition()
{
	isTransitionDone = false;
	isTransitionBackDone = false;
}

void Transition::DrawTransition()
{
	m_actualWindow->draw(shape[0]);
	m_actualWindow->draw(shape[1]);
}

bool Transition::GetIsTransitionDone()
{
	return isTransitionDone;
}

bool Transition::GetIsTransitionBackDone()
{
	return isTransitionBackDone;
}