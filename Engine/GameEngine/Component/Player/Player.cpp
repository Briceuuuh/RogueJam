/*
** EPITECH PROJECT, 2023
** B-CPP-500-RUN-5-1-rtype-florian.etheve
** File description:
** Player
*/

#include "Player.hpp"

Player::Player()
{
}

/**
 * @brief Get the type of the component.
 *
 * @return A reference to the `ComponentType_t` representing the type of this component.
 */
ComponentType_t &Player::GetType()
{
    return (this->_type);
}

/**
 * @brief Check if the component represents a player.
 *
 * @return A reference to a boolean value indicating whether this component represents a player.
 */
bool &Player::isPlayer()
{
    return (this->_player);
}

/**
 * @brief Set the player state of the component.
 *
 * @param state A boolean value representing the player state to be set for the component.
 */
void Player::playerState(bool state)
{
    this->_player = state;
}

/**
 * @brief Get the level of the player.
 *
 * @return A reference to an integer representing the level of the player component.
 */
int &Player::getLevel()
{
    return (this->_level);
}

/**
 * @brief Set the level of the player component.
 *
 * @param level An integer representing the level to be set for the player component.
 */
void Player::setLevel(int level)
{
    this->_level = level;
}

Player::~Player()
{
}
