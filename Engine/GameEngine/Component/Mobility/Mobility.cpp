/*
** EPITECH PROJECT, 2023
** B-CPP-500-RUN-5-1-rtype-florian.etheve
** File description:
** Mobility
*/

#include "./Mobility.hpp"

Mobility::Mobility()
{
}

/**
 * @brief Get the type of the Mobility component.
 *
 * This function returns the type of the Mobility component, which is represented by a ComponentType_t enumeration.
 *
 * @return A reference to the ComponentType_t enum indicating the component's type.
 */
ComponentType_t &Mobility::GetType()
{
    return (this->_type);
}

/**
 * @brief Get the speed of the entity's mobility.
 *
 * This function returns the current speed of the entity's mobility.
 *
 * @return A reference to a floating-point variable indicating the speed of the entity's mobility.
 */
float &Mobility::getSpeed()
{
    return (this->_speed);
}

/**
 * @brief Set the speed of the entity's mobility.
 *
 * This function allows you to set or update the speed of the entity's mobility, controlling how fast it can move within the scene.
 *
 * @param speed The new speed value for the entity's mobility.
 */
void Mobility::setSpeed(float speed)
{
    this->_speed = speed;
}

Mobility::~Mobility()
{
}
