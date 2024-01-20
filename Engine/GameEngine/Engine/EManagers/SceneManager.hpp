/*
** EPITECH PROJECT, 2023
** B-CPP-500-RUN-5-1-rtype-florian.etheve
** File description:
** SceneManager
*/

#ifndef SCENEMANAGER_HPP_
    #define SCENEMANAGER_HPP_
    #include <iostream>
    #include <map>
    #include <string>
    #include <iostream>
    #include <fstream>
    #include <nlohmann/json.hpp>

    #include "../../Scene/Scene.hpp"
    #include "../Engine.hpp"

    class SceneManager {
        public:
            SceneManager(Engine &engine);
            ~SceneManager();
            void createScene(std::string sceneName);
            void removeScene(std::string sceneName);
            std::map<std::string, IScene *> &getScene();
            IScene &getScene(std::string sceneName);
            bool sceneExist(std::string sceneName);
            void setDefaultScene(std::string scene);
            std::string &getDefaultScene();
            void setActualScene(std::string scene);
            std::string &getActualScene();

            void addEntitytoScene(std::string sceneName, std::string entityname);
            void createEntityPreset(std::string room, std::string name, std::vector<int> position, std::string picture, std::string tag, bool itsPlayer);
            void createTextPreset(std::string room, std::string name, std::vector<int> position, std::string font, std::string setToTex, sf::Color color);
            void removeEntitytoScene(std::string sceneName, std::string entityname);
            void removeEntitytoScene(std::string sceneName, IEntity &ent);
            void moveEntityToScene(std::string currentScene, std::string entityName, std::string Newscene);
            std::map<std::string, IEntity *> getAllEntityFromScene(std::string sceneName);
            IEntity &getEntityFromScene(std::string sceneName, std::string entityname);

            void loadSceneFromJson(const std::string& configFile, Engine& engine);
            void loadActionFromJson(const std::string& configFile, Engine& engine);

            class SceneManagerException : public std::runtime_error {
                public:
                    SceneManagerException(const std::string& msg) : std::runtime_error(msg) {};
            };

        private:
            keyboardInput_t strToKey(const std::string& keyStr);
            std::string _defaultScene = "None";
            std::string _actualScene = "None";
            std::map<std::string, IScene *> _scene;
            Engine *_engine;
    };

#endif /* !SCENEMANAGER_HPP_ */
