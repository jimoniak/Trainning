
#include "gui_loadingBar.hpp"


namespace gui
{
	 LoadingBar::LoadingBar(){}
     LoadingBar::LoadingBar(sf::Vector2f size,
				std::string descr,
				float MAX,float param ,
				sf::Color clrBack,
				sf::Color clrFore,
				float MIN) :
                    m_description(addChild(std::make_unique<gui::Text>())),
                    m_count(addChild(std::make_unique<gui::Text>()))
     {
         m_background.setSize(size);
         m_foreground.setSize(size);
         
         m_description.setString(descr);
         m_MAX = MAX;
		 m_param = param;
         m_MIN=  MIN;
         
         m_background.setFillColor(clrBlack);
         m_foreground.setFillColor(clrFore);
         
        
     }
	 
	void LoadingBar::setSize(sf::Vector2f newSize){
		m_background.setSize(newSize);
		m_foreground.setSize(newSize);
		
		m_bounds = m_background.getGlobalBounds();
		
		
	}
	void LoadingBar::setBackColor(sf::Color color){
		m_background.setFillColor(color);
		
	}
	void LoadingBar::setForeColor(sf::Color color){
		m_foreground.setFillColor(color);
		
	}
	
	void LoadingBar::setMax(float MAX){
		m_MAX = MAX;
	}
	void LoadingBar::setMin(float MIN){
		m_MIN = MIN;
	}
	void LoadingBar::majParam(float actuParam){
		
		m_param = actuParam;
		
		float multiplier = (m_param * 100) / m_MAX;
		m_foreground.setSize(m_background.getSize().x * multiplier,m_foreground.getSize().y);
		
	}
	 
	 
    ~LoadingBar(){}
	
	
	
	
	
	
	
}