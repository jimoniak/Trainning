/**
 * \file messagerie.hpp
 * \brief Fichier contenant la class Messenger
 * \author J. PEAULT & Q. PUBERT
 * \version 0.1
 * \date 29 janvier 2015
 *
 * La classe Messagerie permet au joueur de communiquer entre eux. 
 *
 */
 
#ifndef MESSENGER
#define MESSENGER
 
 #include <SFML/Graphics.hpp>
 //#include <LimbGUI/GUI.hpp>
 
 #include "Displayable.hpp"
 #include <string>
 #include <vector>
 
 
 
 class Messenger : public Displayable
 {
	 private:
	 sf::Text m_textEntered; /*!< texte affichable entré par l'utilisateur de la messagerie*/
	 std::vector<std::string> m_linesMessenger;/*!< Sauvegarde ligne par ligne des conversations*/
	 
	 bool m_open;/*!< bool permettant de savoir si la messagerie est active ou non*/
	 
	 
	 public:
	 //void refreshMessenger();/*!< fonction permettant de raffraichir le messenger*/
	 void addLine(std::string newText);/*!< Méthode permettant d'ajouter une ligne dans le messenger (nouveau message par exemple ) et de découper proprement*/
	 
	 void display();/*!< afficher...*/
	 
	 //GETTER
	 const bool isOpen();/*!< récupération de l'état de la messagerie*/
 }; 
 #endif