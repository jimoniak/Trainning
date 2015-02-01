
#include "gui_window.hpp"
#include <string>

namespace gui
{
	
	
	Window::Window()	
	{}
	
	Window::Window(sf::Vector2f size,sf::String title ,sf::Color color):
	m_title(addChild(std::make_unique<gui::Text>()))
	{
		m_titlte->setString(title);
		m_background.setSize(size);
		m_background.setFillColor(color);
		
		
	}
	Window::~Window(){}
	
	
	
	void Window::onMouseEnter(){}
    void Window::onMouseExit(){}
	void Window::drawMyself(sf::RenderTarget& target, sf::RenderStates states) const {}
	
	
	
	
	
	
	
	
}