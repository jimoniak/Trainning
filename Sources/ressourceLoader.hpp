


#ifndef RESSOURCE
#define RESSOURCE

//#include "constantes.hpp"
#include <SFML/Graphics.hpp>
#include <vector>


class RessourceLoader
{
	private:
	std::vector<sf::Texture> m_tabTexTile;
	std::vector<sf::Texture> m_tabTexGUI;


	public:

	RessourceLoader();

	sf::Texture* getTexGUI(unsigned int nbTexture);
	sf::Texture* getTexTile(unsigned int nbTexture);


};


#endif
