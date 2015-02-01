
#ifndef LOADING_BAR
#define LOADING_BAR

#include "gui_text.hpp"

namespace gui
{

class LoadingBar : public Widget
{

    public:
     LoadingBar();
     LoadingBar(sf::Vector2f size,
				std::string descr,
				float MAX,float MIN=0,
				sf::Color clrBack = sf::Color::Blue,
				sf::Color clrFore = sf::Color::White);
	 
	 
    ~LoadingBar();



    private:

    sf::RectangleShape m_background;
    sf::RectangleShape m_foreground;
    float m_MIN;
    float m_MAX;
    gui::Text *m_description;
    gui::Text *m_count;

};




}
#endif