/*
** EPITECH PROJECT, 2023
** B-CPP-500-RUN-5-1-rtype-florian.etheve
** File description:
** EntityManager
*/

#include "EntityManager.hpp"

/**
 * @brief Constructs an EntityManager instance.
 *
 * Initializes an EntityManager with references to the scene map and the engine. The EntityManager is responsible for managing
 * entities within scenes.
 *
 * @param scene A reference to a map containing scene names and their corresponding IScene pointers.
 * @param engine A reference to the Engine instance used to manage game entities.
 */
EntityManager::EntityManager(std::map<std::string, IScene *> &scene, Engine &engine) : _engine(&engine), _scene(scene)
{
}

/**
 * @brief Find and retrieve an entity from a specified scene.
 *
 * This function allows you to find and retrieve an entity by its name from a specified scene within the EntityManager.
 *
 * @param sceneName A string specifying the name of the scene in which the entity is located.
 * @param entityName A string specifying the name of the entity to be retrieved.
 *
 * @return A reference to the IEntity object representing the found entity.
 */
IEntity &EntityManager::findEntity(std::string sceneName, std::string entityName)
{
    if (sceneName.empty() || sceneName.c_str() == nullptr || sceneName.c_str()[0] == '\0')
        throw EntityException("EntityManager.findEntity error: Empty or invalid scene name passed as parameter\n");
    if (entityName.empty() || entityName.c_str() == nullptr || entityName.c_str()[0] == '\0')
        throw EntityException("EntityManager.findEntity error: Empty or invalid entity name passed as parameter\n");
    auto scene = this->_scene.find(sceneName);
    if (scene == this->_scene.end())
        throw EntityException("EntityManager.findEntity error: Scene with the name '" + sceneName + "' not found in the engine\n");

    IScene *sceneObject = scene->second;
    std::map<std::string, IEntity *> tmp = sceneObject->getEntity();
    auto entity = tmp.find(entityName);
    if (entity == tmp.cend())
        throw EntityException("EntityManager.findEntity error: Entity with the name '" + entityName + "' not found in the specified scene\n");
    IEntity &finalEntity = *entity->second;
    return (finalEntity);
}

bool EntityManager::searchEntity(std::string sceneName, std::string entityName)
{
    if (sceneName.empty() || sceneName.c_str() == nullptr || sceneName.c_str()[0] == '\0')
        throw EntityException("EntityManager.findEntity error: Empty or invalid scene name passed as parameter\n");
    if (entityName.empty() || entityName.c_str() == nullptr || entityName.c_str()[0] == '\0')
        throw EntityException("EntityManager.findEntity error: Empty or invalid entity name passed as parameter\n");
    auto scene = this->_scene.find(sceneName);
    if (scene == this->_scene.end())
        return (false);

    IScene *sceneObject = scene->second;
    std::map<std::string, IEntity *> tmp = sceneObject->getEntity();
    auto entity = tmp.find(entityName);
    if (entity == tmp.cend())
        return (false);
    return (true);
}

/**
 * @brief Add a texture to a specified entity within a scene.
 *
 * This function allows you to add a texture to a specified entity within a scene. It first locates the entity by name and checks if
 * it has a Visual Component. If a Visual Component is found, the texture is set to the entity's Visual Component.
 *
 * @param sceneName A string specifying the name of the scene where the entity is located.
 * @param entityName A string specifying the name of the entity to which the texture will be added.
 * @param texturePath A string specifying the file path to the texture to be added.
 */
void EntityManager::addTexture(std::string sceneName, std::string entityName, std::string texturePath)
{
    IEntity &finalEntity = this->findEntity(sceneName, entityName);

    Visual *comp = (Visual *)finalEntity.getComponent(VISUAL);

    if (!comp)
        throw EntityException("EntityManager.addTextureToEntity error: The entity '" + entityName + "' has no Visual Component\n");
    comp->setTextureFromFile(texturePath);
}

/**
 * @brief Set the position of a specified entity within a scene.
 *
 * This function allows you to set the position of a specified entity within a scene. It locates the entity by name and checks if it has a Position Component.
 * If a Position Component is found, the position is set to the entity's Position Component using the provided coordinates.
 *
 * @param sceneName A string specifying the name of the scene where the entity is located.
 * @param entityName A string specifying the name of the entity whose position will be set.
 * @param position A vector of two integers representing the new X and Y coordinates.
 */
