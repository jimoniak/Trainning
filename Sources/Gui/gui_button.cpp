
#include "gui_button.hpp"

namespace gui
{
	
	
     Button()
     {
     
     }
	 
	 Button(const sf::Texture &texture,sf::Vector2f position ) :m_text(addChild(std::make_unique<gui::Text>())){
		
		 setPosition(posiiton);
		 setTexture(texture);
			 
	 }
    
    void Button::setTexture(const sf::Texture &texture){
		
        m_sprite.setTexture(texture);
        m_bounds = m_sprite.getGlobalBounds();    
    
    }
    
    template <typename F>
    void Button::setOnClick(F f) { // button.setOnClick([&menu] { menu.open(); });
        m_onClickFunction = std::move(f);
    }
    
    void Button::onMyClick() override {
        if (m_onClickFunction) {
            m_onClickFunction();
        }
    }
    
    void Button::onMove(const sf::Vector2f& delta){
     m_sprite.setPosition(delta);
     m_highlight.setposition(delta);
   }
    
    Button::~Button(){}
    
    void Button::setText(sf::Font &font,sf::String str ,int characterSize ,sf::Color color){
    
    m_text->setFont(font);
    m_text->setString(str);
    m_text->setCharacterSize(characterSize);
    m_text->setColor(color);    
    }  
    
    void Button::drawMyself(sf::RenderTarget& target, sf::RenderStates states) const 
    {
       
        target.draw(m_sprite);
        target.draw(m_highLight);
    }
	
	
}