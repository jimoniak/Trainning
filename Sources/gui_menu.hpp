/**
 * \file gui_menu.hpp
 * \brief Fichier contenant la class displayable
 * \author J. PEAULT & Q. PUBERT
 * \version 0.1
 * \date 29 janvier 2015
 *
 * La classe GUI_menu permet d'afficher/gérer le gui et tout interface.
 *
 */

#ifndef GUI_MENU
#define GUI_MENU

//#include "constantes.hpp"
#include <SFML/Graphics.hpp>

#include "ressourceLoader.hpp"

#include <vector>


/*! \class GUI_Menu
   * \brief classe servant à gérer tout le gui
   *
   *  .
   */


class GUI_menu : public Displayable
{

	private:
	bool m_open;
	int m_pageMenu;

	sf::Font m_font;

	//attributs liés à l'affichage principal:

	//page 0:
	sf::RectangleShape m_fond;
	lgui::Bouton m_server;
	lgui::Bouton m_client;
	lgui::Bouton m_quitter;

	//page 1:

        //Texte
        sf::Text m_textServerName;
		sf::Text m_textport;
		//Boutons
        lgui::Bouton m_back;

        //Zone de saisie
        lgui::ZoneSaisie m_serverName;
        lgui::ZoneSaisie m_port;


	public:

	GUI_menu(RessourceLoader *rsholder,sf::RenderWindow *window);
   ~GUI_menu();


   void ouvrir();
   void gererSaisie(sf::Event *evt);
   bool display();

   //GETTER
   sf::RenderWindow getWindow();
	bool isOpen();






};




#endif
