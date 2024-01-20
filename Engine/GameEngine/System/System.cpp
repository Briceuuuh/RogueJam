/*
** EPITECH PROJECT, 2023
** B-CPP-500-RUN-5-1-rtype-florian.etheve
** File description:
** System
*/

#include "System.hpp"

keyboardInput_t getKeyBinded(std::tuple<std::string, std::string, std::vector<keyboardInput_t>> keyOfEntity, int index)
{
    return (std::get<2>(keyOfEntity).at(index));
}

System::System(Engine &engine)
{
    this->_engine = &engine;
    this->_engine->clock->createClock("rocket");
    this->_engine->clock->createClock("player");
}

/**
 * @brief Defines a scene change action on button click for a specific entity.
 *
 * This function is used to specify an action to change the active scene when a specific button, associated with
 * a particular entity and scene, is clicked. It ensures that the provided parameters are valid, checks if the
 * specified entity can be clicked, and adds the scene change action to the `_actionButton` collection.
 *
 * @param entityToClick The name of the entity with the clickable button.
 * @param actualScene The name of the current scene in which the entity exists.
 * @param nextScene The name of the scene to switch to upon button click.
 * @param keyToPress The keyboard input key required to trigger the click action.
 */
void System::changeSceneOnClick(std::string entityToClick, std::string actualScene, std::string nextScene, keyboardInput_t keyToPress)
{
    if (entityToClick.empty() || entityToClick.c_str() == nullptr || entityToClick.c_str()[0] == '\0')
        throw SystemException("System.changeSceneOnClick error: Empty or invalid entity '" + entityToClick + "' passed as parameter\n");
    if (actualScene.empty() || actualScene.c_str() == nullptr || actualScene.c_str()[0] == '\0')
        throw SystemException("System.changeSceneOnClick error: Empty or invalid actual scene '" + actualScene + "' passed as parameter\n");
    if (nextScene.empty() || nextScene.c_str() == nullptr || nextScene.c_str()[0] == '\0')
        throw SystemException("System.changeSceneOnClick error: Empty or invalid next scene '" + nextScene + "' passed as parameter\n");

    IEntity *ent = &this->_engine->scene->getEntityFromScene(actualScene, entityToClick);
    if (ent == nullptr)
        throw SystemException("System.changeSceneOnClick error: Entity '" + entityToClick + "' is null\n");
    std::vector<IComponent *> comp = ent->GetCurrentComponent();
    bool valid = false;

    for (size_t i = 0; i != comp.size(); i++) {
        if (comp.at(i)->GetType() == VISUAL)
            valid = true;
    }
    if (!valid)
        throw SystemException("System.changeSceneOnClick error: Entity '" + entityToClick + "' can't be click because he has no Visual Component\n");

    std::tuple<std::string, std::string, std::string, keyboardInput_t> actionToAdd = std::make_tuple(entityToClick, actualScene, nextScene, keyToPress);

    for (auto &find : this->_actionButton) {
        if (std::get<0>(find) == std::get<0>(actionToAdd) && std::get<1>(find) == std::get<1>(actionToAdd) && (std::get<2>(find) == std::get<2>(actionToAdd)) && std::get<3>(find) == std::get<3>(actionToAdd))
            throw SystemException("System.changeSceneOnClick error: Entity '" + entityToClick + "' in the scene '" + actualScene + "' already have an hover action in the scene\n");
    }
    this->_engine->scene->getScene(std::get<2>(actionToAdd));
    this->_actionButton.push_back(actionToAdd);
}

/**
 * @brief Handles changing the active scene based on button clicks.
 *
 * This function is responsible for managing scene changes based on button clicks. It iterates through the `_actionButton`
 * collection and checks if a specified button within a specific entity and scene is clicked. If the button is clicked,
 * it changes the active scene to the one specified in the tuple.
 */
void System::changeSceneSystem()
{
    for (size_t i = 0; i != this->_actionButton.size(); i++) {
        std::tuple<std::string, std::string, std::string, keyboardInput_t> line = this->_actionButton.at(i);
        if (this->_engine->entity->isClicked(std::get<1>(line), std::get<0>(line), std::get<3>(line)) && this->_engine->scene->getActualScene() == std::get<1>(line))
            this->_engine->scene->setActualScene(std::get<2>(line));

    }
}