void EntityManager::addPosition(std::string sceneName, std::string entityName, std::vector<int> position)
{
    IEntity &finalEntity = this->findEntity(sceneName, entityName);

    Position *comp = (Position *)finalEntity.getComponent(POSITION);

    if (!comp)
        throw EntityException("EntityManager.addPositionToEntity error: The entity '" + entityName + "' has no Position Component\n");
    comp->setPosition(position.at(0), position.at(1));
}

/**
 * @brief Get the position of a specified entity within a scene.
 *
 * This function allows you to retrieve the current position of a specified entity within a scene. It locates the entity by name and checks if it has a Position Component.
 * If a Position Component is found, it returns a vector containing the X and Y coordinates of the entity's position.
 *
 * @param sceneName A string specifying the name of the scene where the entity is located.
 * @param entityName A string specifying the name of the entity whose position will be retrieved.
 *
 * @return A vector of two integers representing the X and Y coordinates of the entity's position.
 */
std::vector<int> &EntityManager::getPositionOfEntity(std::string sceneName, std::string entityName)
{
    IEntity &finalEntity = this->findEntity(sceneName, entityName);

    Position *comp = (Position *)finalEntity.getComponent(POSITION);

    if (!comp)
        throw EntityException("EntityManager.getPositionOfEntity error: The entity '" + entityName + "' has no Position Component\n");
    return (comp->getPostion());
}

/**
 * @brief Get the components of a specified entity within a scene.
 *
 * This function allows you to retrieve the components associated with a specified entity within a scene. It locates the entity by name and returns a vector of components attached to the entity.
 *
 * @param sceneName A string specifying the name of the scene where the entity is located.
 * @param entityName A string specifying the name of the entity whose components will be retrieved.
 *
 * @return A vector of pointers to the components attached to the entity.
 */
std::vector<IComponent *> &EntityManager::getComponent(std::string sceneName, std::string entityName)
{
    if (sceneName.empty() || sceneName.c_str() == nullptr || sceneName.c_str()[0] == '\0')
        throw EntityException("EntityManager.getComponentOfEntity error: Empty or invalid scene name passed as parameter\n");
    if (entityName.empty() || entityName.c_str() == nullptr || entityName.c_str()[0] == '\0')
        throw EntityException("EntityManager.getComponentOfEntity error: Empty or invalid entity name passed as parameter\n");

    auto scene = this->_scene.find(sceneName);
    if (scene == this->_scene.end())
        throw EntityException("EntityManager.getComponentOfEntity error: Scene with the name '" + sceneName + "' not found in the engine\n");

    auto entity = scene->second->getEntity().find(entityName);
    if (entity == scene->second->getEntity().end())
        throw EntityException("EntityManager.getComponentOfEntity error: Entity with the name '" + entityName + "' not found in the scene\n");

    return (entity->second->GetCurrentComponent());
}

IComponent *EntityManager::getComponent(std::string sceneName, std::string entityName, ComponentType_t comp)
{
    if (sceneName.empty() || sceneName.c_str() == nullptr || sceneName.c_str()[0] == '\0')
        throw EntityException("EntityManager.getComponent error: Empty or invalid scene name passed as parameter\n");
    if (entityName.empty() || entityName.c_str() == nullptr || entityName.c_str()[0] == '\0')
        throw EntityException("EntityManager.getComponent error: Empty or invalid entity name passed as parameter\n");

    auto scene = this->_scene.find(sceneName);
    if (scene == this->_scene.end())
        throw EntityException("EntityManager.getComponent error: Scene with the name '" + sceneName + "' not found in the engine\n");

    auto entity = scene->second->getEntity().find(entityName);
    if (entity == scene->second->getEntity().end())
        throw EntityException("EntityManager.getComponent error: Entity with the name '" + entityName + "' not found in the scene\n");
    return (entity->second->getComponent(comp));
}

