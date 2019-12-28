#include "Chargement.h"
#include "GameManager.h"
#include "ResourceManager.h"

Chargement::Chargement()
{
	std::cout << "Chargement constructor" << std::endl;

	m_actualWindow = GameManager::Instance()->GetWindow();

	isLoaded = false;
	LoadThread = std::thread(&Chargement::Load, this);

	LoadingTxt.setFont(*ResourceManager::Instance()->GetFont("Font"));
	LoadingTxt.setCharacterSize(100);
	LoadingTxt.setFillColor(sf::Color::White);
	LoadingTxt.setString("Chargement..");
	LoadingTxt.setOrigin(LoadingTxt.getGlobalBounds().width / 2, 50);
	LoadingTxt.setPosition(960, 290);

	LoadingBack.setSize(sf::Vector2f(1000, 50));
	LoadingBack.setFillColor(sf::Color(50,50,50,255));
	LoadingBack.setOrigin(LoadingBack.getSize().x / 2, LoadingBack.getSize().y / 2);
	LoadingBack.setPosition(960, 490);

	LoadingBar.setSize(sf::Vector2f(0, 50));
	LoadingBar.setFillColor(sf::Color::White);
	LoadingBar.setPosition(LoadingBack.getGlobalBounds().left, LoadingBack.getGlobalBounds().top);

	rectLogo = { 0, 0, 872, 396 };
	spLogo.setTextureRect(rectLogo);
	spLogo.setTexture(*ResourceManager::Instance()->GetTexture("Logo"));
	timerAnimLogo.restart();
}

Chargement::~Chargement()
{
}

void Chargement::Update()
{
	if (isLoaded == true)
	{
		std::cout << "Ressources chargees" << std::endl;
		GameManager::Instance()->LoadScene(e_Enum::MENU);
	}
	else if (isLoaded == false)
	{
		LoadingTxt.setFont(*ResourceManager::Instance()->GetFont("Font"));
		LoadingTxt.setOrigin(LoadingTxt.getGlobalBounds().width / 2, 50);

		spLogo.setTexture(*ResourceManager::Instance()->GetTexture("Logo"));
		spLogo.setPosition(sf::Vector2f((1920 / 2) - (spLogo.getGlobalBounds().width / 2), ((1080 / 2) - (spLogo.getGlobalBounds().height / 2)) + 250));
		spLogo.setScale(sf::Vector2f(0.6, 0.6));
		if (timerAnimLogo.getElapsedTime().asSeconds() >= 0.04)
		{
			rectLogo.left += 872;
			spLogo.setTextureRect(rectLogo);
			animCount++;
			timerAnimLogo.restart();
		}

		if (animCount == 16)
		{
			rectLogo.left = 0;
			rectLogo.top = 396;
			spLogo.setTextureRect(rectLogo);
		}
		else if (animCount == 17)
		{
			rectLogo.left = 0;
			rectLogo.top = 0;
			spLogo.setTextureRect(rectLogo);
			animCount = 0;
		}

		// 24 is font + texture vectors final size
		LoadingBar.setSize(sf::Vector2f((ResourceManager::Instance()->GetVectorsSize() / 39) * LoadingBack.getSize().x, 50));
	}
}

void Chargement::Display()
{
	m_actualWindow->draw(LoadingBack);
	m_actualWindow->draw(LoadingBar);
	m_actualWindow->draw(LoadingTxt);
	m_actualWindow->draw(spLogo);
}

void Chargement::EventManager(sf::Event p_pollingEvent)
{
}

void Chargement::Load()
{
	ResourceManager::Instance()->Load();
	//std::cout << ResourceManager::Instance()->GetTextureVector().size() + ResourceManager::Instance()->GetFontVector().size() << std::endl;
	isLoaded = true;
}