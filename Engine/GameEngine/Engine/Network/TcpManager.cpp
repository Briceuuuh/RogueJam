/*
** EPITECH PROJECT, 2023
** B-CPP-500-RUN-5-1-rtype-florian.etheve
** File description:
** UdpManager.cpp
*/

#include "TcpManager.hpp"

/**
 * Constructor for TcpManager.
 * Initializes the TCP socket with the specified server IP and port.
 *
 * @param _port The port to connect to.
 * @param _serverIP The IP address of the server.
 */
TcpManager::TcpManager(const std::string &_port, const std::string & _serverIP)
{
    this->socket = new sf::TcpSocket;
    this->serverPort = std::stoi(_port);
    this->serverIP = _serverIP;
}

/**
 * Get a reference to the TCP socket used for communication.
 *
 * @return A reference to the TCP socket.
 */
sf::TcpSocket &TcpManager::getSocket() const
{
    return *(this->socket);
}

/**
 * Set the TCP package to the provided string.
 *
 * @param str The string to set as the TCP package.
 */
void TcpManager::setPackage(const std::string &str)
{
    if (this->_sendedPacket.size() > 0) {
        this->_sendedPacket.clear();
        this->_sendedPacket = str;
    } else {
        this->_sendedPacket = str;
    }
}

/**
 * Add a string to the TCP package at the specified index.
 *
 * @param str The string to add to the package.
 * @param index The index where the string should be added.
 */
void TcpManager::addPackage(const std::string &str, uint16_t index)
{
    std::string save;
    if (this->_sendedPacket.size() > 0 && this->_sendedPacket.size() < index) {
        save = this->_sendedPacket;
        save.insert(index, str);
        this->setPackage(save);
    } else if (this->_sendedPacket.size() > 0 && this->_sendedPacket.size() >= index) {
        this->_sendedPacket.append((char *)str.c_str(), str.length());
    }
}

/**
 * Get the received TCP package as a string.
 *
 * @return A reference to the received TCP package string.
 */
std::string &TcpManager::getReceivedPackage()
{
    return (this->_receivedPacket);
}

/**
 * Get the TCP package to be sent as a string.
 *
 * @return A reference to the TCP package string to be sent.
 */
std::string &TcpManager::getSendedPackage()
{
    return (this->_sendedPacket);
}

/**
 * Send the provided package string via the TCP socket.
 *
 * @param package The package string to send.
 */
void TcpManager::sendPackage(std::string package)
{
    sf::Packet pack;
    pack << package;
    if (this->socket->send(pack) != sf::Socket::Done)
        throw TcpException("TcpManager.sendPackage error: Cannot communicate with the server\n");
}

/**
 * Send the TCP package stored in the manager via the TCP socket.
 */
void TcpManager::sendPackage()
{
    sf::Packet pack;
    pack << this->getSendedPackage();
    if (this->socket->send(pack) != sf::Socket::Done)
        throw TcpException("TcpManager.sendPackage error: Cannot communicate with the server\n");
}

/**
 * Receive a TCP package from the server and store it in the manager.
 * This function receives data from the socket and appends it to the received package.
 */
void TcpManager::receivePackage()
{
    char buffer[1024];
    size_t receive;

    if (this->getSocket().receive(buffer, sizeof(buffer), receive) != sf::Socket::Done)
        throw TcpException("TcpManager.receivePakcage: Cannot comunnicate with the server\n");

    this->_receivedPacket.assign(buffer, receive);
}

/**
 * Destructor for TcpManager.
 * Frees resources and deletes the TCP socket.
 */
TcpManager::~TcpManager() {
    if (this->socket) {
        this->socket->setBlocking(true);
        delete this->socket;
    }
}
