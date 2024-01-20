/*
** EPITECH PROJECT, 2023
** B-CPP-500-RUN-5-1-rtype-florian.etheve
** File description:
** IA
*/

#include "IA.hpp"

IA::IA()
{
}

/**
 * @brief Get the type of the component.
 *
 * @return A reference to the `ComponentType_t` representing the type of this component.
 */
ComponentType_t &IA::GetType()
{
    return (this->_type);
}

/**
 * @brief Check if this component represents an AI (Artificial Intelligence).
 *
 * @return A reference to a boolean value indicating whether this component represents an AI.
 */
bool &IA::isIA()
{
    return (this->_IA);
}

/**
 * @brief Set the state of the AI component.
 *
 * @param state A boolean value representing the state of the AI component.
 */
void IA::IAState(bool state)
{
    this->_IA = state;
}

/**
 * @brief Get the level of the AI component.
 *
 * @return A reference to an integer representing the level of the AI component.
 */
int &IA::getLevel()
{
    return (this->_level);
}

/**
 * @brief Set the level of the AI component.
 *
 * @param level An integer representing the level to be set for the AI component.
 */
void IA::setLevel(int level)
{
    this->_level = level;
}

IA::~IA()
{
}
