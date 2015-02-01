/**
 * \file gui_button.hpp
 * \brief Fichier contenant la classe button
 * \author J. PEAULT & Q. PUBERT
 * \version 0.1
 * \date 01 fevrier 2015
 *
 *  La classe button permet de créer des boutons qui permettent d'intéragir avec le programme. Ils sont crées à partir d'une texture qui determinera leur bound.
 */
#ifndef BUTTON
#define BUTTON

#include "gui_text.hpp"

namespace gui
{

class Button : public Widget
{
    public:
     Button();
	 Button(const sf::Texture &texture,sf::Vector2f position = {0,0} );
     
    
    void setTexture(const sf::Texture &texture);
	void setText(sf::Font &font,sf::String str = "Titre",int characterSize = 10,sf::Color color = sf::Color::Black);   
    
    
    template <typename F>
    void setOnClick(F f) { // button.setOnClick([&menu] { menu.open(); });
        m_onClickFunction = std::move(f);
    }
    
    void onMyClick();   
    void onMove(const sf::Vector2f& delta);   
    void drawMyself(sf::RenderTarget& target, sf::RenderStates states) const ;
	
    ~Button();
	
    private:
	
    gui::Text *m_text;
    
    sf::RectangleShape m_highLight;
    sf::Sprite   m_sprite;
    std::function<void()> m_onClickFunction;


};
}

#endif