/**
 * @brief Defines a sprite rectangle change action on hover for an entity in a specific scene.
 *
 * This function is used to specify an action to change the sprite rectangle of an entity when it is hovered over
 * within a particular scene. It ensures that the provided parameters are valid, checks if the specified entity
 * can be hovered over, and adds the hover action to the `_hoverAction` collection.
 *
 * @param sceneName The name of the scene in which the entity exists.
 * @param entityToHover The name of the entity for which the hover action is defined.
 * @param hoverRect The `sf::IntRect` representing the new sprite rectangle to set when the entity is hovered over.
 */
void System::changeSpriteRectOnHover(std::string sceneName, std::string entityToHover, sf::IntRect hoverRect)
{
    if (sceneName.empty() || sceneName.c_str() == nullptr || sceneName.c_str()[0] == '\0')
        throw SystemException("System.changeSpriteRectOnHover error: Empty or invalid scene passed as parameter\n");
    if (entityToHover.empty() || entityToHover.c_str() == nullptr || entityToHover.c_str()[0] == '\0')
        throw SystemException("System.changeSpriteRectOnHover error: Empty or invalid entity passed as parameter\n");

    IEntity *ent = &this->_engine->scene->getEntityFromScene(sceneName, entityToHover);
    if (ent == nullptr)
        throw SystemException("System.changeSpriteRectOnHover error: Entity '" + entityToHover + "' is null\n");
    std::vector<IComponent *> comp = ent->GetCurrentComponent();
    bool valid = false;

    for (size_t i = 0; i != comp.size(); i++) {
        if (comp.at(i)->GetType() == VISUAL)
            valid = true;
    }
    if (!valid)
        throw SystemException("System.changeSpriteRectOnHover error: Entity '" + entityToHover + "' can't be hovered because he has no Visual Component\n");

    std::tuple<std::string, std::string, sf::IntRect> hoverToAdd = std::make_tuple(entityToHover, sceneName, hoverRect);


    for (auto &find : this->_hoverAction) {
        if (std::get<0>(find) == std::get<0>(hoverToAdd)  && std::get<1>(find) == std::get<1>(hoverToAdd))
            throw SystemException("System.changeSpriteRectOnHover error: Entity '" + entityToHover + "' in the scene '" + sceneName + "' already have an hover action in the scene\n");
    }
    this->_hoverAction.push_back(hoverToAdd);
}

/**
 * @brief Handles changing sprite rectangles based on hover actions.
 *
 * This function is responsible for managing sprite rectangles and their changes based on hover actions.
 * It iterates through the `_hoverAction` collection and checks if the specified entity within a scene is being hovered over.
 * If the entity is hovered over, it sets the specified sprite rectangle; otherwise, it sets the default sprite rectangle.
 */
void System::changeSpriteRectSystem()
{
    for (size_t i = 0; i != this->_hoverAction.size(); i++) {
        std::tuple<std::string, std::string, sf::IntRect> line = this->_hoverAction.at(i);

        if (this->_engine->entity->isHover(std::get<1>(line), std::get<0>(line)))
            this->_engine->entity->setRect(std::get<1>(line), std::get<0>(line), std::get<2>(line));
        else
            this->_engine->entity->setRect(std::get<1>(line), std::get<0>(line), this->_engine->entity->getDefaultRect(std::get<1>(line), std::get<0>(line)));
    }
}

/**
 * @brief Interprets player input for movement and shooting actions.
 *
 * This function interprets player input for movement and shooting actions for each player configured
 * in the `_playerKeys` collection. It checks for key presses and mouse clicks associated with each
 * player and triggers corresponding actions. The actions include moving up, down, left, right, and shooting.
 */
void System::playerKeysInterpretation(keyboardInput_t key, const MainLoopCallback& callback)
{
    if (this->_engine->event->getKeyPressed() == key || this->_engine->event->getMouseClick() == key) {
        callback();
    }
}

