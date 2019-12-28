#include "Collects.h"
#include "GameManager.h"


Collects::Collects()
{
	std::cout << "Collects constructor" << std::endl;
	m_actualWindow = GameManager::Instance()->GetWindow();
}

Collects::~Collects()
{
}

void Collects::SetupCollects()
{
	for (int i = 0; i < NB_COLLECTS; i++)
	{
		Collects* newCollects = new Collects();
		newCollects->CollectRect.setSize(sf::Vector2f(64, 64));
		newCollects->CollectRect.setFillColor(sf::Color::Green);
		listCollect.push_back(newCollects);
	}
	listCollect[0]->CollectRect.setPosition(sf::Vector2f(500, 400));
	listCollect[1]->CollectRect.setPosition(sf::Vector2f(1000, 800));

	listCollect[0]->type = "missile";
	//listCollect[1]->type = "l'autre";
	listCollect[1]->type = "missile";

	samplePlayer.setSize(sf::Vector2f(64, 64));
	samplePlayer.setFillColor(sf::Color::Cyan);
	posSamplePlayer = { 300, 300 };
	samplePlayer.setPosition(posSamplePlayer);
}

void Collects::Update(Missile* _missile)
{
	if (!isSetup)
	{
		SetupCollects();
		isSetup = true;
	}

	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		posSamplePlayer.x -= 3;
		samplePlayer.setPosition(posSamplePlayer);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		posSamplePlayer.x += 3;
		samplePlayer.setPosition(posSamplePlayer);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		posSamplePlayer.y -= 3;
		samplePlayer.setPosition(posSamplePlayer);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		posSamplePlayer.y += 3;
		samplePlayer.setPosition(posSamplePlayer);
	}*/

	GetPlayerIsCollideCollects();
	for (int i = 0; i < NB_COLLECTS; i++)
	{
		if (listCollect[i]->isCollidePlayer)
		{
			std::cout << "is collide player" << std::endl;

			if (listCollect[i]->type == "missile")
			{
				std::cout << "CREATE NEW MISSILE" << std::endl;
				//_missile->CreateMissile();

				//delete(listCollect[i]);
				listCollect[i]->CollectRect.setPosition(sf::Vector2f(-1000, -1000)); //subtitu au delete
			}
			else if (listCollect[i]->type == "l'autre")
			{

			}

			listCollect[i]->isCollidePlayer = false;
		}
	}
}

void Collects::Display()
{
	//m_actualWindow->draw(samplePlayer);

	for (int i = 0; i < NB_COLLECTS; i++)
	{
		if (listCollect[i] != NULL)
		{
			//m_actualWindow->draw(listCollect[i]->CollectRect);
		}
	}
}

bool Collects::GetPlayerIsCollideCollects()
{
	for (int i = 0; i < NB_COLLECTS; i++)
	{
		listCollect[i]->isCollidePlayer = listCollect[i]->CollectRect.getGlobalBounds().intersects(samplePlayer.getGlobalBounds());
		return listCollect[i]->isCollidePlayer;
	}
}

void Collects::Die()
{
	Alive = false;
}

bool Collects::IsAlive()
{
	return Alive;
}
