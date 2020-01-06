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

	for (int i = 0; i < 2; i++)
	{
		newTexture = new Textures();

		if (newTexture->Create("Skin/J1_Skin" + std::to_string(i + 1) + ".png", "Player1_Colo" + std::to_string(i + 1)))
			_textures.push_back(newTexture);
	}

	for (int i = 0; i < 2; i++)
	{
		newTexture = new Textures();

		if (newTexture->Create("Skin/J2_Skin" + std::to_string(i + 1) + ".png", "Player2_Colo" + std::to_string(i + 1)))
			_textures.push_back(newTexture);
	}


	for (int i = 0; i < 2; i++)
	{
		newTexture = new Textures();

		if (newTexture->Create("Skin/skinLocked" + std::to_string(i + 1) + ".png", "Player_Cache" + std::to_string(i + 1)))
			_textures.push_back(newTexture);
	}

	/*newTexture = new Textures();

	if (newTexture->Create("Player1.png", "Player1"))
		_textures.push_back(newTexture);

	newTexture = new Textures();

	if (newTexture->Create("Player2.png", "Player2"))
		_textures.push_back(newTexture);*/

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

	newTexture = new Textures();

	if (newTexture->Create("Menu_button_unselected.png", "Menu bouton non s�lectionn�"))
		_textures.push_back(newTexture);

	newTexture = new Textures();

	if (newTexture->Create("Menu_button_selected.png", "Menu bouton s�lectionn�"))
		_textures.push_back(newTexture);

	newTexture = new Textures();

	if (newTexture->Create("Fl�che menu.png", "Fl�che menu"))
		_textures.push_back(newTexture);

	newTexture = new Textures();

	if (newTexture->Create("LittleButton_unselected.png", "Petit bouton non s�lectionn�"))
		_textures.push_back(newTexture);

	newTexture = new Textures();

	if (newTexture->Create("LittleButton_selected.png", "Petit bouton s�lectionn�"))
		_textures.push_back(newTexture);

	newTexture = new Textures();

	if (newTexture->Create("Background_credits.jpg", "Background credits"))
		_textures.push_back(newTexture);

	newTexture = new Textures();

	if (newTexture->Create("Commandes_jeu.png", "Commandes jeu"))
		_textures.push_back(newTexture);

	newTexture = new Textures();

	if (newTexture->Create("Commandes_�diteur.png", "Commandes �diteur"))
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

	if (newTexture->Create("Options_button_unselected.png", "Options bouton non s�lectionn�"))
		_textures.push_back(newTexture);

	newTexture = new Textures();

	if (newTexture->Create("Options_button_selected.png", "Options bouton s�lectionn�"))
		_textures.push_back(newTexture);

	newTexture = new Textures();

	if (newTexture->Create("Editor_button_unselected.png", "Editeur bouton non s�lectionn�"))
		_textures.push_back(newTexture);

	newTexture = new Textures();

	if (newTexture->Create("Editor_button_selected.png", "Editeur bouton s�lectionn�"))
		_textures.push_back(newTexture);

	newTexture = new Textures();

	if (newTexture->Create("Popup.png", "Fen�tre popup"))
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

	if (newTexture->Create("Touches_�diteur.png", "Touches �diteur"))
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

	newTexture = new Textures();

	if (newTexture->Create("InfoTile.jpg", "Info tile"))
		_textures.push_back(newTexture);

	newTexture = new Textures();

	if (newTexture->Create("Huile_test.png", "OilFlake"))
		_textures.push_back(newTexture);

	newTexture = new Textures();

	if (newTexture->Create("Level_select_background.png", "Background s�lection niveau"))
		_textures.push_back(newTexture);

	newTexture = new Textures();

	if (newTexture->Create("LevelSelection_button.png", "Selection niveau bouton"))
		_textures.push_back(newTexture);

	newTexture = new Textures();

	if (newTexture->Create("LevelSelection_flechedroite.png", "Selection niveau fl�che droite"))
		_textures.push_back(newTexture);

	newTexture = new Textures();

	if (newTexture->Create("LevelSelection_flechegauche.png", "Selection niveau fl�che gauche"))
		_textures.push_back(newTexture);

	newTexture = new Textures();

	if (newTexture->Create("Touches_s�lection.png", "Touches s�lection"))
		_textures.push_back(newTexture);

	newTexture = new Textures();

	if (newTexture->Create("First.png", "First"))
		_textures.push_back(newTexture);

	newTexture = new Textures();

	if (newTexture->Create("Second.png", "Second"))
		_textures.push_back(newTexture);

	newTexture = new Textures();

	if (newTexture->Create("sprite_missile.png", "Rocket"))
		_textures.push_back(newTexture);

	newTexture = new Textures();

	if (newTexture->Create("sprite_onde_de_choc.png", "Shock"))
		_textures.push_back(newTexture);

	newTexture = new Textures();

	if (newTexture->Create("HudJ1.png", "HUD J1"))
		_textures.push_back(newTexture);

	newTexture = new Textures();

	if (newTexture->Create("sprite_fume_missile.png", "Smoke"))
		_textures.push_back(newTexture);

	newTexture = new Textures();

	if (newTexture->Create("HudJ2.png", "HUD J2"))
		_textures.push_back(newTexture);

	newTexture = new Textures();

	if (newTexture->Create("NumeroJoueur.png", "Numero joueur"))
		_textures.push_back(newTexture);

	for (int i = 0; i < 6; i++)
	{
		newTexture = new Textures();

		if (newTexture->Create("Collect" + std::to_string(i + 1) + ".png", "Collect" + std::to_string(i + 1)))
			_textures.push_back(newTexture);
	}

	//Au dessus y a 87 ressources (marre de recompter � chaque fois)
}

//Fonction retournant une texture selon le nom appel�
sf::Texture* ResourceManager::GetTexture(std::string _FileName)
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