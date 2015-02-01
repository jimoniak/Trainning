/**
 * \file gui_textInput.hpp
 * \brief Fichier contenant la class TextInput
 * \author J. PEAULT & Q. PUBERT
 * \version 0.1
 * \date 01 fevrier 2015
 *
 *  La classe Text permet à l'utilisateur de renseigner du text. chaque objet de cette classe pourront posséder un charset choisi
 *	qui permet d'interdire certain caractère.
 */
 
#ifndef TEXT_INPUT
#define TEXT_INPUT


#include "gui_text.hpp"

namespace gui
{

class TextInput : public Widget
{
    public:
		std::string getTextEntered();
		TextInput();
		TextInput(sf::Vector2u size,sf::String charset = "1234567890",sf::Color color=sf::Color::Green);
     
		void setDescription(sf::Font &font,sf::String str = "Titre",int characterSize = 10,sf::Color color = sf::Color::Black);
		void setTextEntered(sf::Font &font,sf::String str = "Renseignez ici",int characterSize = 10,sf::Color color = sf::Color::Black);
    
		
    
		void majTextEntered();
    
    
   
    
		void drawMyself(sf::RenderTarget& target, sf::RenderStates states) const ;
    
		~TextInput();
	
    private:
	
		sf::RectangleShape m_background;
		sf::RectangleShape m_highLight;
		sf::String m_charset;
		gui::Text  *m_description;   /*<! Phrase expliquant ce que la zone de saisie attend */
		gui::Text  *m_textEntered; /*<! texte entré dans la zone de saisie*/
    
     

};


}
#endif