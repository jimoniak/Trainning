#include <algorithm>
#include <atomic>
#include <iostream>
#include <map>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Network/IpAddress.hpp>
#include <SFML/Network/Packet.hpp>
#include <SFML/Network/SocketHandle.hpp>
#include <SFML/Network/SocketSelector.hpp>
#include <SFML/Network/UdpSocket.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/System/Thread.hpp>
#include <SFML/Window/Event.hpp>

void client(const sf::String& windowTitle,
            const sf::IpAddress& serverIp,
            const unsigned short serverPort);
void server(sf::UdpSocket& socket);

std::atomic<bool> serverRunning;

int main() {
    bool serverMode = false;
    std::cout << "Voulez-vous créer un serveur (1/0) ? ";
    while(!(std::cin >> serverMode));

    if (serverMode) {
        sf::UdpSocket socket;
        if (socket.bind(64000) != sf::Socket::Done) {
            std::cerr << "Le socket serveur ne peut être créé!\n";
            return EXIT_FAILURE;
        }

        std::cout << "Port serveur : " << socket.getLocalPort() << std::endl;

        sf::Thread serverThread([&socket] { server(socket); });
        serverThread.launch();

        client(L"Serveur + Client", "localhost", socket.getLocalPort());

        serverRunning = false;
        serverThread.wait();
    } else {
        std::cout << "Insérez l'adresse du serveur : ";
        std::string serverIp;
        while (!(std::cin >> serverIp));

        std::cout << "Insérez le port du serveur : ";
        unsigned short serverPort;
        while (!(std::cin >> serverPort));

        client(L"Client", serverIp, serverPort);
    }
}

void client(const sf::String& windowTitle,
            const sf::IpAddress& serverIp,
            const unsigned short serverPort) {
    sf::UdpSocket socket;
    if (socket.bind(sf::Socket::AnyPort) != sf::Socket::Done) {
        std::cerr << "Le socket client ne peut être créé!\n";
        return;
    }

    sf::RenderWindow window(sf::VideoMode(400u, 300u), windowTitle);
    window.setVerticalSyncEnabled(true);

    bool focused = true;

    std::vector<sf::Vector2f> positions;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::GainedFocus) {
                focused = true;
            } else if (event.type == sf::Event::LostFocus) {
                focused = false;
            }
        }

        using k = sf::Keyboard;

        bool left = false;
        bool right = false;
        bool up = false;
        bool down = false;

        if (focused) {
            left = k::isKeyPressed(k::Left);
            right = k::isKeyPressed(k::Right);
            up = k::isKeyPressed(k::Up);
            down = k::isKeyPressed(k::Down);
        }

        const sf::Vector2f delta(((left) ? -3.0f : 0.0f) + ((right) ? 3.0f : 0.0f),
                                ((up) ? -3.0f : 0.0f) + ((down) ? 3.0f : 0.0f));

        socket.send(reinterpret_cast<const void*>(&delta), sizeof(sf::Vector2f), serverIp, serverPort);

        sf::Packet packet;
        sf::IpAddress remoteIp;
        unsigned short remotePort;
        socket.setBlocking(true);
        if ((socket.receive(packet, remoteIp, remotePort) == sf::Socket::Done) && remoteIp == serverIp && remotePort == serverPort) {
            auto positionBegin = reinterpret_cast<const sf::Vector2f*>(packet.getData());
            auto positionEnd = positionBegin + packet.getDataSize() / sizeof(sf::Vector2f);
            positions.clear();
            std::copy(positionBegin, positionEnd, std::back_inserter(positions));
        }

        window.clear();
        sf::CircleShape circle(10.0F, 30u);
        circle.setFillColor(sf::Color::Red);
        circle.setOutlineColor(sf::Color::White);
        circle.setOutlineThickness(2.0f);
        circle.setOrigin(10.0f, 10.0f);
        for (const auto& pos : positions) {
            circle.setPosition(pos);
            window.draw(circle);
        }
        window.display();
    }
}

void server(sf::UdpSocket& socket) {
    sf::SocketSelector selector;
    selector.add(socket);

    using Remote = std::pair<sf::IpAddress, unsigned short>;
    std::map<Remote, sf::Vector2f> positions;
    std::vector<sf::Vector2f> posBuffer;

    socket.setBlocking(true);
    serverRunning = true;
    while (serverRunning) {
        sf::Packet packet;
        sf::IpAddress remoteAdress;
        unsigned short remotePort;
        if (selector.wait(sf::seconds(1.0f)) && (socket.receive(packet, remoteAdress, remotePort) == sf::Socket::Done)) {
            positions[{remoteAdress, remotePort}] += *reinterpret_cast<const sf::Vector2f*>(packet.getData());
            posBuffer.clear();
            for (const auto& p : positions) {
                posBuffer.push_back(p.second);
            }
            socket.send(posBuffer.data(), posBuffer.size() * sizeof(sf::Vector2f), remoteAdress, remotePort);
        }
    }
}
