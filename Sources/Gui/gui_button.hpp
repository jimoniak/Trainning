
#ifndef BUTTON
#define BUTTON

#include "gui_text.hpp"

namespace gui
{

class Button : public Widget
{
    public:
     Button();
     
    
    void setTexture(const sf::Texture &texture);
    
    
    template <typename F>
    void setOnClick(F f) { // button.setOnClick([&menu] { menu.open(); });
        m_onClickFunction = std::move(f);
    }
    
    virtual void onMyClick();
    
    void onMove(const sf::Vector2f& delta);
    
    ~Button();
    
    void setText(sf::Font &font,std::string str = "Titre",int characterSize = 10,sf::Color color = sf::Color::Black);   
    void drawMyself(sf::RenderTarget& target, sf::RenderStates states) const ;
    
    private:
    gui::Text *m_text;
    
    sf::RectangleShape m_highLight;
    sf::Sprite   m_sprite;
    std::function<void()> m_onClickFunction;


};
}

#endif