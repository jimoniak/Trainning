

/**
 * \file affichage.hpp
 * \brief Fichier contenant la class displayable
 * \author J. PEAULT & Q. PUBERT
 * \version 0.1
 * \date 29 janvier 2015
 *
 * La classe displayable permet de gérer l'affichage de toutes les classes qui en hérite.
 *
 */




#ifndef DISPLAYABLE
#define DISPLAYABLE



/*! \class Dispayable
   * \brief classe abstraite permettant de gérer l'affichage des objets filles.
   *
   *  La classe gere l'affichage de toutes ses héritières.
   */

class Displayable
{
	protected:

	sf::Vector2f m_position;/*!< position de l'objet à dessiner*/
	sf::RenderWindow *m_window;/*!< pointeur permettant de dessiner dans la fenêtre visée*/

	public:

	virtual bool display() = 0;/*!< Afficher l'objet*/


	//CONSTRUCTOR
			 Displayable();

	//DESTRUCTOR
	virtual ~Displayable();

	//SETTER
	void setPosition(sf::Vector2f newPosition);/*!< Changer arbitrairement la position*/
	void setTexture(sf::Texture *newTexture);/*!< Changer la texture de l'objet*/
	void setWindow(sf::RenderWindow *newWindow);/*!< changer la fenetre dans laquelle dessiner*/



};



#endif
