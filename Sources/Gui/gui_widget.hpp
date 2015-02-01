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

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include <vector>

#include "../make_unique.hpp"

namespace gui
{

using WidgetPtr = std::unique_ptr<Widget>;

class Widget : public sf::Drawable
{

    public:
    Widget(Widget* parent = nullptr);


    sf::Vector2f getLocalPosition() const ;
    sf::FloatRect getLocalBounds() const ;

    sf::Vector2f getGlobalPosition() const ;

    sf::FloatRect getGlobalBounds() const ;

    bool contains(const sf::Vector2f& p) const ;

    template <typename WidgetType>
   WidgetType* addChild(std::unique_ptr<WidgetType> childPtr) {
        if (childPtr.get() == this) return nullptr;

        const auto ret = childPtr.get();
        childPtr->m_parent = this;
        m_children.emplace_back(std::move(childPtr));

        return ret;
    }

    void setParent(Widget* newParent) ;

    void move(const sf::Vector2f& delta) ;

    void setPosition(const sf::Vector2f& newPos) ;

    void setSize(const sf::Vector2f& s) ;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const final override ;

    void onPush(sf::Mouse::Button button) ;

    void onRelease(sf::Mouse::Button button) ;

    void checkHover(sf::Vector2f pos) ;

    void onHover() ;

    void onEnter() ;

    void onExit() ;

    virtual ~Widget();

protected:

    static Widget* s_selected;

    WidgetPtr abandonChild(Widget* childPtr) ;

    virtual void onTextInput(sf::Uint32 c);
    virtual void onMyHover();
    virtual void onMyPush(sf::Mouse::Button button);
    virtual void onMyRelease(sf::Mouse::Button button);
    virtual void onMyEnter();
    virtual void onMyExit();
    virtual void onMyClick(sf::Mouse::Button button);
    virtual void drawMyself(sf::RenderTarget& target, sf::RenderStates states) const ;

    std::vector<WidgetPtr> m_children;
    Widget* m_parent;
    sf::FloatRect m_bounds;

    bool m_active  = true;/*<! Si l'element est utilisable>*/
    bool m_mouseIn = false;
    bool m_pushed  = false;
};

}

#endif
