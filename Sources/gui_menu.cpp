
#include <SFML/Graphics.hpp>
#include <LimbGUI/GUI.hpp>
#include "constantes.hpp"

#include "affichable.hpp"
#include "gui_menu.hpp"


#include <iostream>



GUI_menu::GUI_menu(RessourceLoader *rsholder,sf::RenderWindow *window) :
    m_serverName( m_font, sf::Vector2f(250,30), sf::Vector2f( LFENETRE/2-125, HFENETRE/2 - 50), sf::Color::Red ,sf::Color::Green),
    m_port( m_font, sf::Vector2f(125,30), sf::Vector2f( LFENETRE/2-125, HFENETRE/2 + 50), sf::Color::Red ,sf::Color::Green)
{
	//Création de la fenetre:
	m_window = window; // new sf::RenderWindow(sf::VideoMode(LFENETRE, HFENETRE), L"Trainning Réseau!");
	if(!m_font.loadFromFile("Ressources/GUI/Font/Timeless.ttf")) std::cerr<<" Erreur de chargement de la police!"<<std::endl;

	m_pageMenu = 0;

	//Page 0:
	 m_fond.setFillColor(sf::Color::Blue);
	 m_fond.setSize(sf::Vector2f(LFENETRE,HFENETRE));

		//Boutons
		m_server =  lgui::Bouton(m_font,rsholder->getTexGUI(0),rsholder->getTexGUI(1));
		m_client =  lgui::Bouton(m_font,rsholder->getTexGUI(0),rsholder->getTexGUI(1));
		m_quitter = lgui::Bouton(m_font,rsholder->getTexGUI(0),rsholder->getTexGUI(1));

		m_server.setPosition(sf::Vector2f(LFENETRE / 2 - rsholder->getTexGUI(0)->getSize().x / 2 ,HFENETRE / 2 - 100));
		m_client.setPosition(sf::Vector2f(LFENETRE / 2 - rsholder->getTexGUI(0)->getSize().x / 2 ,HFENETRE / 2 ));
		m_quitter.setPosition(sf::Vector2f(LFENETRE / 2 - rsholder->getTexGUI(0)->getSize().x / 2 ,HFENETRE / 2 + 100));

		m_server.setFenetrelie(*m_window);
		m_client.setFenetrelie(*m_window);
		m_quitter.setFenetrelie(*m_window);

		m_server.setTitre("Serveur");
		m_client.setTitre("Client");
		m_quitter.setTitre("Quitter");

		m_server.setTailleTexte(15);
		m_client.setTailleTexte(15);
		m_quitter.setTailleTexte(15);

	//Page 1:

        //Textes

         m_textServerName.setFont(m_font);
         m_textServerName.setCharacterSize(15);
         m_textServerName.setColor(sf::Color::Green);
         m_textServerName.setString(L"Veuillez entrer le nom de votre serveur:");
         m_textServerName.setPosition(LFENETRE/2 - m_textServerName.getGlobalBounds().width / 2 , HFENETRE / 2 - 100);
		 m_textport.setFont(m_font);
         m_textport.setCharacterSize(15);
         m_textport.setColor(sf::Color::Green);
         m_textport.setString(L"Veuillez entrer le port d'écoute du serveur:");
         m_textport.setPosition(LFENETRE/2 - m_textServerName.getGlobalBounds().width / 2 , HFENETRE / 2 );

		//Boutons
		m_back = lgui::Bouton(m_font,rsholder->getTexGUI(0),rsholder->getTexGUI(1));
		m_back.setPosition(sf::Vector2f(LFENETRE  - (rsholder->getTexGUI(0)->getSize().x + 30 )  ,HFENETRE  - 100 ));
		m_back.setFenetrelie(*m_window);
		m_back.setTitre("Retour");
		m_back.setTailleTexte(15);

		//Zones de Saisie

         // m_serverName = new lgui::ZoneSaisie( m_font, sf::Vector2f(250,30), sf::Vector2f( LFENETRE/2-125, HFENETRE/2 - 50), sf::Color::Green ,sf::Color::Blue);
         // m_port = new lgui::ZoneSaisie( m_font, sf::Vector2f(250,30), sf::Vector2f( LFENETRE/2-125, HFENETRE/2 + 50), sf::Color::Green ,sf::Color::Blue);
         m_serverName.setFont(m_font);
         m_port.setFont(m_font);
          m_serverName.setFenetrelie(*m_window);
          m_port.setFenetrelie(*m_window);

}

GUI_menu::~GUI_menu()
{
}

void GUI_menu::gererSaisie(sf::Event *evt)
{

           if(m_pageMenu==1)
            {
                m_serverName.actif(*evt);
                m_port.actif(*evt);
            }

}

void GUI_menu::ouvrir()
{

	switch(m_pageMenu)
	{
	case 0:
	    if(m_server.actionner())  m_pageMenu = 1;
        if(m_client.actionner())   m_pageMenu = 2;
        if(m_quitter.actionner())  m_window->close();
	break;
	case 1:
	     if(m_back.actionner())  m_pageMenu = 0;
	break;
	case 2:
         if(m_back.actionner())  m_pageMenu = 0;
	default:
	break;
	}


}

bool GUI_menu::display()
{


	if(m_open)
	{
		switch(m_pageMenu)
		{
			case 0:
			m_window->draw(m_fond);
			m_server.afficher();
			m_client.afficher();
			m_quitter.afficher();
			break;
			case 1:
			m_window->draw(m_fond);
			m_window->draw(m_textServerName);
			m_serverName.afficher();
			m_window->draw(m_textport);
			m_port.afficher();
			m_back.afficher();
			break;
			case 2:
            m_window->draw(m_fond);
			m_back.afficher();
			default:
			break;


		}

	}

	//m_window->display();
	return true;

}
