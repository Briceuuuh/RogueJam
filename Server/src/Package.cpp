/*
** EPITECH PROJECT, 2023
** B-CPP-500-RUN-5-1-rtype-florian.etheve
** File description:
** Package.cpp
*/

#include "../include/Package.hpp"

/**
 * @brief Package class constructor.
 *
 * This constructor initializes a Package object.
 */
Package::Package()
{
}

/**
 * @brief Pack data into the package.
 *
 * This function reads data from the internal packet and stores it in the buffer. It also prints the result of the read to the standard output.
 */
void Package::pack()
{
    this->package >> this->buffer;
}

/**
 * @brief Set the buffer with the provided string.
 *
 * This function sets the buffer with the content of the provided string. If the buffer is not empty, it is cleared before setting the new value.
 *
 * @param str The string to set as the buffer content.
 */
void Package::setBuffer(const std::string &str)
{
    if (this->buffer.empty() == false) {
        this->buffer.clear();
    }
    this->buffer = str;
}

/**
 * @brief Get the content of the buffer.
 *
 * This function retrieves the content of the buffer as a constant reference to a string.
 *
 * @return A constant reference to the buffer content.
 */
const std::string &Package::getBuffer() const
{
    return this->buffer;
}

/**
 * @brief Set the internal packet with the provided packet.
 *
 * This function sets the internal packet with the content of the provided packet.
 *
 * @param pack The packet to set as the internal packet.
 */
void Package::setPacket(sf::Packet pack)
{
    this->package = pack;
}

/**
 * @brief Get the internal packet.
 *
 * This function retrieves the internal packet.
 *
 * @return The internal packet.
 */
sf::Packet Package::getPacket() const
{
    return this->package;
}

/**
 * @brief Package class destructor.
 *
 * This destructor is responsible for cleaning up resources associated with the Package object.
 */
Package::~Package()
{
}

