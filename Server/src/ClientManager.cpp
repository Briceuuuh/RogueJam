/*
** EPITECH PROJECT, 2023
** B-CPP-500-RUN-5-1-rtype-florian.etheve
** File description:
** ClientManager.cpp
*/

#include "../include/ClientManager.hpp"

/**
 * @brief ClientManager constructor.
 *
 * This constructor initializes a ClientManager object with the specified unique identifier (ID).
 *
 * @param _id The unique identifier (ID) associated with the client.
 */
ClientManager::ClientManager(size_t _id)
{
    this->id = _id;
    this->connected = false;
    this->first = false;
    this->port = 0;
    this->tcp = new Transmission<sf::TcpSocket>();
    this->tcp->getSocket()->setBlocking(false);
}

/**
 * @brief Set the connection status for the client.
 *
 * This function sets the connection status for the client. If the client is connected to the server, the status is set to true.
 *
 * @param connection True if the client is connected, false otherwise.
 */
void ClientManager::setConnect(bool connection)
{
    this->connected = connection;
}

/**
 * @brief Check the connection status of the client.
 *
 * This function checks whether the client is currently connected to the server.
 *
 * @return True if the client is connected, false otherwise.
 */
bool ClientManager::getConnect() const
{
    return this->connected;
}

/**
 * @brief Add client connection information.
 *
 * This function adds the connection information (IP address and port) for the client. If the information is different from the existing values, it is updated.
 *
 * @param _ip The IP address of the client.
 * @param _port The port number used for communication with the client.
 *
 * @return True if the information was updated, false if it remains the same.
 */
bool ClientManager::addInfo(sf::IpAddress _ip, unsigned short _port, size_t _id)
{
    if (this->id == _id && this->ip.toString() == "0.0.0.0" && this->port != _port) {
        sf::IpAddress new_ip = _ip;
        unsigned short new_port = _port;
        this->ip = new_ip;
        this->port = new_port;
        return true;
    }
    return false;
}

/**
 * @brief Get the TCP transmission object associated with the client.
 *
 * This function retrieves the TCP transmission object, which manages communication with the client via TCP.
 *
 * @return A pointer to the TCP transmission object.
 */
Transmission<sf::TcpSocket> *ClientManager::getTcp() const
{
    return this->tcp;
}

/**
 * @brief Check if it's the first interaction with the server.
 *
 * This function checks whether the client has established its first interaction with the server.
 *
 * @return True if it's the first interaction, false otherwise.
 */
bool ClientManager::getFirst() const
{
    return this->first;
}

/**
 * @brief Set the first interaction status to true.
 *
 * This function marks the client's first interaction with the server as true.
 */
void ClientManager::setFirst()
{
    this->first = true;
}

/**
 * @brief Get the unique identifier (ID) associated with the client.
 *
 * This function retrieves the unique identifier (ID) assigned to the client.
 *
 * @return The client's unique identifier (ID).
 */
size_t ClientManager::getId() const
{
    return this->id;
}

/**
 * @brief Set the IP address associated with the client manager.
 *
 * This function sets the IP address used for connecting to a server or for identifying the client.
 *
 * @param _ip The IP address to set.
 */
void ClientManager::setIp(sf::IpAddress _ip)
{
    sf::IpAddress new_ip = _ip;
    this->ip = new_ip;
}

/**
 * @brief Get the IP address associated with the client manager.
 *
 * This function retrieves the IP address currently associated with the client manager.
 *
 * @return The IP address associated with the client manager.
 */
sf::IpAddress ClientManager::getIp() const
{
    sf::IpAddress new_ip = this->ip;
    return new_ip;
}

/**
 * @brief Set the port number associated with the client manager.
 *
 * This function sets the port number used for communication with a server or for identifying the client's port.
 *
 * @param _port The port number to set.
 */
void ClientManager::setPort(unsigned short _port)
{
    unsigned short new_port = _port;
    this->port = new_port;
}

/**
 * @brief Get the port number associated with the client manager.
 *
 * This function retrieves the port number currently associated with the client manager.
 *
 * @return The port number associated with the client manager.
 */
unsigned short ClientManager::getPort() const
{
    unsigned short new_port = this->port;
    return new_port;
}

/**
 * @brief Handle listening for TCP communication.
 *
 * This function is responsible for listening for incoming TCP communication. It may involve reading data from the TCP socket
 * and processing received packets or messages.
 */
void ClientManager::onListenTcp()
{
    sf::Packet packet = this->tcp->getPack()->getPacket();
    std::string test;
    if (this->tcp->getSocket()->receive(packet) == sf::Socket::Done) {
    }
}

ClientManager::~ClientManager()
{
    delete (this->tcp);
}
