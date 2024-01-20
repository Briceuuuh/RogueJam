/*
** EPITECH PROJECT, 2023
** B-CPP-500-RUN-5-1-rtype-florian.etheve
** File description:
** SystemManager
*/

#include "SystemManager.hpp"

/**
 * @brief Construct a new SystemManager object.
 *
 * The SystemManager class is responsible for managing the game systems and interactions within the engine. It uses a System object to perform various game-related tasks.

 * @param engine A reference to the Engine object to which this SystemManager is associated.
 */
SystemManager::SystemManager(Engine &engine)
{
    this->_system = new System(engine);
}

/**
 * @brief Destroy the SystemManager object.
 *
 * The destructor for the SystemManager class deletes the System object it owns to prevent memory leaks.
 */
SystemManager::~SystemManager()
{
    delete this->_system;
}

/**
 * @brief Change the scene when a specific entity is clicked.
 *
 * This function triggers a scene change when a specific entity is clicked. The scene transition is controlled by the key specified.

 * @param entityToClick The name of the entity that, when clicked, triggers the scene change.
 * @param actualScene The name of the current scene.
 * @param nextScene The name of the scene to transition to.
 * @param keyToPress The keyboard input key that, when pressed, initiates the scene change.
 */
void SystemManager::changeSceneOnClick(std::string entityToClick, std::string actualScene, std::string nextScene, keyboardInput_t keyToPress)
{
    this->_system->changeSceneOnClick(entityToClick, actualScene, nextScene, keyToPress);
}

/**
 * @brief Perform the scene change based on previous triggers.
 *
 * This function executes the scene change process based on the triggers set using the `changeSceneOnClick` method.
 */
void SystemManager::changeSceneSystem()
{
    this->_system->changeSceneSystem();
}

/**
 * @brief Change the sprite's rectangle when an entity is hovered.
 *
 * This function changes the sprite's rectangle when an entity is hovered over, creating an interactive effect on the entity's appearance.

 * @param sceneName The name of the scene.
 * @param entityToHover The name of the entity to apply the hover effect to.
 * @param hoverRect The new rectangle to set for the entity's sprite when hovered over.
 */
void SystemManager::changeSpriteRectOnHover(std::string sceneName, std::string entityToHover, sf::IntRect hoverRect)
{
    this->_system->changeSpriteRectOnHover(sceneName, entityToHover, hoverRect);
}

/**
 * @brief Perform the sprite rectangle changes based on entity hovering.
 *
 * This function executes the changes in sprite rectangles based on the hover effect triggers set using the `changeSpriteRectOnHover` method.
 */
void SystemManager::changeSpriteRectSystem()
{
    this->_system->changeSpriteRectSystem();
}

/**
 * @brief Interpret and process player input keys.
 *
 * This function interprets and processes the input from player-controlled entities, allowing the player to interact with the game world based on the assigned keys.
 */
void SystemManager::playerKeysInterpretation(keyboardInput_t key, const MainLoopCallback& callback)
{
    this->_system->playerKeysInterpretation(key, callback);
}

void SystemManager::moveEntitySystem(std::string entityName, std::string room, std::vector<bool> movement, float speed, bool remove)
{
    this->_system->moveEntitySystem(entityName, room, movement, speed, remove);
}

void SystemManager::moveEntitySpecificSystem(std::string specificTagName, std::string room, std::vector<bool> movement, float speed)
{
    this->_system->moveEntitySpecificSystem(specificTagName, room, movement, speed);
}

void SystemManager::shootSystem(std::string entityName, std::string room, float speed)
{
    this->_system->shootSystem(entityName, room, speed);
}

void SystemManager::shootSpecificSystem(std::string specificTagName, std::string room)
{
    this->_system->shootSpecificSystem(specificTagName, room);
}

bool SystemManager::collisionSystem(std::string entity_name1, std::string entity_name2, std::string room, bool dammage, int nb_dammage, bool removeEnt1, bool removeEnt2)
{
    return (this->_system->collisionSystem(entity_name1, entity_name2, room, dammage, nb_dammage, removeEnt1, removeEnt2));
}

bool SystemManager::checkCollision(Position *pos1, std::vector<float> rocketSize, Position *pos2, std::vector<float> enemySize)
{
    return this->_system->checkCollision(pos1, rocketSize, pos2, enemySize);
}