void System::moveEntitySystem(std::string entityName, std::string room, std::vector<bool> movement, float speed, bool remove)
{
    std::map<std::string, IEntity *> ent = this->_engine->scene->getAllEntityFromScene(room);

    for (auto line = ent.begin(); line != ent.end(); line++) {
        ID *idcomp = (ID *)line->second->getComponent(_ID_);
        Position *poscomp = (Position *)line->second->getComponent(POSITION);
        Visual *visu = (Visual *)line->second->getComponent(VISUAL);

        if (idcomp && idcomp->getTag() == entityName) {
            if (movement.at(0) == true) {
                if (poscomp && (poscomp->getPostion().at(1) - speed) > 0 && (poscomp->getPostion().at(1) - speed) < this->_engine->window->getDimension().at(1)) {
                    poscomp->setPosition(poscomp->getPostion().at(0), (poscomp->getPostion().at(1) - speed));
                }
                else if (poscomp && remove) {
                    this->_engine->scene->removeEntitytoScene(room, *line->second);
                    this->_engine->entity->refreshScene(this->_engine->scene->getScene());
                }
            }
            if (movement.at(1) == true) {
                if (poscomp && ((poscomp->getPostion().at(1) + visu->getScale().at(1)) + speed) > 0 && ((poscomp->getPostion().at(1) + visu->getScale().at(1)) + speed) < this->_engine->window->getDimension().at(1)) {
                    poscomp->setPosition(poscomp->getPostion().at(0), poscomp->getPostion().at(1) + speed);
                }
                else if (poscomp && remove) {
                    this->_engine->scene->removeEntitytoScene(room, *line->second);
                    this->_engine->entity->refreshScene(this->_engine->scene->getScene());
                }
            }
            if (movement.at(2) == true) {
                if (poscomp && (poscomp->getPostion().at(0) - speed) > 0 && (poscomp->getPostion().at(0) - speed) < this->_engine->window->getDimension().at(0)) {
                    poscomp->setPosition(poscomp->getPostion().at(0) - speed, poscomp->getPostion().at(1));
                }
                else if (poscomp && remove) {
                    this->_engine->scene->removeEntitytoScene(room, *line->second);
                    this->_engine->entity->refreshScene(this->_engine->scene->getScene());
                }
            }
            if (movement.at(3) == true) {
                if (poscomp && ((poscomp->getPostion().at(0) + visu->getScale().at(0)) + speed) > 0 && ((poscomp->getPostion().at(0) + visu->getScale().at(0)) + speed) < this->_engine->window->getDimension().at(0)) {
                    poscomp->setPosition(poscomp->getPostion().at(0) + speed, poscomp->getPostion().at(1));
                }
                else if (poscomp && remove) {
                    this->_engine->scene->removeEntitytoScene(room, *line->second);
                    this->_engine->entity->refreshScene(this->_engine->scene->getScene());
                }
            }
        }
    }
}

/**
 * @brief Move an entity within a specific room based on user-defined movement.
 *
 * @param specificTagName The unique tag identifying the entity to move.
 * @param room The name of the room in which the entity is located.
 * @param movement A vector representing movement in four directions (up, down, left, right).
 * @param speed The speed at which the entity should move.
 */
void System::moveEntitySpecificSystem(std::string specificTagName, std::string room, std::vector<bool> movement, float speed)
{
    IEntity &ent = this->_engine->scene->getEntityFromScene(room, specificTagName);

    Position *comp = (Position *)ent.getComponent(POSITION);
    Visual *visu = (Visual *)ent.getComponent(VISUAL);

    if (!comp)
        return;

    if (movement.at(0) == true && comp && (comp->getPostion().at(1) - speed) > 0 && (comp->getPostion().at(1) - speed) < this->_engine->window->getDimension().at(1))
        comp->setPosition(comp->getPostion().at(0), (comp->getPostion().at(1) - speed));
    if (movement.at(1) == true && comp && ((comp->getPostion().at(1) + visu->getScale().at(1)) + speed) > 0 && ((comp->getPostion().at(1) + visu->getScale().at(1)) + speed) < this->_engine->window->getDimension().at(1))
        comp->setPosition(comp->getPostion().at(0), (comp->getPostion().at(1) + speed));
    if (movement.at(2) == true && comp && (comp->getPostion().at(0) - speed) > 0 && (comp->getPostion().at(0) - speed) < this->_engine->window->getDimension().at(0))
        comp->setPosition((comp->getPostion().at(0) - speed), comp->getPostion().at(1));
    if (movement.at(3) == true && comp && ((comp->getPostion().at(0) + visu->getScale().at(0)) + speed) > 0 && ((comp->getPostion().at(0) + visu->getScale().at(0)) + speed) < this->_engine->window->getDimension().at(0))
        comp->setPosition((comp->getPostion().at(0) + speed), comp->getPostion().at(1));
}

/**
 * @brief Create and shoot rockets from a specific entity within a room at a given speed.
 *
 * @param entityName The name or tag of the entity that is shooting rockets.
 * @param room The name of the room in which the entity is located.
 * @param speed The speed at which rockets are created and shot.
 */