/**
 * @brief Get the current rectangle associated with a specified entity's Visual Component.
 *
 * This function allows you to retrieve the current rectangle associated with the Visual Component of a specified entity within a scene. It locates the entity by name, checks if it has a Visual Component, and returns the current rectangle.
 *
 * @param sceneName A string specifying the name of the scene where the entity is located.
 * @param entityName A string specifying the name of the entity whose Visual Component's rectangle will be retrieved.
 *
 * @return The current rectangle (sf::IntRect) associated with the Visual Component of the entity.
 */
const sf::IntRect &EntityManager::getRect(std::string sceneName, std::string entityName)
{
    IEntity &finalEntity = this->findEntity(sceneName, entityName);

    Visual *comp = (Visual *)finalEntity.getComponent(VISUAL);

    if (!comp)
        throw EntityException("EntityManager.getRect error: The entity '" + entityName + "' has no Visual Component\n");
    return comp->getRect();
}

/**
 * @brief Get the default rectangle associated with a specified entity's Visual Component.
 *
 * This function allows you to retrieve the default rectangle associated with the Visual Component of a specified entity within a scene. It locates the entity by name, checks if it has a Visual Component, and returns the default rectangle. The default rectangle is the initial or default configuration of the Visual Component.
 *
 * @param sceneName A string specifying the name of the scene where the entity is located.
 * @param entityName A string specifying the name of the entity whose Visual Component's default rectangle will be retrieved.
 *
 * @return The default rectangle (sf::IntRect) associated with the Visual Component of the entity.
 */
sf::IntRect EntityManager::getDefaultRect(std::string sceneName, std::string entityName)
{
    IEntity &finalEntity = this->findEntity(sceneName, entityName);

    Visual *comp = (Visual *)finalEntity.getComponent(VISUAL);

    if (!comp)
        throw EntityException("EntityManager.getRect error: The entity '" + entityName + "' has no Visual Component\n");
    return comp->getDefaultRect();
}

/**
 * @brief Set the rectangle associated with a specified entity's Visual Component.
 *
 * This function allows you to set the rectangle associated with the Visual Component of a specified entity within a scene. It locates the entity by name, checks if it has a Visual Component, and sets the new rectangle. The rectangle defines the dimensions and position within the entity's visual representation.
 *
 * @param sceneName A string specifying the name of the scene where the entity is located.
 * @param entityName A string specifying the name of the entity whose Visual Component's rectangle will be set.
 * @param rect An `sf::IntRect` representing the new rectangle to set for the entity's Visual Component.
 */
void EntityManager::setRect(std::string sceneName, std::string entityName, sf::IntRect rect)
{
    IEntity &finalEntity = this->findEntity(sceneName, entityName);

    Visual *comp = (Visual *)finalEntity.getComponent(VISUAL);

    if (!comp)
        throw EntityException("EntityManager.setRect error: The entity '" + entityName + "' has no Visual Component\n");
    comp->setRect(rect);
}

/**
 * @brief Set the scale associated with a specified entity's Visual Component.
 *
 * This function allows you to set the scale associated with the Visual Component of a specified entity within a scene. It locates the entity by name, checks if it has a Visual Component, and sets the new scale. The scale determines how the entity's visual representation is resized in both height and width.
 *
 * @param sceneName A string specifying the name of the scene where the entity is located.
 * @param entityName A string specifying the name of the entity whose Visual Component's scale will be set.
 * @param scale A vector of two floating-point values representing the new scale factors for height and width, respectively.
 */
void EntityManager::setScale(std::string sceneName, std::string entityName, std::vector<float> scale)
{
    IEntity &finalEntity = this->findEntity(sceneName, entityName);

    Visual *comp = (Visual *)finalEntity.getComponent(VISUAL);

    if (!comp)
        throw EntityException("EntityManager.setScale error: The entity '" + entityName + "' has no Visual Component\n");
    comp->setScale(scale.at(0), scale.at(1));
}

/**
 * @brief Set the visibility state of a specified entity's Visual Component.
 *
 * This function allows you to set the visibility state of the Visual Component of a specified entity within a scene. It locates the entity by name, checks if it has a Visual Component, and sets the visibility state. The visibility state controls whether the entity's visual representation is displayed or hidden.
 *
 * @param sceneName A string specifying the name of the scene where the entity is located.
 * @param entityName A string specifying the name of the entity whose Visual Component's visibility state will be set.
 * @param state A boolean value that specifies whether the entity's Visual Component should be visible (true) or hidden (false).
 */
