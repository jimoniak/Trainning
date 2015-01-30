#include <algorithm>
#include <atomic>
#include <iostream>
#include <map>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Network/IpAddress.hpp>
#include <SFML/Network/Packet.hpp>
#include <SFML/Network/UdpSocket.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/System/Thread.hpp>
#include <SFML/Window/Event.hpp>

void client(const sf::IpAddress& ip, const unsigned short port, const unsigned short remotePort);
void server();

std::atomic<bool> serverRunning;

int main() {
    bool serverMode = false;
    std::cout << "Voulez-vous créer un serveur (1/0) ? ";
    while(!(std::cin >> serverMode));

    if (serverMode) {
        server();
    } else {
        std::cout << "Insérez l'adresse du serveur : ";
        std::string ipStr;
        while (!(std::cin >> ipStr));

        std::cout << "Choisissez un port du client : ";
        unsigned short clientPort;
        while (!(std::cin >> clientPort));

        std::cout << "Choisissez un port du serveur : ";
        unsigned short serverPort;
        while (!(std::cin >> serverPort));

        client(ipStr, clientPort, serverPort);
    }
}

void client(const sf::IpAddress& ip, const unsigned short port, const unsigned short serverPort) {
    sf::UdpSocket socket;
    if (socket.bind(port) != sf::Socket::Done) {
        std::cerr << "Client socket can't be binded to port " << port << std::endl;
        return;
    }

    sf::RenderWindow window(sf::VideoMode(800u, 600u), L"Title");
    window.setVerticalSyncEnabled(true);

    bool focused = true;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            else if (event.type == sf::Event::GainedFocus) focused = true;
            else if(event.type == sf::Event::LostFocus) focused = false;

        }

        using k = sf::Keyboard;

         bool left ;
         bool right ;
         bool up  ;
         bool down ;

        if(focused)
        {


        left = k::isKeyPressed(k::Left);
        right = k::isKeyPressed(k::Right);
        up = k::isKeyPressed(k::Up);
        down = k::isKeyPressed(k::Down);

        }

        const sf::Vector2f delta(((left) ? -1.0f : 0.0f) + ((right) ? 1.0f : 0.0f),
                                ((up) ? -1.0f : 0.0f) + ((down) ? 1.0f : 0.0f));

        socket.setBlocking(false);

        while (socket.send(reinterpret_cast<const void*>(&delta), sizeof(sf::Vector2f), ip, serverPort) != sf::Socket::Done);


        sf::Packet packet;
        sf::IpAddress remoteIp;
        unsigned short remotePort;
        socket.setBlocking(true);
        while ((socket.receive(packet, remoteIp, remotePort) != sf::Socket::Done) && remoteIp != ip && remotePort != serverPort);

        auto positionBegin = reinterpret_cast<const sf::Vector2f*>(packet.getData());
        auto positionEnd = positionBegin + packet.getDataSize() / sizeof(sf::Vector2f);

        window.clear();
        sf::CircleShape circle(10.0F, 30u);
        circle.setFillColor(sf::Color::Red);
        circle.setOutlineColor(sf::Color::White);
        circle.setOutlineThickness(2.0f);
        circle.setOrigin(10.0f, 10.0f);
        for (; positionBegin != positionEnd; ++positionBegin) {
            circle.setPosition(*positionBegin);
            window.draw(circle);
        }
        window.display();
    }

    serverRunning = false;
}

void server() {
    std::cout << "Choisissez un port serveur : ";
    unsigned short serverPort;
    while (!(std::cin >> serverPort));

    std::cout << "Choisissez un port client : ";
    unsigned short clientPort;
    while (!(std::cin >> clientPort));

    sf::UdpSocket socket;
    if (socket.bind(serverPort) != sf::Socket::Done) {
        std::cerr << "Server socket can't be binded to port " << serverPort << std::endl;
    }

    using Remote = std::pair<sf::IpAddress, unsigned short>;
    std::map<Remote, sf::Vector2f> positions;
    std::vector<sf::Vector2f> posBuffer;

    sf::Thread thread([serverPort, clientPort] () { client(sf::IpAddress::LocalHost, clientPort, serverPort); });
    thread.launch();

    socket.setBlocking(false);
    serverRunning = true;
    while (serverRunning) {
        sf::Packet packet;
        sf::IpAddress remoteAdress;
        unsigned short remotePort;
        if (socket.receive(packet, remoteAdress, remotePort) != sf::Socket::Done)
            continue;
        positions[{remoteAdress, remotePort}] += *reinterpret_cast<const sf::Vector2f*>(packet.getData());

        posBuffer.clear();
        for (const auto& p : positions) {
            posBuffer.push_back(p.second);
        }
        for (const auto& p : positions) {
            while (socket.send(posBuffer.data(), posBuffer.size() * sizeof(sf::Vector2f), p.first.first, p.first.second) != sf::Socket::Done);
        }
    }
}
