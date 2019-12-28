#include "ResourceManager.h"

#pragma region ResourceManager
ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}

//Chargement de toutes les ressources
void ResourceManager::Load()
{
	Fonts* newFont = new Fonts();

	if (newFont->Create("Font.ttf", "Font"))
		_fonts.push_back(newFont);

	Textures* newTexture = new Textures();

	newTexture = new Textures();

	if (newTexture->Create("logoAnim.png", "Logo"))
		_textures.push_back(newTexture);

	for (int i = 0; i < 8; i++)
	{
		newTexture = new Textures();

		if (newTexture->Create("Tile" + std::to_string(i + 1) + ".png", "Case" + std::to_string(i + 1)))
			_textures.push_back(newTexture);
	}

	for (int i = 0; i < 10; i++)
	{
		newTexture = new Textures();

		if (newTexture->Create("Plan1_" + std::to_string(i) + ".png", "Plan1_" + std::to_string(i)))
			_textures.push_back(newTexture);
	}

	for (int i = 0; i < 4; i++)
	{
		newTexture = new Textures();

		if (newTexture->Create("P" + std::to_string(i + 1) + ".png", "Plan" + std::to_string(i + 1)))
			_textures.push_back(newTexture);
	}

	newTexture = new Textures();

	if (newTexture->Create("Player.png", "Player"))
		_textures.push_back(newTexture);

	for (int i = 0; i < 4; i++)
	{
		newTexture = new Textures();

		if (newTexture->Create("Key" + std::to_string(i + 1) + ".jpg", "Key" + std::to_string(i + 1)))
			_textures.push_back(newTexture);
	}

	newTexture = new Textures();

	if (newTexture->Create("Tileset.png", "Tileset"))
		_textures.push_back(newTexture);

	newTexture = new Textures();

	if (newTexture->Create("Bandeau_�diteur.jpg", "Bandeau"))
		_textures.push_back(newTexture);

	newTexture = new Textures();

	if (newTexture->Create("Interface_�diteur.jpg", "Interface �diteur"))
		_textures.push_back(newTexture);

	newTexture = new Textures();

	if (newTexture->Create("MenuIG_J1.png", "MenuIG J1"))
		_textures.push_back(newTexture);

	newTexture = new Textures();

	if (newTexture->Create("MenuIG_J2.png", "MenuIG J2"))
		_textures.push_back(newTexture);

	newTexture = new Textures();

	if (newTexture->Create("Fl�che_droite.png", "Fl�che droite"))
		_textures.push_back(newTexture);

	newTexture = new Textures();

	if (newTexture->Create("Fl�che_gauche.png", "Fl�che gauche"))
		_textures.push_back(newTexture);

	newTexture = new Textures();

	if (newTexture->Create("Th�me1.jpg", "Th�me1"))
		_textures.push_back(newTexture);

	newTexture = new Textures();

	if (newTexture->Create("Th�me2.jpg", "Th�me2"))
		_textures.push_back(newTexture);

	newTexture = new Textures();

	if (newTexture->Create("Background_interface.jpg", "Background interface"))
		_textures.push_back(newTexture);
}

//Fonction retournant une texture selon le nom appel�
sf::Texture * ResourceManager::GetTexture(std::string _FileName)
{
	for (int i = 0; i < _textures.size(); i++)
	{
		if (_textures[i]->GetName() == _FileName)
		{
			return _textures[i]->GetTexture();
		}
	}

	return NULL;
}

//Fonction retournant une police selon le nom appel�
sf::Font* ResourceManager::GetFont(std::string _FileName)
{
	for (int i = 0; i < _fonts.size(); i++)
	{
		if (_fonts[i]->GetName() == _FileName)
		{
			return _fonts[i]->GetFont();
		}
	}

	return NULL;
}
std::vector<Textures*> ResourceManager::GetTextureVector()
{
	return _textures;
}
std::vector<Fonts*> ResourceManager::GetFontVector()
{
	return _fonts;
}
float ResourceManager::GetVectorsSize()
{
	return _fonts.size() + _textures.size();
}
#pragma endregion

#pragma region Textures
Textures::Textures()
{
}

Textures::~Textures()
{
}

//Cr�ation d'une texture selon son nom
bool Textures::Create(std::string pFileName, std::string pName)
{
	if (!pFileName.empty())
	{
		_name = pName;

		return _texture.loadFromFile("Ressources/Textures/" + pFileName);
	}

	return false;
}

//Fonction permettant de conna�tre le nom d'une texture
std::string Textures::GetName()
{
	return _name;
}

//Fonction retournant la texture
sf::Texture* Textures::GetTexture()
{
	return &_texture;
}
#pragma endregion

#pragma region Fonts
Fonts::Fonts()
{
}

Fonts::~Fonts()
{
}

//Cr�ation d'une police selon son nom
bool Fonts::Create(std::string pFileName, std::string pName)
{
	if (!pFileName.empty())
	{
		_name = pName;

		return _font.loadFromFile("Ressources/Font/" + pFileName);
	}

	return false;
}

//Fonction permettant de conna�tre le nom d'une police
std::string Fonts::GetName()
{
	return _name;
}

//Fonction retournant la police
sf::Font* Fonts::GetFont()
{
	return &_font;
}
#pragma endregion