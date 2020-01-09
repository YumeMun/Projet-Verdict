#include "Chargement.h"
#include "GameManager.h"
#include "ResourceManager.h"

Chargement::Chargement()
{
	std::cout << "Chargement constructor" << std::endl;

	m_actualWindow = GameManager::Instance()->GetWindow();

	isLoaded = false;
	LoadThread = std::thread(&Chargement::Load, this);

	LoadingBack.setSize(sf::Vector2f(1000, 30));
	LoadingBack.setFillColor(sf::Color(50, 50, 50, 255));
	LoadingBack.setOrigin(LoadingBack.getSize().x / 2, LoadingBack.getSize().y / 2);
	LoadingBack.setPosition(960, 900);

	LoadingBar.setSize(sf::Vector2f(0, 30));
	LoadingBar.setFillColor(sf::Color{ 159, 60, 61, 255 });
	LoadingBar.setPosition(LoadingBack.getGlobalBounds().left, LoadingBack.getGlobalBounds().top);

	BackgroundTexture[0].loadFromFile("Ressources/Textures/Background_Chargement1.png");
	BackgroundTexture[1].loadFromFile("Ressources/Textures/Background_Chargement2.png");

	spBackground[0].setTexture(BackgroundTexture[0]);
	spBackground[1].setTexture(BackgroundTexture[1]);

	spBackground[1].setPosition(-1920, 0);

	LogoTexture[0].loadFromFile(("Ressources/Textures/Logo1.png"));
	LogoTexture[1].loadFromFile(("Ressources/Textures/Logo2.png"));

	spLogo[0].setTexture(LogoTexture[0]);
	spLogo[1].setTexture(LogoTexture[1]);

	for (int i = 0; i < 2; i++)
	{
		spLogo[i].setOrigin(spLogo[i].getGlobalBounds().width / 2, spLogo[i].getGlobalBounds().height / 2);
		spLogo[i].setPosition(960, 700);
	}

	spLogo[0].setScale(0, 1);
	spLogo[1].setScale(1, 1);

	Scale[0] = 1;
	Scale[1] = 0;

	Font.loadFromFile("Ressources/Font/Font.TTF");

	Percent.setFont(Font);
	Percent.setCharacterSize(50);
	Percent.setFillColor(sf::Color::White);
	Percent.setString("0 %");
	Percent.setOrigin(Percent.getGlobalBounds().width / 2, Percent.getGlobalBounds().height / 2);
	Percent.setPosition(LoadingBack.getPosition().x, LoadingBack.getPosition().y + LoadingBack.getSize().y * 2);
}

Chargement::~Chargement()
{
}

void Chargement::Update()
{
	spBackground[1].move(50, 0);

	if (spBackground[1].getPosition().x >= 1920)
		spBackground[1].setPosition(-1920, 0);

	if (AnimLogo.getElapsedTime().asSeconds() > 1 && AnimLogo.getElapsedTime().asSeconds() < 4)
	{
		if (Scale[0] > 0)
			Scale[0] -= 0.05;

		if (Scale[1] < 1 && Scale[0] <= 0.1)
			Scale[1] += 0.05;
	}
	else if (AnimLogo.getElapsedTime().asSeconds() > 4 && AnimLogo.getElapsedTime().asSeconds() < 6)
	{
		if (Scale[1] > 0)
			Scale[1] -= 0.05;

		if (Scale[0] < 1 && Scale[1] <= 0.1)
			Scale[0] += 0.05;
	}
	else if (AnimLogo.getElapsedTime().asSeconds() > 6)
		AnimLogo.restart();

	spLogo[0].setScale(Scale[0], 1);
	spLogo[1].setScale(Scale[1], 1);

	if (isLoaded == true)
	{
		std::cout << "Ressources chargees" << std::endl;
		GameManager::Instance()->LoadScene(e_Enum::MENU);
	}
	else if (isLoaded == false)
	{
		// 24 is font + texture vectors final size
		LoadingBar.setSize(sf::Vector2f((ResourceManager::Instance()->GetVectorsSize() / 129) * LoadingBack.getSize().x, 30));
		Percent.setString(std::to_string(int(ResourceManager::Instance()->GetVectorsSize() / 129 * 100)) + " %");
		Percent.setOrigin(Percent.getGlobalBounds().width / 2, Percent.getGlobalBounds().height / 2);
	}

	//Percent.setPosition(LoadingBack.getPosition().x, LoadingBack.getPosition().y + LoadingBack.getSize().y);
}

void Chargement::Display()
{
	m_actualWindow->clear(sf::Color{ 200, 119, 57, 255 });
	m_actualWindow->draw(spBackground[1]);
	m_actualWindow->draw(spBackground[0]);

	m_actualWindow->draw(LoadingBack);
	m_actualWindow->draw(LoadingBar);

	for (int i = 0; i < 2; i++)
	{
		m_actualWindow->draw(spLogo[i]);
	}

	m_actualWindow->draw(Percent);
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