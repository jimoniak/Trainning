#ifndef WINDOW
#define WINDOW

#include "gui_button.hpp"

namespace gui
{
	
	
class Window : public Widget
{
	public:
	 Window();
	 Window(sf::Vector2f size,std::title = "window",sf::Color color = sf::Color blue);
	~Window();
	
	
	
	void onMouseEnter();
    void onMouseExit() ;
	void drawMyself(sf::RenderTarget& target, sf::RenderStates states) const ;
	void onMyMove() ;
	
	private:
	
	sf::RectangleShape m_background;/*<! fond de la fenetre>*/
	
	
	
	gui::Text   *m_title;
	gui::Button *m_close;
	
	
};



}

#endif