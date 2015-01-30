


#ifndef ELEMENT_GUI
#define ELEMENT_GUI

#define DllExport   __declspec(dllexport)

#include <SFML/Graphics.hpp>

namespace lgui
{

    class DllExport ElementGUI
    {
        static int compteur;
        friend class ManagerGUI;

        protected:

        sf::Texture     *m_Texture;
        sf::Texture       m_texture;
        sf::Texture      *m_textureOn;
        sf::Texture       m_texturOn;
        sf::Image m_fond;
        sf::Image m_fondOn;

        sf::RenderWindow *m_fenetre;

        sf::Sprite         m_apparence;

        sf::Vector2f     m_position;
        sf::Vector2f      m_taille;//taille de la Texture pointé par *m_Texture

        int                  m_priorite;
        bool               m_cliquable;
        bool               m_selectionnable;
        sf::Vector2f      positionSouris;

        bool                m_actif ;


        public:
        void setFenetrelie(sf::RenderWindow &fenetre);
        virtual void  afficher();
        virtual void  activer();
        virtual bool  actif();
        virtual bool estDessus();

        //getter
        sf::Vector2f getPosition();
        bool estSelectionnable();

        //setter
         void setTexture();
         void setPosition(sf::Vector2f position);
         void setPosition(int positionx,int positiony);
         void setCliquable(bool cliquable);
                       ElementGUI();
          virtual ~ElementGUI();
    } ;


}


#endif // ELEMENT_GUI