void EntityManager::setVisibility(std::string sceneName, std::string entityName, bool state)
{
    IEntity &finalEntity = this->findEntity(sceneName, entityName);

    Visual *comp = (Visual *)finalEntity.getComponent(VISUAL);

    if (!comp)
        throw EntityException("EntityManager.setVisibility error: The entity '" + entityName + "' has no Visual Component\n");
    comp->visibleState(state);
}

/**
 * @brief Check the visibility state of a specified entity's Visual Component.
 *
 * This function allows you to check the visibility state of the Visual Component of a specified entity within a scene. It locates the entity by name, verifies if it has a Visual Component, and retrieves the current visibility state. The visibility state controls whether the entity's visual representation is displayed or hidden.
 *
 * @param sceneName A string specifying the name of the scene where the entity is located.
 * @param entityName A string specifying the name of the entity whose Visual Component's visibility state will be checked.
 *
 * @return A reference to a boolean value indicating whether the entity's Visual Component is currently visible (true) or hidden (false).
 */
bool &EntityManager::isVisible(std::string sceneName, std::string entityName)
{
    IEntity &finalEntity = this->findEntity(sceneName, entityName);

    Visual *comp = (Visual *)finalEntity.getComponent(VISUAL);

    if (!comp)
        throw EntityException("EntityManager.isVisible error: The entity '" + entityName + "' has no Visual Component\n");
    return (comp->isVisible());
}

/**
 * @brief Check if an entity is clicked based on a specific input and mouse position.
 *
 * This function allows you to check if a specified entity is clicked. It verifies whether the entity's Visual Component is visible, checks if the specified input (e.g., mouse button) matches the input received, and compares the mouse position with the entity's position and dimensions. If all conditions are met, the function returns true, indicating that the entity is clicked.
 *
 * @param sceneName A string specifying the name of the scene where the entity is located.
 * @param entityName A string specifying the name of the entity to be checked for a click event.
 * @param input A keyboardInput_t representing the input event to be checked (e.g., a mouse button click).
 *
 * @return A boolean value indicating whether the entity is clicked (true) or not (false).
 */
bool EntityManager::isClicked(std::string sceneName, std::string entityName, keyboardInput_t input)
{
    IEntity &finalEntity = this->findEntity(sceneName, entityName);

    Visual *comp = (Visual *)finalEntity.getComponent(VISUAL);

    if (!comp)
        throw EntityException("EntityManager.isVisible error: The entity '" + entityName + "' has no Visual Component\n");

    if (this->_engine->event->getMouseClick() == input &&
    this->_engine->window->getMousePosition().x >= this->_engine->entity->getPositionOfEntity(sceneName, entityName).at(0) &&
    this->_engine->window->getMousePosition().y >= this->_engine->entity->getPositionOfEntity(sceneName, entityName).at(1) &&
    this->_engine->window->getMousePosition().x <= this->_engine->entity->getRect(sceneName, entityName).width + this->_engine->entity->getPositionOfEntity(sceneName, entityName).at(0) &&
    this->_engine->window->getMousePosition().y <= this->_engine->entity->getRect(sceneName, entityName).height + this->_engine->entity->getPositionOfEntity(sceneName, entityName).at(1)) {
        return true;
    }
    return false;
}

/**
 * @brief Check if the mouse pointer is hovering over a specific entity.
 *
 * This function allows you to check if the mouse pointer is hovering over a specified entity. It verifies whether the entity's Visual Component is visible and compares the mouse position with the entity's position and dimensions. If the mouse pointer is over the entity, the function returns true; otherwise, it returns false.
 *
 * @param sceneName A string specifying the name of the scene where the entity is located.
 * @param entityName A string specifying the name of the entity to be checked for hover.
 *
 * @return A boolean value indicating whether the mouse pointer is hovering over the entity (true) or not (false).
 */
