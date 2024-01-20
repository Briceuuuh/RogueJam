/*
** EPITECH PROJECT, 2023
** B-CPP-500-RUN-5-1-rtype-florian.etheve
** File description:
** SceneManager
*/

#include "SceneManager.hpp"

SceneManager::SceneManager(Engine &engine)
{
    this->_engine = &engine;
}

SceneManager::~SceneManager()
{
    delete (this->_engine);
}

/**
 * @brief Create a new game scene.
 *
 * This function creates a new game scene with the specified name and adds it to the engine. If the scene name is already in use, it will raise an exception. Additionally, if no default or actual scenes are set, the newly created scene will become the default and actual scene, and the window and entity manager will be updated accordingly.

 * @param sceneName The name of the new game scene to be created.
 */
void SceneManager::createScene(std::string sceneName)
{
    if (sceneName.empty() || sceneName.c_str() == nullptr || sceneName.c_str()[0] == '\0')
        throw SceneManagerException("SceneManager.createScene error: Empty or invalid name passed as parameter\n");

    if (this->_scene.find(sceneName) != this->_scene.end())
        throw SceneManagerException("SceneManager.createScene error: Scene with the name '" + sceneName + "' already exist in the engine\n");
    IScene *scene = new Scene();
    scene->setName(sceneName);
    std::pair<std::string, IScene *> newline(sceneName, scene);

    this->_scene.insert(newline);

    if (this->getDefaultScene() == "None" || this->getActualScene() == "None" || this->getScene().size() <= 0) {
        this->setDefaultScene(sceneName);
        this->setActualScene(sceneName);
    }
}

/**
 * @brief Remove a game scene from the engine.
 *
 * This function removes the game scene with the specified name from the engine. The scene is deleted, and if it was the last scene in the engine, an exception is raised. After removal, the default and actual scenes are updated to the first available scene in the engine.

 * @param sceneName The name of the game scene to be removed.
 */
void SceneManager::removeScene(std::string sceneName)
{
    if (sceneName.empty() || sceneName.c_str() == nullptr || sceneName.c_str()[0] == '\0')
        throw SceneManagerException("SceneManager.removeScene error: Empty or invalid name passed as parameter\n");

    auto scene = this->_scene.find(sceneName);
    if (scene == this->_scene.end())
        throw SceneManagerException("SceneManager.removeScene error: Scene with the name '" + sceneName + "' not found in the engine\n");

    if (this->getScene().size() <= 1)
        throw SceneManagerException("SceneManager.removeScene error: You can't remove the scene '" + sceneName + "' because is the only scene in the engine\n");

    delete scene->second;
    this->_scene.erase(scene);

    auto newScene = this->_scene.begin();

    this->setDefaultScene(newScene->first);
    this->setActualScene(newScene->first);
}

/**
 * @brief Get a reference to the map of all game scenes in the engine.
 *
 * @return A reference to the map containing all game scenes.
 */
std::map<std::string, IScene *> &SceneManager::getScene()
{
    return (this->_scene);
}

/**
 * @brief Get a reference to a specific game scene by its name.
 *
 * @param sceneName The name of the game scene to retrieve.
 * @return A reference to the specified game scene.
 */
IScene &SceneManager::getScene(std::string sceneName)
{
    if (sceneName.empty() || sceneName.c_str() == nullptr || sceneName.c_str()[0] == '\0')
        throw SceneManagerException("SceneManager.getScene error: Empty or invalid scene name '" + sceneName + "' passed as parameter\n");

    auto scene = this->_scene.find(sceneName);
    if (scene == this->_scene.end())
        throw SceneManagerException("SceneManager.getScene error: Scene with the name '" + sceneName + "' not found in the engine\n");
    return (*scene->second);
}

/**
 * @brief Check if a game scene with the specified name exists in the engine.
 *
 * @param sceneName The name of the game scene to check for existence.
 * @return `true` if the scene exists, `false` otherwise.
 */
bool SceneManager::sceneExist(std::string sceneName)
{
    if (sceneName.empty() || sceneName.c_str() == nullptr || sceneName.c_str()[0] == '\0')
        throw SceneManagerException("SceneManager.sceneExist error: Empty or invalid scene name '" + sceneName + "' passed as parameter\n");

    auto scene = this->_scene.find(sceneName);
    if (scene == this->_scene.end())
        return (false);
    return (true);
}

/**
 * @brief Set the default game scene for the engine.
 *
 * @param scene The name of the game scene to set as the default.
 */
