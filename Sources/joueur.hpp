/**
 * \file joueur.hpp
 * \brief Fichier contenant la classe Player
 * \author J. PEAULT & Q. PUBERT
 * \version 0.1
 * \date 29 janvier 2014
 *
 * Player est une classe qui repr�sente le joueur dans le jeu. Elle h�rite � la fois de Displayable et de NetWork  car elle 
 * elle peut � la fois �tre affich� et communiquer avec le serveur.
 *
 */


#ifndef PLAYER
#define PLAYER

#include <SFML/Graphics.hpp>

#include "affichable.hpp"

#include <string>

/*! \class Player
   * \brief La classe representant l'utilisateur
   *
   *  Player permet � l'utilisateur de prendre en main un personnage sur le serveur et ainsi int�ragir dans l'environnement.
   */

   
class Player : public Displayable 
{
	
	private:
	sf::Texture *m_texture; /*!<pointeur de type texture permettant de recevoir la texture n�c�ssaire � m_sprite*/
	sf::Sprite   m_sprite; /*!< Le sprite permettant l'affichage*/
	
	std::string m_pseudonyme;/*!< pseudonyme du joueur*/
	std::string m_password;/*!<et son mot de passe*/
	
	int m_skinNumber; /*!<numero du skin � utiliser*/
	
	public:
	
	//methode herit�es modifi�es:
	void display(); /*!<affichage h�rit� de la classe Displayable*/
	
	//methodes propres � Player:
	
	
	
	//GETTER
	
	const std::string getPseudo();/*!<recuperer le pseudo du joueur*/
	//sf::Vector2f getPosition();
	const int getSkinNB();/*!<recup�rer le numero du skin actuel*/
	
	//SETTER
	void setPseudo(std::string newPseudo);/*!<modifier le pseudonyme*/
	void setSkin(int newSkin);/*!<changer le skin en envoyant un nouveau num�ro*/
	
	
	
};

#endif