void System::shootSystem(std::string entityName, std::string room, float speed)
{
    if (this->_engine->clock->getTimeElapsed("rocket") > speed) {
        std::map<std::string, IEntity *> ent = this->_engine->scene->getAllEntityFromScene(room);

        for (auto line = ent.begin(); line != ent.end(); line++) {
            ID *idcomp = (ID *)line->second->getComponent(_ID_);
            Position *poscomp = (Position *)line->second->getComponent(POSITION);

            if (idcomp && idcomp->getTag() == entityName) {
                std::map<std::string, IEntity *> search = this->_engine->scene->getAllEntityFromScene(room);
                int tmp = 0;
                for (auto line_search = search.begin(); line_search != search.end(); line_search++) {
                    ID *idcomp_search = (ID *)line_search->second->getComponent(_ID_);
                    if (idcomp_search && idcomp_search->getTag() == "rocket_ennemy") {
                        std::istringstream ss(line->second->getName());
                        std::vector<std::string> tokens;
                        std::string token;

                        while (ss >> token) {
                            tokens.push_back(token);
                        }
                        if (tokens.size() == 3 && std::atoi(tokens.at(2).c_str()) > tmp)
                            tmp = std::atoi(tokens.at(2).c_str());
                        tmp++;
                    }
                }
                std::string rocketid = "rocket " + entityName + " " + std::to_string(tmp);
                this->_engine->scene->addEntitytoScene(room, rocketid);
                this->_engine->entity->addComponent(room, rocketid, DAMAGE, HEALTH, HITBOX, MOBILITY, POSITION, VISUAL, _ID_);
                this->_engine->entity->addTexture(room, rocketid, "./Client/assets/missile.png");
                this->_engine->entity->addPosition(room, rocketid, {poscomp->getPostion().at(0), (poscomp->getPostion().at(1) + 30)});
                this->_engine->entity->setTag(room, rocketid, "rocket_ennemy");
            }
        }
        this->_engine->clock->restart("rocket");
    }
}

/**
 * @brief Create and shoot rockets from a specific entity within a room.
 *
 * @param specificTagName The unique tag identifying the entity to shoot rockets from.
 * @param room The name of the room in which the entity is located.
 */
void System::shootSpecificSystem(std::string specificTagName, std::string room)
{
    IEntity &ent = this->_engine->scene->getEntityFromScene(room, specificTagName);
    std::vector<IComponent *> entityComp = ent.GetCurrentComponent();

    bool PositionComp = false;
    bool PlayerComp = false;
    Position *comp;

    for (size_t i = 0; i!= entityComp.size(); i++) {
        if (entityComp.at(i)->GetType() == POSITION) {
            comp = (Position *)entityComp.at(i);
            PositionComp = true;
        }
        if (entityComp.at(i)->GetType() == PLAYER) {
            PlayerComp = true;
        }
    }

    if (!PositionComp || !PlayerComp)
        return;
    int tmp = 0;
    std::map<std::string, IEntity *> shoot = this->_engine->scene->getAllEntityFromScene(room);

    for (auto line = shoot.begin(); line != shoot.end(); line++) {
        ID *idcomp = (ID *)line->second->getComponent(_ID_);
        if (idcomp && idcomp->getTag() == "rocket_player") {
            std::istringstream ss(line->second->getName());
            std::vector<std::string> tokens;
            std::string token;

            while (ss >> token) {
                tokens.push_back(token);
            }
            if (tokens.size() == 3 && std::atoi(tokens.at(2).c_str()) > tmp)
                tmp = std::atoi(tokens.at(2).c_str());
            tmp++;
        }
    }
    std::string rocketid = "rocket " + specificTagName + " " + std::to_string(tmp);
    this->_engine->scene->addEntitytoScene(room, rocketid);
    this->_engine->entity->addComponent(room, rocketid, DAMAGE, HEALTH, HITBOX, MOBILITY, POSITION, VISUAL, _ID_);
    this->_engine->entity->addTexture(room, rocketid, "./Client/assets/missile.png");
    this->_engine->entity->addPosition(room, rocketid, {comp->getPostion().at(0), (comp->getPostion().at(1) + 30)});
    this->_engine->entity->setTag(room, rocketid, "rocket_player");
}

/**
 * @brief Check for collision between two entities using their positions and sizes.
 *
 * @param pos1 The Position component of the first entity.
 * @param rocketSize A vector representing the size of the first entity (e.g., rocket).
 * @param pos2 The Position component of the second entity (e.g., enemy).
 * @param enemySize A vector representing the size of the second entity (e.g., enemy).
 * @return true if the two entities collide, false otherwise.
 */
