/*
** EPITECH PROJECT, 2023
** B-CPP-500-RUN-5-1-rtype-florian.etheve
** File description:
** UdpManager.cpp
*/

#include "UdpManager.hpp"

/**
 * Constructor for UdpManager.
 * Initializes the UDP socket with the specified server IP and port.
 *
 * @param port The port to connect to.
 * @param serverIP The IP address of the server.
 */
UdpManager::UdpManager(const std::string &port, const std::string & serverIP)
{
    this->_socket = new sf::UdpSocket;
    this->_serverPort = std::stoi(port);
    this->_serverIP = serverIP;
    this->_sendedPacket = new sf::Packet;
    this->_socket->setBlocking(false);
}

/**
 * Get a reference to the UDP socket used for communication.
 *
 * @return A reference to the UDP socket.
 */
sf::UdpSocket &UdpManager::getSocket() const
{
    return *(this->_socket);
}

/**
 * Send the provided string as a UDP package to the server.
 *
 * @param string The string to send as a UDP package.
 */
void UdpManager::sendPackage(std::string string)
{
    if (this->getSocket().send(string.c_str(), string.size(), this->_serverIP, this->_serverPort) != sf::Socket::Done)
        throw UdpException("UdpManager.sendPackage: Cannot comunnicate with the server\n");
}

/**
 * Send the UDP package stored in the manager to the server.
 */
void UdpManager::sendPackage()
{
    std::string tmp;
    sf::Packet pack;
    this->getSendedPackage() >> tmp;
    pack << tmp;
    if (this->getSocket().send(tmp.c_str(), tmp.size(), this->_serverIP, this->_serverPort) != sf::Socket::Done)
        throw UdpException("UdpManager.sendPackage: Cannot comunnicate with the server\n");
}

/**
 * Get a constant reference to the UDP package stored in the manager.
 *
 * @return A constant reference to the UDP package.
 */
sf::Packet &UdpManager::getPackage() const
{
    return *this->_sendedPacket;
}

/**
 * Receive a UDP package from the server and store it in the manager.
 */
void UdpManager::receivePackage()
{
    char buffer[2];
    size_t reveive;

    sf::IpAddress ip = this->_serverIP;
    unsigned short port = this->_serverPort;
    if (this->getSocket().receive(buffer, sizeof(buffer), reveive, ip, port) != sf::Socket::Done) {
    } else {
        this->_receivedPacket = buffer;
    }
}

/**
 * Get a reference to the UDP package to be sent.
 *
 * @return A reference to the UDP package string to be sent.
 */
sf::Packet &UdpManager::getSendedPackage()
{
    return *(this->_sendedPacket);
}

/**
 * Get the received UDP package as a string.
 *
 * @return A reference to the received UDP package string.
 */
std::string &UdpManager::getReceivedString()
{
    return (this->_receivedPacket);
}

/**
 * Set the UDP package to the provided string.
 *
 * @param str The string to set as the UDP package.
 */
void UdpManager::setPackage(const std::string &str)
{
    if (this->_sendedPacket->getDataSize() > 0) {
        this->_sendedPacket->clear();
        this->getSendedPackage() << str;
    } else {
        this->getSendedPackage() << str;
    }
}

/**
 * Add a string to the UDP package at the specified index.
 *
 * @param str The string to add to the package.
 * @param index The index where the string should be added.
 */
void UdpManager::addPackage(const std::string &str, uint16_t index)
{
    std::string save;
    if (this->_sendedPacket->getDataSize() > 0 && this->_sendedPacket->getDataSize() < index) {
        this->getSendedPackage() >> save;
        save.insert(index, str);
        this->setPackage(save);
    } else if (this->_sendedPacket->getDataSize() > 0 && this->_sendedPacket->getDataSize() >= index) {
        this->_sendedPacket->append((char *)str.c_str(), str.length());
    }
}

/**
 * Destructor for UdpManager.
 * Frees resources and deletes the UDP socket and the UDP package.
 */
UdpManager::~UdpManager()
{
    if (this->_socket) {
        this->_socket->setBlocking(true);
        delete this->_socket;
    }
    if (this->_sendedPacket)
        delete this->_sendedPacket;
}
