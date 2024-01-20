/*
** EPITECH PROJECT, 2023
** B-CPP-500-RUN-5-1-rtype-florian.etheve
** File description:
** Entity
*/

#include "./Entity.hpp"
#include "../Component/ComponentPackage.hpp"

Entity::Entity()
{
}

/**
 * @brief Add a component of the specified type to the entity.
 *
 * This function allows you to add a component of a specified type to the entity. It accepts a `ComponentType_t`
 * enumeration representing the type of component to add and creates a new instance of the corresponding component
 * type. The new component is then added to the entity's list of components.
 *
 * @param type The type of component to add to the entity.
 */
void Entity::AddComponent(ComponentType_t type)
{
    if (type == POSITION) {
        IComponent *comp = new Position();
        this->_components.push_back(comp);
        return;
    }
    if (type == MOBILITY) {
        IComponent *comp = new Mobility();
        this->_components.push_back(comp);
        return;
    }
    if (type == HEALTH) {
        IComponent *comp = new Health();
        this->_components.push_back(comp);
        return;
    }
    if (type == DAMAGE) {
        IComponent *comp = new Damage();
        this->_components.push_back(comp);
        return;
    }
    if (type == HITBOX) {
        IComponent *comp = new Hitbox();
        this->_components.push_back(comp);
        return;
    }
    if (type == VISUAL) {
        IComponent *comp = new Visual();
        this->_components.push_back(comp);
        return;
    }
    if (type == TEXT) {
        IComponent *comp = new Text();
        this->_components.push_back(comp);
        return;
    }
    if (type == _IA_) {
        IComponent *comp = new IA();
        this->_components.push_back(comp);
        return;
    }
    if (type == PLAYER) {
        IComponent *comp = new Player();
        this->_components.push_back(comp);
        return;
    }
    if (type == _ID_) {
        IComponent *comp = new ID();
        this->_components.push_back(comp);
        return;
    }
    throw EntityException("Entity.addComponent error: Undefined type\n");
}

/**
 * @brief Remove a component of the specified type from the entity.
 *
 * This function allows you to remove a component of a specified type from the entity. It iterates through the list of components,
 * checks the type of each component, and removes the first component of the specified type found. If no such component exists,
 * it raises an exception.
 *
 * @param type The type of component to remove from the entity.
 */
void Entity::RemoveComponent(ComponentType_t type)
{
    for (auto comp = this->_components.begin(); comp != this->_components.end(); comp++) {
        if ((*comp)->GetType() == type) {
            this->_components.erase(comp);
            return;
        }
    }
    throw EntityException("Entity.removeComponent error: Undefined type\n");
}

/**
 * @brief Get a reference to the vector of components in the entity.
 *
 * This function returns a reference to the vector of components currently associated with the entity. Each component
 * in the vector contributes to the entity's behavior and functionality.
 *
 * @return A reference to a vector containing pointers to the entity's components.
 */
std::vector<IComponent *> &Entity::GetCurrentComponent()
{
    return (this->_components);
}

/**
 * @brief Get a pointer to a specific component of the entity by its component type.
 *
 * @param comp The ComponentType_t value specifying the type of the component to retrieve.
 * @return A pointer to the requested component if found, or nullptr if the component is not present.
 */
IComponent *Entity::getComponent(ComponentType_t comp)
{
    for (size_t i = 0; i != this->_components.size(); i++) {
        if (this->_components.at(i)->GetType() == comp)
            return (this->_components.at(i));
    }
    return nullptr;
}

/**
 * @brief Get a reference to a specific component of the entity by its component type.
 *
 * @param comp The ComponentType_t value specifying the type of the component to retrieve.
 * @return A reference to the requested component if found, or a reference to an Invalid component (presumably used for error handling) if the requested component is not present.
 */
IComponent &Entity::getComponentRef(ComponentType_t comp)
{
    for (size_t i = 0; i != this->_components.size(); i++) {
        if (this->_components.at(i)->GetType() == comp)
            return (*this->_components.at(i));
    }
    Invalid *invalid = new Invalid();
    return (*invalid);
}

/**
 * @brief Get the name of the entity.
 *
 * This function returns the name of the entity as a reference to a string. The name is used to identify and reference
 * the entity within the application.
 *
 * @return A reference to a string representing the name of the entity.
 */
std::string &Entity::getName()
{
    return (this->_name);
}

/**
 * @brief Set the name of the entity.
 *
 * This function allows you to set or change the name of the entity to the provided string. The name is used to identify and reference
 * the entity within the application.
 *
 * @param name The new name to assign to the entity.
 */
void Entity::setName(std::string name)
{
    this->_name = name;
}

Entity::~Entity()
{
    this->_components.clear();
}
