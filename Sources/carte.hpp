/**
 * \file carte.hpp
 * \brief Fichier contenant la class Map
 * \author J. PEAULT & Q. PUBERT
 * \version 0.1
 * \date 29 janvier 2015
 *
 * La classe Map permet de créer la carte sur laquelle les joueurs évolue.
 *
 */




#ifndef MAP
#define MAP

#include <SFML/Graphics.hpp>
#include "affichable.hpp"

class Map : public Displayable
{

	private:
	sf::Vector2f m_size;//en nombres de tiles
	sf::Texture  m_texture;
	sf::Sprite    m_apparence;


	public:
	    Map();
	    Map(sf::Vector2f size,sf::RenderWindow *window);
      ~Map();


	    void createMap(RessourceLoader &rsholder);

	    bool display();

	    //GETTER:
	    sf::Vector2f getSize();



};





#endif
