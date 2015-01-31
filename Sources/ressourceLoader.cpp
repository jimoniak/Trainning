

#include "ressourceLoader.hpp"

#include "utils.hpp"

RessourceLoader::RessourceLoader()
{
	std::vector<std::string> m_listTexTile;
	std::vector<std::string> m_listTexGUI;

	m_listTexTile = utils::rechercheFichier("Ressources\\Tiles\\", ".png");
	m_listTexGUI = utils::rechercheFichier("Ressources\\GUI\\Bouton\\", ".png");

	for(unsigned int i = 0 ; i < m_listTexTile.size() ; i++ ) //Chargement des Tiles...
	{
		std::string chemin = "Ressources/Tiles/" + m_listTexTile[i];
		m_tabTexTile.push_back(sf::Texture());
		m_tabTexTile[i].loadFromFile(chemin);
	}

	for(unsigned int i = 0 ; i < m_listTexGUI.size() ; i++ ) //Chargement des Boutons...
	{
		std::string chemin = "Ressources/GUI/Bouton/" + m_listTexGUI[i];
		m_tabTexGUI.push_back(sf::Texture());
		m_tabTexGUI[i].loadFromFile(chemin);
	}


}


sf::Texture* RessourceLoader::getTexGUI(unsigned int nbTexture)
{
	if(nbTexture<m_tabTexGUI.size())
	{
		return &m_tabTexGUI[nbTexture];

	}


}
sf::Texture* RessourceLoader::getTexTile(unsigned int nbTexture)
{
	if(nbTexture<m_tabTexTile.size())
	{
		return &m_tabTexTile[nbTexture];

	}



}
