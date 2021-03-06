
#include "ressourceLoader.hpp"
#include "carte.hpp"


Map::Map()
{



}

Map::Map(sf::Vector2f size,sf::RenderWindow *window)
{
    m_size = size;
    m_window = window;


}

Map::~Map(){}



 void Map::createMap(RessourceLoader &rsholder)
 {
     sf::Image   m_imageCarte;
     sf::Image   m_imageTile;

     m_imageTile = rsholder.getTexTile(0)->copyToImage();

     m_imageCarte.create (m_size.x * m_imageTile.getSize().x,m_size.y * m_imageTile.getSize().y); //creation du support en memoire o� blitter les tiles.
     m_imageCarte.createMaskFromColor(sf::Color::Black);

     for(unsigned int j=0; j<m_size.y; j++)
    {
        for(unsigned int i=0; i<m_size.x; i++)
        {
            m_imageCarte.copy(m_imageTile,i*m_imageTile.getSize().x,j*m_imageTile.getSize().y,sf::IntRect(0, 0, 0, 0),true); //Copie des tiles sur le support,

        }


    }

        m_texture.loadFromImage(m_imageCarte);
        m_texture.setSmooth(true);
        m_apparence.setTexture(m_texture);

 }

 bool Map::display()
 {

     m_window->draw(m_apparence);
     return true;

 }

 //GETTER

 sf::Vector2f Map::getSize()
 {
     return m_size;
 }
