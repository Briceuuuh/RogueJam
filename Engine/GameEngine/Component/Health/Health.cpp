/*
** EPITECH PROJECT, 2023
** B-CPP-500-RUN-5-1-rtype-florian.etheve
** File description:
** Health
*/

#include "./Health.hpp"

Health::Health()
{
}

/**
 * @brief Get the type of the Health component.
 *
 * This function returns the type of the Health component, which is represented by a ComponentType_t enumeration.
 *
 * @return A reference to the ComponentType_t enum indicating the component's type.
 */
ComponentType_t &Health::GetType()
{
    return (this->_type);
}

/**
 * @brief Get the current health value of the entity.
 *
 * This function returns the current health value associated with the entity. The health value represents the entity's current
 * state of well-being or hit points.
 *
 * @return A reference to an integer representing the entity's health value.
 */
int &Health::getHealth()
{
    return (this->_health);
}

/**
 * @brief Set the health value for the entity.
 *
 * This function allows you to set or update the health value for the entity. The health value represents the entity's current
 * state of well-being or hit points.
 *
 * @param health The new health value to assign to the entity.
 */
void Health::setHealth(int health)
{
    this->_health = health;
}

Health::~Health()
{
}
