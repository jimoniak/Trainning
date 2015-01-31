

/**
 * \file serveur.hpp
 * \brief Fichier contenant la class Serveur
 * \author J. PEAULT & Q. PUBERT
 * \version 0.1
 * \date 30 janvier 2015
 *
 * La classe Serveur permet de gérer les connexions entre les clients et proposer un environnement pour qu'ils puissent évoluer et dialoguer.
 *
 */




 #ifndef SERVER
 #define SERVER


 #include <SFML/System.hpp>
 #include <SFML/Network.hpp>

 #include "carte.hpp"

 #include <vector>


 class Server
 {
	 private:
	 std::string m_name;
	 std::string m_listenPort;

	 int m_nbPlayer;
	 Map *m_map;

	 sf::SocketSelector m_selector;
	 std::vector<sf::TcpSocket> m_tabSocket;


	 public:
	 Server();

	 ~Server();


 };

 #endif
