
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
		TextInput(sf::Vector2u size,std::string charset = "1234567890",sf::Color color=sf::Color::Green);
     
		void setDescription(sf::Font &font,std::string str = "Titre",int characterSize = 10,sf::Color color = sf::Color::Black);
		void setTextEntered(sf::Font &font,std::string str = "Renseignez ici",int characterSize = 10,sf::Color color = sf::Color::Black);
    
		void onMove(const sf::Vector2f& delta);
    
		void majTextEntered();
    
    
   
    
		void drawMyself(sf::RenderTarget& target, sf::RenderStates states) const ;
    
		~TextInput();
	
    private:
		sf::RectangleShape m_background;
		sf::RectangleShape m_highLight;
		std::string m_charset;
		gui::Text *m_description;   /*<! Phrase expliquant ce que la zone de saisie attend */
		sf::Text m_textEntered; /*<! texte entr� dans la zone de saisie*/
    
     

};


}
#endif