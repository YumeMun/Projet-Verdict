#include "Scene.h"
#include "ResourceManager.h"

//Creation Scene vide
Scene::Scene()
{
	m_actualWindow = NULL;
	if (ResourceManager::Instance()->GetTexture("Bouton retour"))
		spBoutonRetour.setTexture(*ResourceManager::Instance()->GetTexture("Bouton retour"));
	spBoutonRetour.setPosition(0, 950);
}

//Destructeur Generique
Scene::~Scene()
{
}