void SceneManager::setDefaultScene(std::string scene)
{
    if (scene.empty() || scene.c_str() == nullptr || scene.c_str()[0] == '\0')
        throw SceneManagerException("SceneManager.setDefaultScene error: Empty or invalid scene name passed as parameter\n");
    auto sceneName = this->_scene.find(scene);
    if (sceneName == this->_scene.end())
        throw SceneManagerException("SceneManager.setDefaultScene error: Scene with the name '" + scene + "' not found in the engine\n");
    this->_defaultScene = scene;
    if (this->getActualScene() != scene)
        this->_actualScene = scene;
}

/**
 * @brief Get the name of the default game scene.
 *
 * @return A reference to the name of the default game scene.
 */
std::string &SceneManager::getDefaultScene()
{
    return (this->_defaultScene);
}

/**
 * @brief Set the currently active game scene.
 *
 * @param scene The name of the game scene to set as the active scene.
 */
void SceneManager::setActualScene(std::string scene)
{
    if (scene.empty() || scene.c_str() == nullptr || scene.c_str()[0] == '\0')
        throw SceneManagerException("SceneManager.setActualScene error: Empty or invalid scene name passed as parameter\n");
    auto sceneName = this->_scene.find(scene);
    if (sceneName == this->_scene.end())
        throw SceneManagerException("SceneManager.setActualScene error: Scene with the name '" + scene + "' not found in the engine\n");
    this->_actualScene = scene;
}

/**
 * @brief Get the name of the currently active game scene.
 *
 * @return A reference to the name of the currently active game scene.
 */
std::string &SceneManager::getActualScene()
{
    return (this->_actualScene);
}

/**
 * @brief Add an entity to a specific game scene.
 *
 * @param sceneName The name of the game scene to add the entity to.
 * @param entityName The name of the entity to be added.
 */
void SceneManager::addEntitytoScene(std::string sceneName, std::string entityname)
{
    if (sceneName.empty() || sceneName.c_str() == nullptr || sceneName.c_str()[0] == '\0')
        throw SceneManagerException("SceneManager.addEntitytoScene error: Empty or invalid scene name passed as parameter\n");
    if (entityname.empty() || entityname.c_str() == nullptr || entityname.c_str()[0] == '\0')
        throw SceneManagerException("SceneManager.addEntitytoScene error: Empty or invalid entity name passed as parameter\n");

    auto scene = this->_scene.find(sceneName);
    if (scene == this->_scene.end())
        throw SceneManagerException("SceneManager.addEntitytoScene error: Scene with the name '" + sceneName + "' not found in the engine\n");

    IScene *sceneObject = scene->second;
    sceneObject->addEntity(entityname);
}

void SceneManager::createEntityPreset(std::string room, std::string name, std::vector<int> position, std::string picture, std::string tag, bool itsPlayer)
{
    if (!this->_engine->entity->searchEntity(room, name)) {
        this->_engine->scene->addEntitytoScene(room, name);
        (itsPlayer) ? this->_engine->entity->addComponent(room, name, POSITION, VISUAL, PLAYER, _ID_, HEALTH) : this->_engine->entity->addComponent(room, name, POSITION, VISUAL, _ID_, HEALTH) ;
        this->_engine->entity->addTexture(room, name, picture);
        this->_engine->entity->addPosition(room, name, position);
        this->_engine->entity->setTag(room, name, tag);
    }
}

void SceneManager::createTextPreset(std::string room, std::string name, std::vector<int> position, std::string font, std::string setToText, sf::Color color)
{
    if (!this->_engine->entity->searchEntity(room, name)) {
        this->_engine->scene->addEntitytoScene(room, name);
        this->_engine->entity->addComponent(room, name, POSITION, VISUAL, TEXT);
        Text *txt = (Text *)this->_engine->entity->getComponent(room, name, TEXT);
        Position *pos = (Position *)this->_engine->entity->getComponent(room, name, POSITION);
        txt->setFont(font);
        txt->setText(setToText, true);
        txt->setColor(color);
        pos->setPosition(position.at(0), position.at(1));
        txt->setSize(25);
        txt->getText().setPosition(position.at(0), position.at(1));
    }
}

/**
 * @brief Remove an entity from a specific game scene.
 *
 * @param sceneName The name of the game scene from which to remove the entity.
 * @param entityName The name of the entity to be removed.
 */
