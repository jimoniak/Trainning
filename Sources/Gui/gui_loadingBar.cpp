
#include "gui_loadingBar.hpp"


namespace gui
{
	LoadingBar(){}
     LoadingBar(sf::Vector2f size,
				std::string descr,
				float MAX,float MIN,
				sf::Color clrBack ,
				sf::Color clrFore ) :
                    m_description(addChild(std::make_unique<gui::Text>())),
                    m_count(addChild(std::make_unique<gui::Text>()))
     {
         m_background.setSize(size);
         m_foreground.setSize(size);
         
         m_description.setString(descr);
         m_MAX = MAX;
         m_MIN=  MIN;
         
         m_background.setFillColor(clrBlack);
         m_foreground.setFillColor(clrFore);
         
        
     }
	 
	 
    ~LoadingBar(){}
	
	
	
	
	
	
	
}