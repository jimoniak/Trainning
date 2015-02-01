
#include "gui_widget.hpp"

namespace gui
{

using WidgetPtr = std::unique_ptr<Widget>;


    Widget::Widget(Widget* parent)
    : m_parent(parent)
    {}

    sf::Vector2f Widget::getGlobalPosition() const {
        return (m_parent) ? m_parent->getGlobalPosition() + getLocalPosition() : {0.0f, 0.0f};
    }
    
    sf::FloatRect Widget::getGlobalBounds() const {
       // return (
    }
    
    sf::Vector2f Widget::getLocalPosition() const { return {m_bounds.left, m_bounds.top}; }
    sf::FloatRect Widget::getLocalBounds() const { return m_bounds; }
    
    bool Widget::contains(const sf::Vector2f& p) const {
        return (m_bounds.left <= p.x)
            && (p.x <= m_bounds.left + m_bounds.width)
            && (m_bounds.top <= p.y)
            && (p.y <= m_bounds.top + m_bounds.height);
    }

    Widget* Widget::addChild(Widget* childPtr) {
        if (childPtr == this) return;
        
        m_children.emplace_back(childPtr->m_parent->abandonChild(childPtr));
        childPtr->m_parent = this;
        computeBounds();
    }
   
    void Widget::setParent(Widget* newParent) {
        newParent->addChild(this);
    }

    void Widget::move(const sf::Vector2f& delta) {
        m_bounds.left += delta.x;
        m_bounds.top += delta.y;
        onMove(delta);
        
        if (m_parent) {        
            m_parent->computeBounds();
        }
    }
    
    void Widget::setPosition(const sf::Vector2f& newPos) {
        move(newPos - getPosition());
    }
    
    void Widget::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        drawMyself(target, states);
        states.transform.translate(getPosition());
        for (const auto& childPtr : m_children) {
            target.draw(*childPtr, states);
        }
    }
    
    void Widget::onMove(const sf::Vector2f& delta) {
        onMyMove();
    }
    
    void Widget::onClick(sf::Vector2f mousePos) {
        for (auto childPtrIt = m_children.rbegin(), end = m_children.rend(); childPtrIt != end; ++childPtrIt) {
            if (*childPtrIt->contains(mousePos)) {
                mousePos -= *childPtrIt->getPosition();
                *childPtrIt->onClick();
                return;
            }
        }
        
        Widget::onMyClick(){}
    }
    
    void Widget::onMouseEnter() {}
    void Widget::onMouseExit() {}
    
     Widget::~Widget(){}
    

    WidgetPtr Widget::abandonChild(Widget* childPtr) {
        childPtr->m_parent = nullptr;
        auto childIt = std::find(m_children.begin(), m_children.end(), childPtr);
        if (childIt != m_children.end()) {
            m_children.erase(childIt);
            computeBounds();
            return childPtr;
        }
        
        return nullptr;
    }
	
    /*
    void Widget::computeBounds(sf::FloatRect basicBounds) {
        for (auto& childPtr : m_children) {
            const auto childBounds = childPtr.getGlobalBounds();
            childBounds.left += 
            const float right = std::max(childBounds.left + childBounds.width, basicBounds.left + basicBounds.width);
            const float bottom = std::max(childBounds.top + childBounds.height, basicBounds.top + basicBounds.height);
            basicBounds.left = std::min(basicBounds.left, childBounds.left);
            basicBounds.top = std::min(basicBounds.top, childBounds.top);
            basicBounds.width = right - basicBounds.left;
            basicBounds.height = bottom - basicBounds.top;
        }
    }*/

     void Widget::onMyMove() {}
     void Widget::drawMyself(sf::RenderTarget& target, sf::RenderStates states) const {}
    
    

}