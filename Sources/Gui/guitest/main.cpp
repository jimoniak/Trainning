#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>

#include <memory>
#include <vector>

namespace std {

template <typename T, typename... Args>
unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>{new T{std::forward<Args>(args)...}};
}

}

namespace gui
{

class Widget;

using WidgetPtr = std::unique_ptr<Widget>;

class Widget
: public sf::Drawable
{
public:
    Widget(Widget* parent = nullptr)
    : m_parent(parent)
    {
    }

    sf::Vector2f getLocalPosition() const { return {m_bounds.left, m_bounds.top}; }
    sf::FloatRect getLocalBounds() const { return m_bounds; }

    sf::Vector2f getGlobalPosition() const {
        return (m_parent) ? m_parent->getGlobalPosition() + getLocalPosition() : getLocalPosition();
    }

    sf::FloatRect getGlobalBounds() const {
        const sf::Vector2f globalPos = getGlobalPosition();

        sf::FloatRect globalBounds = m_bounds;
        globalBounds.left += globalPos .x;
        globalBounds.top += globalPos .y;

        return globalBounds;
    }

    bool contains(const sf::Vector2f& p) const {
        return (m_bounds.left <= p.x)
            && (p.x <= m_bounds.left + m_bounds.width)
            && (m_bounds.top <= p.y)
            && (p.y <= m_bounds.top + m_bounds.height);
    }

    template <typename WidgetType>
    WidgetType* addChild(std::unique_ptr<WidgetType> childPtr) {
        if (childPtr.get() == this) return nullptr;

        const auto ret = childPtr.get();
        childPtr->m_parent = this;
        m_children.emplace_back(std::move(childPtr));

        return ret;
    }

    void setParent(Widget* newParent) {
        newParent->addChild((m_parent) ? m_parent->abandonChild(this) : WidgetPtr{this});
    }

    void move(const sf::Vector2f& delta) {
        m_bounds.left += delta.x;
        m_bounds.top += delta.y;
    }

    void setPosition(const sf::Vector2f& newPos) {
        m_bounds.left = newPos.x;
        m_bounds.top = newPos.y;
    }

    void setSize(const sf::Vector2f& s) {
        m_bounds.width = s.x;
        m_bounds.height = s.y;
    }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const final override {
        drawMyself(target, states);
        states.transform.translate(getLocalPosition());
        for (const auto& childPtr : m_children) {
            target.draw(*childPtr, states);
        }
    }

    void onPush(sf::Mouse::Button button) {
        for (auto childPtrIt = m_children.rbegin(), end = m_children.rend(); childPtrIt != end; ++childPtrIt) {
            if ((*childPtrIt)->m_mouseIn) {
                (*childPtrIt)->onPush(button);
                return;
            }
        }

        m_pushed = true;
        onMyPush(button);
    }

    void onRelease(sf::Mouse::Button button) {
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

    void checkHover(sf::Vector2f pos) {
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

    void onHover() {
        onMyHover();
    }

    void onEnter() {
        m_mouseIn = true;
        onMyEnter();
    }

    void onExit() {
        m_mouseIn = false;
        m_pushed = false;
        onMyExit();
    }

    virtual ~Widget(){}

protected:
    static Widget* s_selected;

    WidgetPtr abandonChild(Widget* childPtr) {
        childPtr->m_parent = nullptr;
        auto childIt = std::find_if(m_children.begin(), m_children.end(),
                                    [childPtr] (const WidgetPtr& wptr) { return wptr.get() == childPtr; });
        if (childIt != m_children.end()) {
            m_children.erase(childIt);
            return WidgetPtr(childPtr);
        }

        return nullptr;
    }

    virtual void onTextInput(sf::Uint32 c);
    virtual void onMyHover() {}
    virtual void onMyPush(sf::Mouse::Button button) {}
    virtual void onMyRelease(sf::Mouse::Button button) {}
    virtual void onMyEnter() {}
    virtual void onMyExit() {}
    virtual void onMyClick(sf::Mouse::Button button) {}
    virtual void drawMyself(sf::RenderTarget& target, sf::RenderStates states) const {}

    std::vector<WidgetPtr> m_children;
    Widget* m_parent;
    sf::FloatRect m_bounds;

    bool m_active = true;/*<! Si l'element est utilisable>*/
    bool m_mouseIn = false;
    bool m_pushed = false;
};

Widget* Widget::s_selected = nullptr;

class Text
: public Widget
, public sf::Text
{
public:
    void drawMyself(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        target.draw(m_text, states);
    }

private:
    sf::Text m_text;
};


class Button
: public Widget
{
public:
    Button()
    : m_text(addChild(std::make_unique<gui::Text>()))
    {

    }

    void setTexture(const sf::Texture &texture) {
        m_sprite.setTexture(texture);
        setSize(sf::Vector2f{texture.getSize()});
    }

    template <typename F>
    void setOnClick(F f) { // button.setOnClick([&menu] { menu.open(); });
        m_onClickFunction = std::forward(f);
    }

    virtual void onMyClick(sf::Mouse::Button button) override {
        if (m_onClickFunction) {
            m_onClickFunction();
        }
    }

    ~Button(){}

    Text& getText() {
        return *m_text;
    }

    virtual void drawMyself(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(m_sprite, states);
        target.draw(m_highLight, states);
    }

private:
    gui::Text *m_text;

    sf::RectangleShape m_highLight;
    sf::Sprite m_sprite;
    std::function<void()> m_onClickFunction;
};

class TextInput
: public Widget
{
public:
    sf::String getString() const{
        return m_text->getString();
    }

    TextInput(const sf::Vector2f& size,
              sf::String charset = L"1234567890",
              sf::Color color = sf::Color::Green)
    : m_description(addChild(std::make_unique<gui::Text>()))
    , m_text(addChild(std::make_unique<gui::Text>()))
    , m_background(size)
    , m_highLight(size)
    , m_charset(charset)
    {
        m_background.setFillColor(color);
        m_highLight.setFillColor({125u, 125u, 125u, 125u});
    }

    gui::Text& getDescription() {
        return *m_description;
    }

    gui::Text& getText() {
        return *m_text;
    }

    void majTextEntered()
    {

    }

    void drawMyself(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(m_highLight, states);
    }

    ~TextInput() = default;

private:
    sf::RectangleShape m_background;
    sf::RectangleShape m_highLight;
    sf::String m_charset;
    gui::Text *m_description;   /*<! Phrase expliquant ce que la zone de saisie attend */
    gui::Text *m_text; /*<! texte entré dans la zone de saisie*/
};

class LoadingBar : public Widget
{

    public:
     LoadingBar(){}
     LoadingBar(sf::Vector2f size,
                sf::String descr,
                float MAX,float MIN=0,
                sf::Color clrBack = sf::Color::Blue,
                sf::Color clrFore = sf::Color::White)
    : m_description(addChild(std::make_unique<gui::Text>()))
    , m_count(addChild(std::make_unique<gui::Text>()))
    {
        m_background.setSize(size);
        m_foreground.setSize(size);

        m_description->setString(descr);
        m_MAX = MAX;
        m_MIN=  MIN;

        m_background.setFillColor(clrBack);
        m_foreground.setFillColor(clrFore);
    }

    ~LoadingBar() = default;

private:
    sf::RectangleShape m_background;
    sf::RectangleShape m_foreground;
    float m_MIN;
    float m_MAX;
    gui::Text *m_description;
    gui::Text *m_count;
};

}

int main() {
    sf::RenderWindow window(sf::VideoMode(800u, 600u), "GUI Tests");
    window.setVerticalSyncEnabled(true);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        gui::Button btest;


        window.clear();
        window.display();
    }
}
