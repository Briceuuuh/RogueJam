/*
** EPITECH PROJECT, 2023
** B-CPP-500-RUN-5-1-rtype-florian.etheve
** File description:
** Scene
*/

#include "./Scene.hpp"

Scene::Scene()
{
}

/**
 * @brief Get a reference to the map of entities in the scene.
 *
 * This function returns a reference to the map of entities contained within the scene. Entities are stored in the
 * map with their names as keys.
 *
 * @return A reference to a map where the keys are entity names and the values are pointers to IEntity objects.
 */
std::map<std::string, IEntity *> &Scene::getEntity()
{
    return (this->_entity);
}

/**
 * @brief Add an entity to the scene.
 *
 * This function adds a new entity to the scene with the specified name. It first validates the name parameter,
 * checks if an entity with the same name already exists in the scene, and then creates a new entity and adds it to the scene.
 *
 * @param name The name to assign to the new entity to be added to the scene.
 */
void Scene::addEntity(std::string name)
{
    if (name.empty() || name.c_str() == nullptr || name.c_str()[0] == '\0')
        throw SceneException("Scene.addEntity error: Empty or invalid name passed as parameter\n");
    if (this->_entity.find(name) != this->_entity.end())
        throw SceneException("Scene.addEntity error: Entity with the name '" + name + "' already exist in the scene\n");
    IEntity *entity = new Entity();
    entity->setName(name);
    std::cout << name << std::endl;
    std::pair<std::string, IEntity*> newline(name, entity);
    this->_entity.insert(newline);
}

/**
 * @brief Remove an entity from the scene.
 *
 * This function removes the entity with the specified name from the scene. It first validates the name parameter
 * and then attempts to find and delete the entity. If the entity is not found, it raises an exception.
 *
 * @param name The name of the entity to be removed from the scene.
 */
void Scene::removeEntity(std::string name)
{
    if (name.empty() || name.c_str() == nullptr || name.c_str()[0] == '\0')
        throw SceneException("Scene.removeEntity error: Empty or invalid name passed as parameter\n");

    auto entity = this->_entity.find(name);
    if (entity == this->_entity.end())
        throw SceneException("Scene.removeEntity error: Entity with the name '" + name + "' not found in the scene\n");
    delete entity->second;
    this->_entity.erase(entity);
}

/**
 * @brief Remove an entity from the scene.
 *
 * @param ent The IEntity object to be removed from the scene.
 * @throws SceneException if the entity with the specified name is not found in the scene.
 */
void Scene::removeEntity(IEntity &ent)
{
    auto entity = this->_entity.find(ent.getName());
    if (entity == this->_entity.end())
        throw SceneException("Scene.removeEntity error: Entity with the name '" + ent.getName() + "' not found in the scene\n");
    delete entity->second;
    this->_entity.erase(entity);
    delete (Entity *)&ent;
}

/**
 * @brief Set the name of the scene.
 *
 * This function sets the name of the scene to the provided string.
 *
 * @param name The new name to assign to the scene.
 */
void Scene::setName(std::string name)
{
    this->_name = name;
}

/**
 * @brief Get the name of the scene.
 *
 * This function returns the name of the scene as a reference to a string.
 *
 * @return A reference to a string representing the name of the scene.
 */
std::string &Scene::getName()
{
    return (this->_name);
}

Scene::~Scene()
{
    for (auto &ient : this->_entity)
        delete ient.second;
    this->_entity.clear();
}
