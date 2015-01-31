/**
 * \file main.cpp
 * \brief Fichier contenant le point d'entré du programme
 * \author J. PEAULT & Q. PUBERT
 * \version 0.1
 * \date 29 janvier 2015
 *
 * Ce programme permet de tester les fonctionnalités réseaux de la sfml 2.2 . Cela permet également d'entrainer l'équipe pour un projet plus conséquent.
 *
 */
  #define GLOBAL
  #include <SFML/Graphics.hpp>
  #include <LimbGUI/GUI.hpp>
  #include "constantes.hpp"

  #include "affichable.hpp"
  #include "gui_menu.hpp"
  #include "ressourceLoader.hpp"




 int main(void)
 {
	 LFENETRE = 800;
	 HFENETRE = 600;

     sf::RenderWindow mainWindow(sf::VideoMode(LFENETRE,HFENETRE),"MainWindow");

     mainWindow.setVerticalSyncEnabled(true);

	 RessourceLoader ressourceLoader;
	 GUI_menu menuPrincipal(&ressourceLoader,&mainWindow);
	 sf::Event event;

	 while (mainWindow.isOpen()) {

        while (mainWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                mainWindow.close();

                menuPrincipal.gererSaisie(&event);


        }
            menuPrincipal.ouvrir();

            mainWindow.clear();
            menuPrincipal.display();

            mainWindow.display();

	 }

	 return 0;
 }
