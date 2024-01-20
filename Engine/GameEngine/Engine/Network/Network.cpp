/*
** EPITECH PROJECT, 2023
** B-CPP-500-RUN-5-1-rtype-florian.etheve
** File description:
** Network
*/

#include "Network.hpp"

/**
 * Constructor for the Network class.
 * Initializes a Network instance with the provided engine, server IP, and port.
 *
 * @param engine The Engine instance associated with the network.
 * @param ip     The server IP address (can be "localhost" for local testing).
 * @param port   The port number for both UDP and TCP connections.
 */
Network::Network(Engine &engine, std::string ip, std::string port)
{
    (ip == "localhost") ? this->_serverIP = "127.0.0.1" : this->_serverIP = ip;
    this->_port = std::atoi(port.c_str());
    this->_udp = new UdpManager(port, ip);
    this->_tcp = new TcpManager(port, ip);
    this->_code = new Code();
    this->_engine = &engine;
    this->_connectedTcp = false;
    this->_connectedUdp = false;
}

/**
 * Establishes a TCP connection to the server and receives client information.
 * If not already connected, it connects to the server and receives client session data.
 *
 * @throws NetworkException if the connection to the server fails.
 */
void Network::connectionTcp()
{
    if (!this->_connectedTcp) {
        if (this->_tcp->getSocket().connect(this->_serverIP, this->_port) != sf::Socket::Done) {
            throw NetworkException("Network.connect error: Cannot connect to the server\n");
        }
        this->_tcp->sendPackage("New client connected");
        this->_tcp->receivePackage();
        std::string delimiter = ",";
        size_t pos = this->_tcp->getReceivedPackage().find(delimiter);
        if (pos != std::string::npos) {
            std::string partie1 = this->_tcp->getReceivedPackage().substr(0, pos);
            std::string partie2 = this->_tcp->getReceivedPackage().substr(pos + delimiter.length());
            ClientSession *tmp = new ClientSession(std::atoi(partie1.c_str()), std::atoi(partie2.c_str()));
            this->_clients.push_back(tmp);
            this->_engine->scene->createEntityPreset("room" + std::to_string(tmp->getRoom()), "player" + std::to_string(tmp->getId()), {0, tmp->getId()}, "./Client/assets/Ship" + std::to_string(tmp->getId()) + ".png", "player", true);
            Health *comp = (Health*)this->_engine->entity->getComponent("room" + std::to_string(tmp->getRoom()), "player" + std::to_string(tmp->getId()), HEALTH);
            this->_engine->scene->createTextPreset("room" + std::to_string(tmp->getRoom()), "player" + std::to_string(tmp->getId()) + "health", {(this->_engine->window->getDimension().at(0) / 2) - 5 * 10, 0}, "./Client/assets/font.ttf", "PV:" + std::to_string(comp->getHealth()), sf::Color::White);
        }
        this->_connectedTcp = true;
    }
}

/**
 * Establishes a UDP connection and receives data from the server.
 * If the TCP connection is established and not already connected over UDP, it establishes a UDP connection.
 */
void Network::connectionUdp()
{
    if (this->_connectedTcp && !this->_connectedUdp) {
        std::string tmp;
        std::string res;
        for (int i = 1; i >= 0; --i) {
            int bit = ((this->_clients.at(0)->getRoom() - 1) >> i) & 1;
            tmp += std::to_string(bit);
        }
        res += tmp;
        tmp.clear();
        for (int i = 2; i >= 0; --i) {
            int bit = (this->_clients.at(0)->getId() >> i) & 1;
            tmp += std::to_string(bit);
        }
        res += tmp;
        tmp.clear();
        res += "11111111000";
        this->_code->setSendPackage(res);
        this->_code->switchToAscii();
        this->_udp->setPackage(this->_code->getPackage());
        this->_udp->sendPackage();
        this->_udp->receivePackage();
        while (this->_udp->getReceivedString().empty()) {
            this->_udp->receivePackage();
        }
        this->_code->getReceivePackage(this->_udp->getReceivedString());
        ClientSession *adversary = new ClientSession(this->_code);
        this->_clients.push_back(adversary);
        this->_engine->scene->createEntityPreset("room" + std::to_string(adversary->getRoom()), "player" + std::to_string(adversary->getId()), {0, adversary->getId()}, "./Client/assets/Ship" + std::to_string(adversary->getId()) + ".png", "player", true);
        this->_connectedUdp = true;
    }
}