void SceneManager::removeEntitytoScene(std::string sceneName, std::string entityname)
{
    if (sceneName.empty() || sceneName.c_str() == nullptr || sceneName.c_str()[0] == '\0')
        throw SceneManagerException("SceneManager.removeEntitytoScene error: Empty or invalid scene name passed as parameter\n");
    if (entityname.empty() || entityname.c_str() == nullptr || entityname.c_str()[0] == '\0')
        throw SceneManagerException("SceneManager.removeEntitytoScene error: Empty or invalid entity name passed as parameter\n");

    auto scene = this->_scene.find(sceneName);
    if (scene == this->_scene.end())
        throw SceneManagerException("SceneManager.removeEntitytoScene error: Scene with the name '" + sceneName + "' not found in the engine\n");

    IScene *sceneObject = scene->second;
    sceneObject->removeEntity(entityname);
}

/**
 * @brief Get a map of all entities in a specific game scene.
 *
 * @param sceneName The name of the game scene to retrieve entities from.
 * @return A map of entity names to entity objects in the specified scene.
 */
void SceneManager::removeEntitytoScene(std::string sceneName, IEntity &ent)
{
    auto scene = this->_scene.find(sceneName);
    if (scene == this->_scene.end())
        throw SceneManagerException("SceneManager.removeEntitytoScene error: Scene with the name '" + sceneName + "' not found in the engine\n");

    IScene *sceneObject = scene->second;
    sceneObject->removeEntity(ent.getName());
}

std::map<std::string, IEntity *> SceneManager::getAllEntityFromScene(std::string sceneName)
{
    if (sceneName.empty() || sceneName.c_str() == nullptr || sceneName.c_str()[0] == '\0')
        throw SceneManagerException("SceneManager.getAllEntityFromScene error: Empty or invalid scene name passed as parameter\n");

    auto scene = this->_scene.find(sceneName);
    if (scene == this->_scene.end())
        throw SceneManagerException("SceneManager.getAllEntityFromScene error: Scene with the name '" + sceneName + "' not found in the engine\n");

    IScene *sceneObject = scene->second;
    return (sceneObject->getEntity());
}

/**
 * @brief Get an entity from a specific game scene.
 *
 * @param sceneName The name of the game scene from which to retrieve the entity.
 * @param entityName The name of the entity to retrieve.
 * @return A reference to the entity in the specified scene.
 */
IEntity &SceneManager::getEntityFromScene(std::string sceneName, std::string entityname)
{
    if (sceneName.empty() || sceneName.c_str() == nullptr || sceneName.c_str()[0] == '\0')
        throw SceneManagerException("SceneManager.getEntityFromScene error: Empty or invalid scene name passed as parameter\n");
    if (entityname.empty() || entityname.c_str() == nullptr || entityname.c_str()[0] == '\0')
        throw SceneManagerException("SceneManager.getEntityFromScene error: Empty or invalid entity name passed as parameter\n");

    auto scene = this->_scene.find(sceneName);
    if (scene == this->_scene.end())
        throw SceneManagerException("SceneManager.getEntityFromScene error: Scene with the name '" + sceneName + "' not found in the engine\n");
    IScene *sceneObject = scene->second;
    std::map<std::string, IEntity *> tmp = sceneObject->getEntity();
    auto entity = tmp.find(entityname);
    if (entity == tmp.cend())
        throw SceneManagerException("SceneManager.getEntityFromScene error: Entity with the name '" + entityname + "' not found in the specified scene\n");
    IEntity &finalEntity = *entity->second;
    return (finalEntity);
}

void SceneManager::loadSceneFromJson(const std::string& configFile, Engine& engine)
{
    std::ifstream file(configFile);
    if (file.is_open()) {
        nlohmann::json config;
        file >> config;
        for (const auto& scene : config["scenes"]) {
            const std::string sceneName = scene["name"];
            engine.scene->createScene(sceneName);

            for (const auto& entity : scene["entities"]) {
                const std::string entityName = entity["name"];
                // std::cout << entityName << std::endl;
                engine.scene->addEntitytoScene(sceneName, entityName);

                for (const auto& component : entity["components"]) {
                    const std::string componentType = component["type"];

                    if (componentType == "VISUAL") {
                        engine.entity->addComponent(sceneName, entityName, POSITION, VISUAL, PLAYER, _ID_, HEALTH);
                        engine.entity->addTexture(sceneName, entityName, component["texture"]);
                        const nlohmann::json& position = component["position"];
                        engine.entity->addPosition(sceneName, entityName, {position["x"], position["y"]});
                        if (component.find("scale") != component.end()) {
                            const nlohmann::json& scale = component["scale"];
                            engine.entity->setScale(sceneName, entityName, {scale["x"], scale["y"]});
                        }
                        if (component.find("rect") != component.end()) {
                            const nlohmann::json& rect = component["rect"];
                            engine.entity->setRect(sceneName, entityName, {rect["x"], rect["y"], rect["width"], rect["height"]});
                        }
                        if (component.find("changeScene") != component.end()) {
                            const nlohmann::json& change = component["changeScene"];
                            engine.system->changeSceneOnClick(entityName, sceneName, change["scene"], change["key"]);
                        }
                    }
                }
            }
        }
        if (config.find("windowName") != config.end() && config.find("windowSize") != config.end()) {
            const std::string WindowTitle = config["windowName"];
            const int windowSizeX = config["windowSize"]["x"];
            const int windowSizeY = config["windowSize"]["y"];
            engine.window->create(windowSizeX, windowSizeY, WindowTitle);
        } else
            engine.window->create(500, 500, "Default Name");
    } else {
        std::cerr << "Failed to open the configuration file." << std::endl;
        exit(84);
    }
}

