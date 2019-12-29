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

	if (newTexture->Create("Player2.png", "Player2"))
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

	if (newTexture->Create("Bandeau_éditeur.jpg", "Bandeau"))
		_textures.push_back(newTexture);

	newTexture = new Textures();

	if (newTexture->Create("Interface_éditeur.jpg", "Interface éditeur"))
		_textures.push_back(newTexture);

	newTexture = new Textures();

	if (newTexture->Create("MenuIG_J1.png", "MenuIG J1"))
		_textures.push_back(newTexture);

	newTexture = new Textures();

	if (newTexture->Create("MenuIG_J2.png", "MenuIG J2"))
		_textures.push_back(newTexture);

	newTexture = new Textures();

	if (newTexture->Create("Flèche_droite.png", "Flèche droite"))
		_textures.push_back(newTexture);

	newTexture = new Textures();

	if (newTexture->Create("Flèche_gauche.png", "Flèche gauche"))
		_textures.push_back(newTexture);

	newTexture = new Textures();

	if (newTexture->Create("Thème1.jpg", "Thème1"))
		_textures.push_back(newTexture);

	newTexture = new Textures();

	if (newTexture->Create("Thème2.jpg", "Thème2"))
		_textures.push_back(newTexture);

	newTexture = new Textures();

	if (newTexture->Create("Background_interface.jpg", "Background interface"))
		_textures.push_back(newTexture);

	newTexture = new Textures();

	if (newTexture->Create("Menu_button_unselected.png", "Menu bouton non sélectionné"))
		_textures.push_back(newTexture);

	newTexture = new Textures();

	if (newTexture->Create("Menu_button_selected.png", "Menu bouton sélectionné"))
		_textures.push_back(newTexture);

	newTexture = new Textures();

	if (newTexture->Create("Flèche menu.png", "Flèche menu"))
		_textures.push_back(newTexture);

	newTexture = new Textures();

	if (newTexture->Create("LittleButton_unselected.png", "Petit bouton non sélectionné"))
		_textures.push_back(newTexture);

	newTexture = new Textures();

	if (newTexture->Create("LittleButton_selected.png", "Petit bouton sélectionné"))
		_textures.push_back(newTexture);

	newTexture = new Textures();

	if (newTexture->Create("Background_credits.jpg", "Background credits"))
		_textures.push_back(newTexture);

	newTexture = new Textures();

	if (newTexture->Create("Commandes_jeu.png", "Commandes jeu"))
		_textures.push_back(newTexture);

	newTexture = new Textures();

	if (newTexture->Create("Commandes_éditeur.png", "Commandes éditeur"))
		_textures.push_back(newTexture);

	newTexture = new Textures();

	if (newTexture->Create("RB.png", "RB"))
		_textures.push_back(newTexture);

	newTexture = new Textures();

	if (newTexture->Create("RB_Press.png", "RB Press"))
		_textures.push_back(newTexture);

	newTexture = new Textures();

	if (newTexture->Create("LB.png", "LB"))
		_textures.push_back(newTexture);

	newTexture = new Textures();

	if (newTexture->Create("LB_Press.png", "LB Press"))
		_textures.push_back(newTexture);

	newTexture = new Textures();

	if (newTexture->Create("Icone_volume.png", "Icone volume"))
		_textures.push_back(newTexture);

	newTexture = new Textures();

	if (newTexture->Create("Volume.png", "Volume"))
		_textures.push_back(newTexture);

	newTexture = new Textures();

	if (newTexture->Create("Options_button_unselected.png", "Options bouton non sélectionné"))
		_textures.push_back(newTexture);

	newTexture = new Textures();

	if (newTexture->Create("Options_button_selected.png", "Options bouton sélectionné"))
		_textures.push_back(newTexture);

	newTexture = new Textures();

	if (newTexture->Create("Editor_button_unselected.png", "Editeur bouton non sélectionné"))
		_textures.push_back(newTexture);

	newTexture = new Textures();

	if (newTexture->Create("Editor_button_selected.png", "Editeur bouton sélectionné"))
		_textures.push_back(newTexture);

	newTexture = new Textures();

	if (newTexture->Create("Popup.png", "Fenêtre popup"))
		_textures.push_back(newTexture);

	newTexture = new Textures();

	if (newTexture->Create("Bouton_retour.png", "Bouton retour"))
		_textures.push_back(newTexture);

	newTexture = new Textures();

	if (newTexture->Create("Curseur_pose.png", "Curseur pose"))
		_textures.push_back(newTexture);

	newTexture = new Textures();

	if (newTexture->Create("Curseur_suppr.png", "Curseur suppression"))
		_textures.push_back(newTexture);

	newTexture = new Textures();

	if (newTexture->Create("Touches_éditeur.png", "Touches éditeur"))
		_textures.push_back(newTexture);

	newTexture = new Textures();

	if (newTexture->Create("RT.png", "RT"))
		_textures.push_back(newTexture);

	newTexture = new Textures();

	if (newTexture->Create("LT.png", "LT"))
		_textures.push_back(newTexture);

	newTexture = new Textures();

	if (newTexture->Create("Loupe+.png", "Loupe+"))
		_textures.push_back(newTexture);

	newTexture = new Textures();

	if (newTexture->Create("Loupe-.png", "Loupe-"))
		_textures.push_back(newTexture);

	newTexture = new Textures();

	if (newTexture->Create("Bouton_sauvegarder.png", "Bouton sauvegarder"))
		_textures.push_back(newTexture);

	newTexture = new Textures();

	if (newTexture->Create("Touche_select.png", "Touche select"))
		_textures.push_back(newTexture);
}

//Fonction retournant une texture selon le nom appelé
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

//Fonction retournant une police selon le nom appelé
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

//Création d'une texture selon son nom
bool Textures::Create(std::string pFileName, std::string pName)
{
	if (!pFileName.empty())
	{
		_name = pName;

		return _texture.loadFromFile("Ressources/Textures/" + pFileName);
	}

	return false;
}

//Fonction permettant de connaître le nom d'une texture
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

//Création d'une police selon son nom
bool Fonts::Create(std::string pFileName, std::string pName)
{
	if (!pFileName.empty())
	{
		_name = pName;

		return _font.loadFromFile("Ressources/Font/" + pFileName);
	}

	return false;
}

//Fonction permettant de connaître le nom d'une police
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