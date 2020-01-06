#include "Intro.h"

Intro::Intro()
{
	m_actualWindow = GameManager::Instance()->GetWindow();

	Setup();
}

Intro::~Intro()
{
}

int Intro::Setup()
{
	if (!textureLogo.loadFromFile("Ressources/Textures/logoAnim.png"))
		return EXIT_FAILURE;

	spLogo.setTexture(textureLogo);
	rectLogo = { 0, 0, 872, 396 };
	spLogo.setTextureRect(rectLogo);
	scaleLogo = { 0.500, 0.500 };
	spLogo.setScale(scaleLogo);

	posLogo = { (1920 / 2) - spLogo.getGlobalBounds().width/2, (1080 / 2) - spLogo.getGlobalBounds().height/2};
	spLogo.setPosition(posLogo);

	rectFade.setSize(sf::Vector2f(spLogo.getGlobalBounds().width, spLogo.getGlobalBounds().height));
	rectFade.setFillColor(sf::Color(0, 0, 0, alphaLogo));
	rectFade.setPosition(posLogo);
}

void Intro::Update()
{
	if (isintroEnd)
	{
		if (cooldown.getElapsedTime().asSeconds() > 2)
		{
			GameManager::Instance()->LoadScene(e_Enum::e_Scene::CHARGEMENT);
			isintroEnd = false;
		}
	}
	else
	{
		if (isFadeEnd)
		{
			if (timerAnimLogo.getElapsedTime().asMilliseconds() > 100)
			{
				rectLogo.left += 872;
				spLogo.setTextureRect(rectLogo);
				if (rectLogo.left == 12 * 872)
				{
					rectLogo.left = 0;
					rectLogo.top = 1 * 396;
					spLogo.setTextureRect(rectLogo);
					isintroEnd = true;
					cooldown.restart();
				}
				timerAnimLogo.restart();
			}
		}
		else
		{
			if (alphaLogo > 0)
			{
				alphaLogo -= 4;
				/*x = ((4 / 255) / 2);
				x = 4;
				x / 255;
				x / 2;*/
				scaleLogo.y += x; //(scaleLogo.y + ((4 / 255)/2));
				scaleLogo.x += ((4 / 255) / 2) * (16/9);
				//std::cout << "scale X : " << scaleLogo.x << std::endl;
				//std::cout << "scale Y : " << scaleLogo.y << std::endl;
				spLogo.setScale(scaleLogo);
				rectFade.setSize(sf::Vector2f(spLogo.getGlobalBounds().width, spLogo.getGlobalBounds().height));
				rectFade.setFillColor(sf::Color(0, 0, 0, alphaLogo));
			}
			else
			{
				isFadeEnd = true;
				alphaLogo = 0;
				rectFade.setFillColor(sf::Color(0, 0, 0, alphaLogo));

				timerAnimLogo.restart();
			}
		}
	}	
}

void Intro::Display()
{
	m_actualWindow->draw(spLogo);
	m_actualWindow->draw(rectFade);
}

void Intro::EventManager(sf::Event p_pollingEvent)
{
}
