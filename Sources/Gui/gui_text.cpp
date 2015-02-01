

#include "gui_text.hpp"

namespace gui
{
	
    void Text::setFont(const sf::Font &font){
        m_text.setFont(font);
    }
    void Text::setString(const sf::String& str){
        m_text.setString(str);
    }
    void Text::setCharacterSize(int size){
        m_text.setCharacterSize(size);
    }
    void Text::setColor(const sf::Color color){
        m_text.setColor(color);
    }

    void Text::onMove(const sf::Vector2f& delta){
    m_text.setPosition(delta);    
    }
	
    void Text::drawMyself(sf::RenderTarget& target, sf::RenderStates states) const 
    {target.draw(m_text);
    }
	
	Text::~Text(){}
    
};
	
	
	
	
	
	
}