bool System::checkCollision(Position *pos1, std::vector<float> rocketSize, Position *pos2, std::vector<float> enemySize)
{
    return (pos1->getPostion().at(0) < pos2->getPostion().at(0) + enemySize.at(0) &&
            pos1->getPostion().at(0) + rocketSize.at(0) > pos2->getPostion().at(0) &&
            pos1->getPostion().at(1) < pos2->getPostion().at(1) + enemySize.at(1) &&
            pos1->getPostion().at(1) + rocketSize.at(1) > pos2->getPostion().at(1));
}

/**
 * @brief Check for collisions between a specific entity and other entities in a room.
 *
 * @param room The name of the room in which to check for collisions.
 * @param poscomp The Position component of the specific entity.
 * @param ent A map containing all entities in the specified room.
 * @param entity_name1 The tag of the specific entity to check for collisions with.
 * @param visualComp1 The Visual component of the specific entity.
 * @param removeEnt2 A boolean flag indicating whether to remove colliding entities.
 * @return true if a collision is detected, false otherwise.
 */
bool System::checksystem(std::string room, Position *poscomp, std::map<std::string, IEntity *> ent, std::string entity_name1, Visual *visualComp1, bool removeEnt2)
{
    if (!poscomp)
        return false;
    for (auto line = ent.begin(); line != ent.end(); line++) {
        if (!line->second)
            return false;
        std::vector<IComponent *> entityComp = line->second->GetCurrentComponent();
        ID *idcomp = nullptr;
        Position *poscomp2 = nullptr;
        Visual *visualComp2 = nullptr;
        for (size_t i = 0; i != entityComp.size(); i++) {
            if (entityComp.at(i)->GetType() == _ID_)
                idcomp = (ID *)entityComp.at(i);
            if (entityComp.at(i)->GetType() == POSITION)
                poscomp2 = (Position *)entityComp.at(i);
            if (entityComp.at(i)->GetType() == VISUAL)
                visualComp2 = (Visual *)entityComp.at(i);
        }
        if (idcomp && idcomp->getTag() == entity_name1) {
            bool collisionResult = checkCollision(poscomp, visualComp1->getScale(), poscomp2, visualComp2->getScale());
            if (collisionResult) {
                (void)room;
                if (removeEnt2)
                    this->_engine->scene->removeEntitytoScene(room, *line->second);
                return (true);
            }
        }
    }
    return (false);
}

/**
 * @brief Handle collisions and apply damage between two specified entities within a room.
 *
 * @param entity_name1 The tag of the first entity (e.g., the one causing the collision).
 * @param entity_name2 The tag of the second entity (e.g., the one receiving the collision).
 * @param room The name of the room where collisions are checked.
 * @param damage A boolean flag to indicate if damage should be applied upon collision.
 * @param nb_damage The amount of damage to be applied (if 'damage' is true).
 * @param removeEnt1 A boolean flag to remove the first entity upon collision.
 * @param removeEnt2 A boolean flag to remove the second entity upon collision.
 * @return true if a collision is detected and processed, false otherwise.
 */
bool System::collisionSystem(std::string entity_name1, std::string entity_name2, std::string room, bool dammage, int nb_dammage, bool removeEnt1, bool removeEnt2)
{
    std::map<std::string, IEntity *> ent = this->_engine->scene->getAllEntityFromScene(room);
    for (auto line = ent.begin(); line != ent.end(); line++) {
        std::vector<IComponent *> entityComp = line->second->GetCurrentComponent();
        ID *idcomp = (ID *)this->_engine->entity->getComponent(room, line->second->getName(), _ID_);
        Visual *visualcomp = (Visual *)this->_engine->entity->getComponent(room, line->second->getName(), VISUAL);
        Position *poscomp = (Position *)this->_engine->entity->getComponent(room, line->second->getName(), POSITION);
        Health *healthcomp = (Health *)this->_engine->entity->getComponent(room, line->second->getName(), HEALTH);
        if (idcomp && idcomp->getTag() == entity_name1) {
            if (checksystem(room, poscomp, ent, entity_name2, visualcomp, removeEnt2)) {
                if (dammage && healthcomp) {
                    if (healthcomp->getHealth() - nb_dammage >= 0) {
                        healthcomp->setHealth(healthcomp->getHealth() - nb_dammage);
                    }
                    else
                        healthcomp->setHealth(0);
                    healthcomp->getHealth();
                    // if (healthcomp->getHealth() == 0) {
                    //     this->_engine->scene->removeEntitytoScene(room, *line->second);
                    // }
                    if (removeEnt1)
                        this->_engine->scene->removeEntitytoScene(room, *line->second);
                }
                return true;
            }
        }
    }
    return (false);
}

System::~System()
{
    delete (this->_engine);
}
