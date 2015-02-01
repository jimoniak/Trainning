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