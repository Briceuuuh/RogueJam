/*
** EPITECH PROJECT, 2023
** B-CPP-500-RUN-5-1-rtype-florian.etheve
** File description:
** Damage
*/

#include "./Damage.hpp"

Damage::Damage()
{
}

/**
 * @brief Get the type of the Damage component.
 *
 * This function returns the type of the Damage component, which is represented by a ComponentType_t enumeration.
 *
 * @return A reference to the ComponentType_t enum indicating the component's type.
 */
ComponentType_t &Damage::GetType()
{
    return (this->_type);
}

/**
 * @brief Get the current damage count of the entity.
 *
 * This function returns the current damage count associated with the entity. The damage count represents the amount
 * of damage the entity has received.
 *
 * @return A reference to an integer representing the entity's damage count.
 */
int &Damage::getDamage()
{
    return (this->_damageCount);
}

/**
 * @brief Set the damage count for the entity.
 *
 * This function allows you to set or update the damage count for the entity. The damage count represents the amount of damage
 * the entity has received.
 *
 * @param damageCount The new damage count to assign to the entity.
 */
void Damage::setDamage(int damageCount)
{
    this->_damageCount = damageCount;
}

/**
 * @brief Check the disable state of the Damage component.
 *
 * This function allows you to check the current disable state of the Damage component. If the component is disabled, it may
 * not perform its normal functions.
 *
 * @return A reference to a boolean indicating whether the Damage component is currently disabled.
 *
 * @note This function allows you to query the disable state of the component, which can be useful for controlling and managing
 *       its behavior.
 */
bool &Damage::isDisable()
{
    return (this->_disabled);
}

/**
 * @brief Set the disable state of the Damage component.
 *
 * This function allows you to enable or disable the Damage component by setting its disable state.
 *
 * @param state A boolean indicating whether to disable (true) or enable (false) the Damage component.
 */
void Damage::disableState(bool state)
{
    this->_disabled = state;
}

Damage::~Damage()
{
}
