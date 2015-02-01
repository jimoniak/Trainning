
#include <SFML/Graphics.hpp>
#include <vector>


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

    sf::Vector2f getGlobalPosition() const {
        return (m_parent) ? m_parent->getGlobalPosition() + getLocalPosition() : {0.0f, 0.0f};
    }
    
    sf::FloatRect getGlobalBounds() const {
        return (
    }
    
    sf::Vector2f getLocalPosition() const { return {m_bounds.left, m_bounds.top}; }
    sf::FloatRect getLocalBounds() const { return m_bounds; }
    
    bool contains(const sf::Vector2f& p) const {
        return (m_bounds.left <= p.x)
            && (p.x <= m_bounds.left + m_bounds.width)
            && (m_bounds.top <= p.y)
            && (p.y <= m_bounds.top + m_bounds.height);
    }

    Widget* addChild(Widget* childPtr) {
        if (childPtr == this) return;
        
        m_children.emplace_back(childPtr->m_parent->abandonChild(childPtr));
        childPtr->m_parent = this;
        computeBounds();
    }
   
    void setParent(Widget* newParent) {
        newParent->addChild(this);
    }

    void move(const sf::Vector2f& delta) {
        m_bounds.left += delta.x;
        m_bounds.top += delta.y;
        onMove(delta);
        
        if (m_parent) {        
            m_parent->computeBounds();
        }
    }
    
    void setPosition(const sf::Vector2f& newPos) {
        move(newPos - getPosition());
    }
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        drawMyself(target, states);
        states.transform.translate(getPosition());
        for (const auto& childPtr : m_children) {
            target.draw(*childPtr, states);
        }
    }
    
    void onMove(const sf::Vector2f& delta) {
        onMyMove();
    }
    
    void onClick(sf::Vector2f mousePos) {
        for (auto childPtrIt = m_children.rbegin(), end = m_children.rend(); childPtrIt != end; ++childPtrIt) {
            if (*childPtrIt->contains(mousePos)) {
                mousePos -= *childPtrIt->getPosition();
                *childPtrIt->onClick();
                return;
            }
        }
        
        onMyClick();
    }
    
    virtual void onMouseEnter() {}
    virtual void onMouseExit() {}
    
    virtual ~Widget();
    
protected:
    WidgetPtr abandonChild(Widget* childPtr) {
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
    void computeBounds(sf::FloatRect basicBounds) {
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

    virtual void onMyMove() {}
    virtual void drawMyself(sf::RenderTarget& target, sf::RenderStates states) const {}
    
    std::vector<WidgetPtr> m_children;
    Widget* m_parent;
    sf::FloatRect m_bounds;
  
    bool m_active;/*<! Si l'element est utilisable>*/
};

class Text : public Widget
{
    public:
    void setFont(const sf::Font &font){
        m_text.setFont(font);
    }
    void setString(const sf::String& str){
        m_text.setString(str);
    }
    void setCharacterSize(int size){
        m_text.setCharacterSize(size);
    }
    void setColor(const sf::Color color){
        m_text.setColor(color);
    }

    void onMove(const sf::Vector2f& delta){
    m_text.setPosition(delta);
    
    }
    void drawMyself(sf::RenderTarget& target, sf::RenderStates states) const 
    {target.draw(m_text);
    }
    private:
    sf::Text m_text;
};


class Button : public Widget
{
    public:
     Button() : m_text(addChild(std::make_unique<gui::Text>()))
     {
     
     }
    
    void setTexture(const sf::Texture &texture)
    {
        m_sprite.setTexture(texture);
        m_bounds = texture.getGlobalBound();    
    
    }
    
    template <typename F>
    void setOnClick(F f) { // button.setOnClick([&menu] { menu.open(); });
        m_onClickFunction = std::move(f);
    }
    
    virtual void onMyClick() override {
        if (m_onClickFunction) {
            m_onClickFunction();
        }
    }
    
    void onMove(const sf::Vector2f& delta){
     m_sprite.setPosition(delta);
     m_highlight.setposition(delta);
   }
    
    ~Button();
    
    void setText(sf::Font &font,std::string str = "Titre",int characterSize = 10,sf::Color color = sf::Color::Black){
    
    m_text->setFont(font);
    m_text->setString(str);
    m_text->setCharacterSize(characterSize);
    m_text->setColor(color);    
    }  
    
    void drawMyself(sf::RenderTarget& target, sf::RenderStates states) const 
    {
       
        target.draw(m_sprite);
        target.draw(m_highLight);
            }
    
    private:
    gui::Text *m_text;
    
    sf::RectangleShape m_highLight;
    sf::Sprite   m_sprite;
    std::function<void()> m_onClickFunction;


};

class TextInput : public Widget
{
    public:
    std::string getTextEntered(){
    return m_textEntered;
    }
     TextInput();
     TextInput(sf::Vector2u size,std::string charset = "1234567890",sf::Color color=sf::Color::Green):
     m_description(addChild(std::make_unique<gui::Text>())){
     m_background.setSize(size);
     m_highLight.setSize(size);
     m_charset = charset;     
     m_background.setFillColor(color);
     m_highLight.setFillColor(sf::Color(125,125,125,125));   
     }
     
     void setDescription(sf::Font &font,std::string str = "Titre",int characterSize = 10,sf::Color color = sf::Color::Black){
    
    m_description->setFont(font);
    m_description->setString(str);
    m_description->setCharacterSize(characterSize);
    m_description->setColor(color);    
    }
    void setTextEntered(sf::Font &font,std::string str = "Renseignez ici",int characterSize = 10,sf::Color color = sf::Color::Black){
    
    m_textEntered->setFont(font);
    m_textEntered->setString(str);
    m_textEntered->setCharacterSize(characterSize);
    m_textEntered->setColor(color);    
       
    }
    
    void onMove(const sf::Vector2f& delta){
    m_background.setPosition(delta);
    m_highLight.setPosition(delta);
    m_description->setPosition(delta);
    
    }
    
    void majTextEntered()
    {
    
    }
    
   
    
    void drawMyself(sf::RenderTarget& target, sf::RenderStates states) const 
    {
        
        target.draw(m_textEntered);
        target.draw(m_highLight);
           
    }
    
    ~TextInput();
    
    
    
    
    private:
    sf::RectangleShape m_background;
    sf::RectangleShape m_highLight;
    std::string m_charset;
    gui::Text *m_description;   /*<! Phrase expliquant ce que la zone de saisie attend */
    sf::Text m_textEntered; /*<! texte entré dans la zone de saisie*/
    
     

};

class LoadingBar : public Widget
{

    public:
     LoadingBar(){}
     LoadingBar(sf::Vector2f size,
				std::string descr,
				float MAX,float MIN=0,
				sf::Color clrBack = sf::Color::Blue,
				sf::Color clrFore = sf::Color::White) :
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



    private:

    sf::RectangleShape m_background;
    sf::RectangleShape m_foreground;
    float m_MIN;
    float m_MAX;
    gui::Text *m_description;
    gui::Text *m_count;

};
}