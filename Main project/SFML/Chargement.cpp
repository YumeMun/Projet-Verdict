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
	LoadingTxt.setPosition(960, 440);

	LoadingBack.setSize(sf::Vector2f(1000, 50));
	LoadingBack.setFillColor(sf::Color(50,50,50,255));
	LoadingBack.setOrigin(LoadingBack.getSize().x / 2, LoadingBack.getSize().y / 2);
	LoadingBack.setPosition(960, 640);

	LoadingBar.setSize(sf::Vector2f(0, 50));
	LoadingBar.setFillColor(sf::Color::White);
	LoadingBar.setPosition(LoadingBack.getGlobalBounds().left, LoadingBack.getGlobalBounds().top);
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

		// 24 is font + texture vectors final size
		LoadingBar.setSize(sf::Vector2f((ResourceManager::Instance()->GetVectorsSize() / 24) * LoadingBack.getSize().x, 50));
	}
}

void Chargement::Display()
{
	m_actualWindow->draw(LoadingBack);
	m_actualWindow->draw(LoadingBar);
	m_actualWindow->draw(LoadingTxt);
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