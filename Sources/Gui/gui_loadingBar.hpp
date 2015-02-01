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
	//GETTER
	
	sf::Vector2f getPosition();
	
	
	//SETTER
	void setSize(sf::Vector2f newSize);
	void setBackColor(sf::Color color);
	void setForeColor(sf::Color color);
	
	void setMax(float MAX);
	void setMin(float MIN);
	void majParam(float actuParam);
	
	
	
	//CONSTRUCTOR
     LoadingBar();
     LoadingBar(sf::Vector2f size,
				sf::String descr,
				float MAX,float param = MAX,
				sf::Color clrBack = sf::Color::Blue,
				sf::Color clrFore = sf::Color::White,
				float MIN=0);
	 
	 
    ~LoadingBar();



    private:

    sf::RectangleShape m_background;		/*<! arrière plan de la barre					  */
    sf::RectangleShape m_foreground;		/*<! partie de la barre changeante 				  */
    float m_MIN; 							/*<! valeur minimal du parametre (0% de la barre) */
	float m_param;							/*<! valeur du parametre						  */
    float m_MAX;							/*<! valeur maximal du parametre (100%de la barre)*/
    gui::Text *m_description;				/*<! Texte d'accompagnement de la barre			  */
    gui::Text *m_count; 					/*<! affichage du parametre :( m_param / M_MAX)	  */

};




}
#endif