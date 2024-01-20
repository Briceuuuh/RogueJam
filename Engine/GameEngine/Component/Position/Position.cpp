/*
** EPITECH PROJECT, 2023
** B-CPP-500-RUN-5-1-rtype-florian.etheve
** File description:
** Position
*/

#include "./Position.hpp"

Position::Position()
{
}

/**
 * @brief Get the type of the Position component.
 *
 * This function returns the type of the Position component, which is represented by a ComponentType_t enumeration.
 *
 * @return A reference to the ComponentType_t enum indicating the component's type.
 */
ComponentType_t &Position::GetType()
{
    return (this->_type);
}

/**
 * @brief Get the current position of the entity.
 *
 * This function returns the current position of the entity as a vector of integers [x, y].
 *
 * @return A reference to a vector of integers specifying the current position of the entity [x, y].
 */
std::vector<int> &Position::getPostion()
{
    static std::vector<int> vec(2);
    vec.at(0) = this->_x;
    vec.at(1) = this->_y;
    return (vec);
}

/**
 * @brief Set the position of the entity.
 *
 * This function allows you to set or update the position of the entity within the scene by specifying the new x and y coordinates.
 *
 * @param x The new x-coordinate of the entity's position.
 * @param y The new y-coordinate of the entity's position.
 *
 * @note Use this function to reposition the entity within the scene by providing new x and y coordinates. It allows you to control
 * the entity's location in the 2D space of the scene.
 */
void Position::setPosition(int x, int y)
{
    this->_x = x;
    this->_y = y;
}

Position::~Position()
{
}
