
#include "gui_textInput.hpp"

namespace gui
{
	std::string TextInput::getTextEntered(){
    return m_textEntered;
    }
     TextInput::TextInput();
     TextInput::TextInput(sf::Vector2u size,std::string charset,sf::Color color):
     m_description(addChild(std::make_unique<gui::Text>())){
     m_background.setSize(size);
     m_highLight.setSize(size);
     m_charset = charset;     
     m_background.setFillColor(color);
     m_highLight.setFillColor(sf::Color(125,125,125,125));   
     }
     
     void TextInput::setDescription(sf::Font &font,std::string str,int characterSize ,sf::Color color){
    
    m_description->setFont(font);
    m_description->setString(str);
    m_description->setCharacterSize(characterSize);
    m_description->setColor(color);    
    }
    void TextInput::setTextEntered(sf::Font &font,std::string str,int characterSize ,sf::Color color ){
    
    m_textEntered->setFont(font);
    m_textEntered->setString(str);
    m_textEntered->setCharacterSize(characterSize);
    m_textEntered->setColor(color);    
       
    }
    
    void TextInput::onMove(const sf::Vector2f& delta){
    m_background.setPosition(delta);
    m_highLight.setPosition(delta);
    m_description->setPosition(delta);
    
    }
    
    void TextInput::majTextEntered()
    {
    
    }
    
   
    
    void TextInput::drawMyself(sf::RenderTarget& target, sf::RenderStates states) const 
    {
        
        target.draw(m_textEntered);
        target.draw(m_highLight);
           
    }
    
    TextInput::~TextInput(){}
	
	
	
	
	
}