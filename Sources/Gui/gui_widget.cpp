
#include "gui_widget.hpp"

namespace gui
{

using WidgetPtr = std::unique_ptr<Widget>;
Widget* Widget::s_selected = nullptr;


    Widget::Widget(Widget* parent)
    : m_parent(parent)
    {}

    sf::Vector2f Widget::getLocalPosition() const { return {m_bounds.left, m_bounds.top}; }
    sf::FloatRect Widget::getLocalBounds() const { return m_bounds; }

    sf::Vector2f Widget::getGlobalPosition() const {
        return (m_parent) ? m_parent->getGlobalPosition() + getLocalPosition() : getLocalPosition();
    }

    sf::FloatRect Widget::getGlobalBounds() const {
        const sf::Vector2f globalPos = getGlobalPosition();

        sf::FloatRect globalBounds = m_bounds;
        globalBounds.left += globalPos .x;
        globalBounds.top += globalPos .y;

        return globalBounds;
    }

    bool Widget::contains(const sf::Vector2f& p) const {
        return (m_bounds.left <= p.x)
            && (p.x <= m_bounds.left + m_bounds.width)
            && (m_bounds.top <= p.y)
            && (p.y <= m_bounds.top + m_bounds.height);
    }

    

    void Widget::setParent(Widget* newParent) {
        newParent->addChild((m_parent) ? m_parent->abandonChild(this) : WidgetPtr{this});
    }

    void Widget::move(const sf::Vector2f& delta) {
        m_bounds.left += delta.x;
        m_bounds.top += delta.y;
    }

    void Widget::setPosition(const sf::Vector2f& newPos) {
        m_bounds.left = newPos.x;
        m_bounds.top = newPos.y;
    }

    void Widget::setSize(const sf::Vector2f& s) {
        m_bounds.width = s.x;
        m_bounds.height = s.y;
    }

    void Widget::draw(sf::RenderTarget& target, sf::RenderStates states) const final override {
        drawMyself(target, states);
        states.transform.translate(getLocalPosition());
        for (const auto& childPtr : m_children) {
            target.draw(*childPtr, states);
        }
    }

    void Widget::onPush(sf::Mouse::Button button) {
        for (auto childPtrIt = m_children.rbegin(), end = m_children.rend(); childPtrIt != end; ++childPtrIt) {
            if ((*childPtrIt)->m_mouseIn) {
                (*childPtrIt)->onPush(button);
                return;
            }
        }

        m_pushed = true;
        onMyPush(button);
    }

    void Widget::onRelease(sf::Mouse::Button button) {
        for (auto childPtrIt = m_children.rbegin(), end = m_children.rend(); childPtrIt != end; ++childPtrIt) {
            if ((*childPtrIt)->m_mouseIn) {
                (*childPtrIt)->onRelease(button);
                return;
            }
        }

        if (m_pushed) {
            m_pushed = false;
            onMyClick(button);
        }
        onMyRelease(button);
    }

    void Widget::checkHover(sf::Vector2f pos) {
        if (contains(pos)) {
            onHover();

            if (!m_mouseIn) {
                onEnter();
            }

            for (auto& childPtr : m_children) {
                childPtr->checkHover(pos - getLocalPosition());
            }
        } else {
            if (m_mouseIn) {
                onExit();

                for (auto childPtrIt = m_children.rbegin(), end = m_children.rend(); childPtrIt != end; ++childPtrIt) {
                    if ((*childPtrIt)->m_mouseIn) {
                        (*childPtrIt)->onExit();
                        return;
                    }
                }
            }
        }
    }

    void Widget::onHover() {
        onMyHover();
    }

    void Widget::onEnter() {
        m_mouseIn = true;
        onMyEnter();
    }

    void Widget::onExit() {
        m_mouseIn = false;
        m_pushed = false;
        onMyExit();
    }

    Widget::~Widget(){}
	
	WidgetPtr Widget::abandonChild(Widget* childPtr) {
        childPtr->m_parent = nullptr;
        auto childIt = std::find_if(m_children.begin(), m_children.end(),
                                    [childPtr] (const WidgetPtr& wptr) { return wptr.get() == childPtr; });
        if (childIt != m_children.end()) {
            m_children.erase(childIt);
            return WidgetPtr(childPtr);
        }

        return nullptr;
    }

    void Widget::onTextInput(sf::Uint32 c);
    void Widget::onMyHover() {}
    void Widget::onMyPush(sf::Mouse::Button button) {}
    void Widget::onMyRelease(sf::Mouse::Button button) {}
    void Widget::onMyEnter() {}
    void Widget::onMyExit() {}
    void Widget::onMyClick(sf::Mouse::Button button) {}
    void Widget::drawMyself(sf::RenderTarget& target, sf::RenderStates states) const {}

    
    

}