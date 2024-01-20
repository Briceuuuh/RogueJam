/*
** EPITECH PROJECT, 2023
** B-CPP-500-RUN-5-1-rtype-florian.etheve
** File description:
** ID
*/

#include "ID.hpp"

ID::ID()
{
}

/**
 * @brief Get the type of the component.
 *
 * @return A reference to the `ComponentType_t` representing the type of this component.
 */
ComponentType_t &ID::GetType()
{
    return (this->_type);
}

/**
 * @brief Get the ID of the component.
 *
 * @return A reference to a string representing the ID of this component.
 */
unsigned int &ID::getID()
{
    return (this->_ID);
}

/**
 * @brief Set the ID of the component.
 *
 * @param ID A string representing the ID to be set for the component.
 */
void ID::setID(unsigned ID)
{
    this->_ID = ID;
}

std::string &ID::getTag()
{
    return (this->_tag);
}

void ID::setTag(std::string tag)
{
    this->_tag = tag;
}

ID::~ID()
{
}