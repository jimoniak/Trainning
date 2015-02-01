/**
 * \file gui_loadingBar.hpp
 * \brief Fichier contenant la class LoadingBar
 * \author J. PEAULT & Q. PUBERT
 * \version 0.1
 * \date 01 fevrier 2015
 *
 *  LoadingBar permet de créer des barres de chargements ou d'information (par exemple la vie d'un joueur). en fonction d'une la valeur actuelle de son
 *  paramètre et le maximum, la sf::RectangleShape m_foreground changera de taille
 */
#ifndef LOADING_BAR
#define LOADING_BAR

#include "gui_text.hpp"



namespace gui
{

class LoadingBar : public Widget
{

    public:
     LoadingBar();
     LoadingBar(sf::Vector2f size,
				std::string descr,
				float MAX,float MIN=0,
				sf::Color clrBack = sf::Color::Blue,
				sf::Color clrFore = sf::Color::White);
	 
	 
    ~LoadingBar();



    private:

    sf::RectangleShape m_background;
    sf::RectangleShape m_foreground;
    float m_MIN;
    float m_MAX;
    gui::Text *m_description;
    gui::Text *m_count;

};




}
#endif