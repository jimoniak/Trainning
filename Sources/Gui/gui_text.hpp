/**
 * \file gui_text.hpp
 * \brief Fichier contenant la class Text
 * \author J. PEAULT & Q. PUBERT
 * \version 0.1
 * \date 01 fevrier 2015
 *
 *  La classe Text est un dérivé de la class sf::Text. En effet, afin de pouvoir l'intégrer correctement au gui, cette class englobe le sf::Text dans un Widget.
 *  L'objet peut ainsi être manipulé comme un widget a part entière.
 */

#ifndef TEXT
#define TEXT

#include <string>
#include "gui_widget.hpp"
namespace gui
{

class Text : public Widget
{
    public:
	~Text();
    void setFont(const sf::Font &font);
    void setString(const sf::String& str);
    void setCharacterSize(int size);
    void setColor(const sf::Color color);

    void onMove(const sf::Vector2f& delta);
    void drawMyself(sf::RenderTarget& target, sf::RenderStates states) const ;
    
    private:
	
    sf::Text m_text;
};

}

#endif