bool EntityManager::isHover(std::string sceneName, std::string entityName)
{
    IEntity &finalEntity = this->findEntity(sceneName, entityName);

    Visual *comp = (Visual *)finalEntity.getComponent(VISUAL);

    if (!comp)
        throw EntityException("EntityManager.isVisible error: The entity '" + entityName + "' has no Visual Component\n");

    if (this->_engine->window->getMousePosition().x >= this->_engine->entity->getPositionOfEntity(sceneName, entityName).at(0) &&
    this->_engine->window->getMousePosition().y >= this->_engine->entity->getPositionOfEntity(sceneName, entityName).at(1) &&
    this->_engine->window->getMousePosition().x <= this->_engine->entity->getRect(sceneName, entityName).width + this->_engine->entity->getPositionOfEntity(sceneName, entityName).at(0) &&
    this->_engine->window->getMousePosition().y <= this->_engine->entity->getRect(sceneName, entityName).height + this->_engine->entity->getPositionOfEntity(sceneName, entityName).at(1)) {
        return true;
    }
    return false;
}

/**
 * @brief Refresh the scene map with new scene data.
 *
 * This function updates the internal scene map with new scene data, allowing the `EntityManager` to work with the updated scene information. It replaces the existing scene map with the provided `newScene` map.
 *
 * @param newScene A map containing the new scene data with scene names as keys and `IScene` pointers as values.
 */
void EntityManager::refreshScene(std::map<std::string, IScene *> newScene)
{
    this->_scene = newScene;
}

void EntityManager::setID(std::string sceneName, std::string entityName, unsigned int id)
{
    IEntity &finalEntity = this->findEntity(sceneName, entityName);

    std::vector<IComponent *> entityComp = finalEntity.GetCurrentComponent();

    bool IDComp = false;
    ID *comp;
    (void)comp;

    for (size_t i = 0; i!= entityComp.size(); i++) {
        if (entityComp.at(i)->GetType() == _ID_) {
            comp = dynamic_cast<ID *>(entityComp.at(i));
            IDComp = true;
        }
    }

    if (!IDComp)
        throw EntityException("EntityManager.setID error: The entity '" + entityName + "' has no ID Component\n");
    comp->setID(id);
}

unsigned int &EntityManager::getID(std::string sceneName, std::string entityName)
{
    IEntity &finalEntity = this->findEntity(sceneName, entityName);

    std::vector<IComponent *> entityComp = finalEntity.GetCurrentComponent();

    bool IDComp = false;
    ID *comp;
    (void)comp;

    for (size_t i = 0; i!= entityComp.size(); i++) {
        if (entityComp.at(i)->GetType() == _ID_) {
            comp = dynamic_cast<ID *>(entityComp.at(i));
            IDComp = true;
        }
    }

    if (!IDComp)
        throw EntityException("EntityManager.getID error: The entity '" + entityName + "' has no ID Component\n");
    return (comp->getID());
}

void EntityManager::setTag(std::string sceneName, std::string entityName, std::string tag)
{
    IEntity &finalEntity = this->findEntity(sceneName, entityName);

    std::vector<IComponent *> entityComp = finalEntity.GetCurrentComponent();

    bool IDComp = false;
    ID *comp;
    (void)comp;

    for (size_t i = 0; i!= entityComp.size(); i++) {
        if (entityComp.at(i)->GetType() == _ID_) {
            comp = dynamic_cast<ID *>(entityComp.at(i));
            IDComp = true;
        }
    }

    if (!IDComp)
        throw EntityException("EntityManager.setTag error: The entity '" + entityName + "' has no ID Component\n");
    comp->setTag(tag);
}

std::string &EntityManager::getTag(std::string sceneName, std::string entityName)
{
    IEntity &finalEntity = this->findEntity(sceneName, entityName);

    std::vector<IComponent *> entityComp = finalEntity.GetCurrentComponent();

    bool IDComp = false;
    ID *comp;
    (void)comp;

    for (size_t i = 0; i!= entityComp.size(); i++) {
        if (entityComp.at(i)->GetType() == _ID_) {
            comp = dynamic_cast<ID *>(entityComp.at(i));
            IDComp = true;
        }
    }

    if (!IDComp)
        throw EntityException("EntityManager.getTag error: The entity '" + entityName + "' has no ID Component\n");
    return (comp->getTag());
}

EntityManager::~EntityManager()
{
    delete (this->_engine);
}