/**
 * Handles the game protocol, processing received messages from the server.
 * If both TCP and UDP connections are established, this function receives UDP data
 * and processes it based on the game events.
 * It updates player positions and events according to the received data.
 */
void Network::gameProtocol()
{
    if (this->_connectedTcp && this->_connectedUdp) {
        this->_udp->receivePackage();
        this->_code->getReceivePackage(this->_udp->getReceivedString());
        for (size_t i = 0; i != this->_clients.size(); i++) {
            if (this->_clients.at(i)->getId() == this->_code->getId()) {
                if (this->_code->getEvent() == "remove entity") {
                    this->_engine->scene->removeEntitytoScene("room" + std::to_string(this->_clients.at(i)->getId()), "ennemy" + std::to_string(this->_clients.at(i)->getId()));
                    std::cout << "j'ai recu un remove ennemy" << std::endl;
                }
                if (this->_code->getEvent() == "move entity") {
                    if (this->_clients.at(i)->getDown() != this->_code->getDown()) {
                        this->_clients.at(i)->changeDown(this->_code->getDown());
                        this->_engine->system->moveEntitySpecificSystem("player" + std::to_string(this->_clients.at(i)->getId()), "room" + std::to_string(this->_clients.at(i)->getRoom()), {this->_clients.at(i)->getUp(), this->_clients.at(i)->getDown(), this->_clients.at(i)->getLeft(), this->_clients.at(i)->getRight()}, 5);
                        return;
                    }
                    if (this->_clients.at(i)->getUp() != this->_code->getUp()) {
                        this->_clients.at(i)->changeUp(this->_code->getUp());
                        this->_engine->system->moveEntitySpecificSystem("player" + std::to_string(this->_clients.at(i)->getId()), "room" + std::to_string(this->_clients.at(i)->getRoom()), {this->_clients.at(i)->getUp(), this->_clients.at(i)->getDown(), this->_clients.at(i)->getLeft(), this->_clients.at(i)->getRight()}, 5);
                        return;
                    }
                    if (this->_clients.at(i)->getRight() != this->_code->getRight()) {
                        this->_clients.at(i)->changeRight(this->_code->getRight());
                        this->_engine->system->moveEntitySpecificSystem("player" + std::to_string(this->_clients.at(i)->getId()), "room" + std::to_string(this->_clients.at(i)->getRoom()), {this->_clients.at(i)->getUp(), this->_clients.at(i)->getDown(), this->_clients.at(i)->getLeft(), this->_clients.at(i)->getRight()}, 5);
                        return;
                    }
                    if (this->_clients.at(i)->getLeft() != this->_code->getLeft()) {
                        this->_clients.at(i)->changeLeft(this->_code->getLeft());
                        this->_engine->system->moveEntitySpecificSystem("player" + std::to_string(this->_clients.at(i)->getId()), "room" + std::to_string(this->_clients.at(i)->getRoom()), {this->_clients.at(i)->getUp(), this->_clients.at(i)->getDown(), this->_clients.at(i)->getLeft(), this->_clients.at(i)->getRight()}, 5);
                        return;
                    }
                    if (this->_clients.at(i)->getShoot() != this->_code->getShoot()) {
                        this->_clients.at(i)->changeShoot(this->_code->getShoot());
                        this->_engine->system->shootSpecificSystem("player" + std::to_string(this->_clients.at(i)->getId()), "room" + std::to_string(this->_clients.at(i)->getRoom()));
                        return;
                    }
                }
                if (this->_code->getEvent() == "error")
                    return;
            }
        }
    }
}

Code &Network::getCode()
{
    return *(this->_code);
}

TcpManager &Network::getTcp()
{
    return *(this->_tcp);
}

UdpManager &Network::getUdp()
{
    return *(this->_udp);
}

std::vector<ClientSession*> &Network::getClient()
{
    return (this->_clients);
}

Network::~Network()
{
    delete this->_udp;
    delete this->_tcp;
    delete this->_code;
    delete this->_engine;
}
