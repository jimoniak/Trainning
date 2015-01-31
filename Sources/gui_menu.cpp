
#include <SFML/Graphics.hpp>
#include <LimbGUI/GUI.hpp>
#include "constantes.hpp"

#include "affichable.hpp"
#include "gui_menu.hpp"
#include <iostream>

//Commentaire test pour Github

GUI_menu::GUI_menu(RessourceLoader *rsholder,
                   sf::RenderWindow *window)
    : m_serverName(m_font,
                   {250.0f, 30.0f},
                   {static_cast<float>(LFENETRE) / 2.0f - 125.0f,
                    static_cast<float>(HFENETRE) / 2.0f - 50.0f},
                    sf::Color::Red,
                    sf::Color::Green)
    , m_port(m_font,
             {125.0f, 30.0f},
             {static_cast<float>(LFENETRE) / 2.0f - 125.0f,
              static_cast<float>(HFENETRE) / 2.0f + 50.0f},
              sf::Color::Red,
              sf::Color::Green)
    ,m_ipServer(m_font,
                   {250.0f, 30.0f},
                   {static_cast<float>(LFENETRE) / 2.0f - 125.0f,
                    static_cast<float>(HFENETRE) / 2.0f - 50.0f},
                    sf::Color::Red,
                    sf::Color::Green)
{
	//Création de la fenetre:
    m_window = window; // new sf::RenderWindow(sf::VideoMode(LFENETRE, HFENETRE), L"Trainning Réseau!");
    m_font.loadFromFile("Ressources/GUI/Font/Timeless.ttf");

    m_pageMenu = 0;
    m_open = true;

	//Page 0:
    m_fond.setFillColor(sf::Color::Blue);
    m_fond.setSize(sf::Vector2f{sf::Vector2i{LFENETRE, HFENETRE}});

    //Boutons
    const auto buttonFact = [&] { return lgui::Bouton(m_font,rsholder->getTexGUI(0),rsholder->getTexGUI(1)); };
    m_server = buttonFact();
    m_client = buttonFact();
    m_quitter = buttonFact();

    sf::Vector2f firstButtonPos(static_cast<float>(LFENETRE - rsholder->getTexGUI(0)->getSize().x) / 2.0f,
                                static_cast<float>(HFENETRE / 2.0f - 100.0f));
    m_server.setPosition(firstButtonPos);
    firstButtonPos.y += 100.0f;
    m_client.setPosition(firstButtonPos);
    firstButtonPos.y += 100.0f;
    m_quitter.setPosition(firstButtonPos);

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

        m_textplayer.setFont(m_font);
         m_textplayer.setCharacterSize(15);
         m_textplayer.setColor(sf::Color::Green);
         m_textplayer.setString(L"Veuillez entrer le nombre de joueurs maximal:");
         m_textplayer.setPosition(LFENETRE/2 - m_textServerName.getGlobalBounds().width / 2 , HFENETRE / 2 + 100 );

		//Boutons
		m_back = lgui::Bouton(m_font,rsholder->getTexGUI(0),rsholder->getTexGUI(1));
		m_back.setPosition(sf::Vector2f(LFENETRE  - (rsholder->getTexGUI(0)->getSize().x + 30 )  ,HFENETRE  - 100 ));
		m_back.setFenetrelie(*m_window);
		m_back.setTitre("Retour");
		m_back.setTailleTexte(15);


        m_create = lgui::Bouton(m_font,rsholder->getTexGUI(0),rsholder->getTexGUI(1));
		m_create.setPosition(sf::Vector2f(LFENETRE/2   - (rsholder->getTexGUI(0)->getSize().x / 2  )  ,HFENETRE  - 100 ));
		m_create.setFenetrelie(*m_window);
		m_create.setTitre("Creer ");
		m_create.setTailleTexte(15);


		//Zones de Saisie
            m_serverName.setFont(m_font);
            m_port.setFont(m_font);
            m_serverName.setFenetrelie(*m_window);
            m_port.setFenetrelie(*m_window);
            std::string charset = "0123456789";
            m_port.setCharset(charset);

    //Page 2:
            //Textes

            m_textIpServer.setFont(m_font);
            m_textIpServer.setCharacterSize(15);
            m_textIpServer.setColor(sf::Color::Green);
            m_textIpServer.setString(L"Veuillez entrer le L'ip ou l'adresse du serveur:");
            m_textIpServer.setPosition(LFENETRE/2 - m_textServerName.getGlobalBounds().width / 2 , HFENETRE / 2 - 100);

            //Bouton:
            m_join =   lgui::Bouton(m_font,rsholder->getTexGUI(0),rsholder->getTexGUI(1));
            m_join.setPosition(sf::Vector2f(LFENETRE/2   - (rsholder->getTexGUI(0)->getSize().x / 2  )  ,HFENETRE  - 100 ));
            m_join.setFenetrelie(*m_window);
            m_join.setTitre("Rejoindre ");
            m_join.setTailleTexte(15);

            //Zone de saisie:


            m_ipServer.setFont(m_font);
            m_ipServer.setFenetrelie(*m_window);


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
            if(m_pageMenu == 2)
            {

                m_ipServer.actif(*evt);
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
	     if(m_create.actionner())  {}
	break;
	case 2:
         if(m_back.actionner())  m_pageMenu = 0;
         if(m_join.actionner()) {}
	default:
	break;
	}


}

bool GUI_menu::display()
{


//	if(m_open)
	//{
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
			m_window->draw(m_textplayer);
			m_back.afficher();
			m_create.afficher();
			break;
			case 2:
            m_window->draw(m_fond);
            m_window->draw(m_textIpServer);
            m_window->draw(m_textport);
			m_port.afficher();
            m_ipServer.afficher();

            m_join.afficher();
			m_back.afficher();
			default:
			break;


		}

	//}


	return true;

}