void SceneManager::loadActionFromJson(const std::string& configFile, Engine& engine)
{
    std::ifstream file(configFile);
    if (file.is_open()) {
        nlohmann::json config;
        file >> config;
        for (const auto& scene : config["action"]) {
            const std::string sceneName = scene["namescene"];

            for (const auto& entity : scene["entities"]) {
                const std::string entityName = entity["name"];

                for (const auto& component : entity["action"]) {
                    if (component.find("changeScene") != component.end()) {
                        const nlohmann::json& change = component["changeScene"];
                        keyboardInput_t key_to_press = this->strToKey(change["key"]);
                        engine.system->changeSceneOnClick(entityName, sceneName, change["newscene"], key_to_press);
                    }
                    if (component.find("hover") != component.end()) {
                        const nlohmann::json& hover = component["hover"];
                        engine.system->changeSpriteRectOnHover(sceneName, entityName, {hover["x"], hover["y"], hover["width"], hover["height"]});
                    }
                }
            }
        }
    } else {
        std::cerr << "Failed to open the configuration file." << std::endl;
        exit(84);
    }
}

keyboardInput_t SceneManager::strToKey(const std::string& keyStr) {
    if (keyStr == "KEY_A")
        return (KEY_A);
    if (keyStr == "KEY_Z")
        return (KEY_Z);
    if (keyStr == "KEY_E")
        return (KEY_E);
    if (keyStr == "KEY_R")
        return (KEY_R);
    if (keyStr == "KEY_T")
        return (KEY_T);
    if (keyStr == "KEY_Y")
        return (KEY_Y);
    if (keyStr == "KEY_U")
        return (KEY_U);
    if (keyStr == "KEY_I")
        return (KEY_I);
    if (keyStr == "KEY_O")
        return (KEY_O);
    if (keyStr == "KEY_P")
        return (KEY_P);

    if (keyStr == "KEY_Q")
        return (KEY_Q);
    if (keyStr == "KEY_S")
        return (KEY_S);
    if (keyStr == "KEY_D")
        return (KEY_D);
    if (keyStr == "KEY_F")
        return (KEY_F);
    if (keyStr == "KEY_G")
        return (KEY_G);
    if (keyStr == "KEY_H")
        return (KEY_H);
    if (keyStr == "KEY_J")
        return (KEY_J);
    if (keyStr == "KEY_K")
        return (KEY_K);
    if (keyStr == "KEY_L")
        return (KEY_L);
    if (keyStr == "KEY_M")
        return (KEY_M);

    if (keyStr == "KEY_W")
        return (KEY_W);
    if (keyStr == "KEY_X")
        return (KEY_X);
    if (keyStr == "KEY_C")
        return (KEY_C);
    if (keyStr == "KEY_V")
        return (KEY_V);
    if (keyStr == "KEY_B")
        return (KEY_B);
    if (keyStr == "KEY_N")
        return (KEY_N);

    if (keyStr == "KEY_UP")
        return (KEY_UP);
    if (keyStr == "KEY_LEFT")
        return (KEY_LEFT);
    if (keyStr == "KEY_RIGHT")
        return (KEY_RIGHT);
    if (keyStr == "KEY_DOWN")
        return (KEY_DOWN);

    if (keyStr == "KEY_SPACE")
        return (KEY_SPACE);
    if (keyStr == "KEY_ENTER")
        return (KEY_ENTER);

    if (keyStr == "MOUSE_LEFT")
        return (MOUSE_LEFT);
    if (keyStr == "MOUSE_MIDDLE")
        return (MOUSE_MIDDLE);
    if (keyStr == "MOUSE_RIGHT")
        return (MOUSE_RIGHT);
    return KEY_NULL;
}