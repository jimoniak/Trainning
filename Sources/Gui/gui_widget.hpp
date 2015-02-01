/**
 * \file gui_widget.hpp
 * \brief Fichier contenant la class Widget
 * \author J. PEAULT & Q. PUBERT
 * \version 0.1
 * \date 01 fevrier 2015
 *
 *  La classe Widget est le point de départ du gui. tout element de gui hérite de cette classe.
 */


#ifndef WIDGET
#define WIDGET


#include <SFML/Graphics.hpp>
#include <vector>

namespace gui
{

class Widget
: public sf::Drawable
{
public:
    Widget(Widget* parent = nullptr);


    sf::Vector2f getGlobalPosition() const ;

    sf::FloatRect getGlobalBounds() const ;

    sf::Vector2f getLocalPosition() const ;
    sf::FloatRect getLocalBounds() const ;

    bool contains(const sf::Vector2f& p) const ;

    Widget* addChild(Widget* childPtr);

    void setParent(Widget* newParent) ;

    void move(const sf::Vector2f& delta);

    void setPosition(const sf::Vector2f& newPos);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const ;

    void onMove(const sf::Vector2f& delta) ;

    void onClick(sf::Vector2f mousePos) ;

    virtual void onMouseEnter();
    virtual void onMouseExit() ;

    virtual ~Widget();

protected:
    WidgetPtr abandonChild(Widget* childPtr) ;



      virtual void drawMyself(sf::RenderTarget& target, sf::RenderStates states) const;

    std::vector<WidgetPtr> m_children;
    Widget* m_parent;
    sf::FloatRect m_bounds;

    bool m_active;/*<! Si l'element est utilisable>*/
};

}

#endif
