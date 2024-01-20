/*
** EPITECH PROJECT, 2023
** B-CPP-500-RUN-5-1-rtype-florian.etheve
** File description:
** EntityManager
*/

#ifndef ENTITYMANAGER_HPP_
    #define ENTITYMANAGER_HPP_
    #include <iostream>
    #include <map>
    #include "../../Scene/Scene.hpp"
    #include "./EventManager.hpp"
    #include "../../Component/ComponentPackage.hpp"
    #include "../Engine.hpp"

    class Engine;

    class EntityManager {
        public:
            EntityManager(std::map<std::string, IScene *> &scene, Engine &engine);
            ~EntityManager();

            IEntity &findEntity(std::string sceneName, std::string entityName);
            bool searchEntity(std::string sceneName, std::string entityName);

            template<typename... ComponentTypes>
            void addComponent(std::string sceneName, std::string entityName, ComponentTypes... components) {
                if (sceneName.empty() || sceneName.c_str() == nullptr || sceneName.c_str()[0] == '\0')
                    throw EntityException("Engine.addComponentToEntity error: Empty or invalid scene name passed as parameter\n");
                if (entityName.empty() || entityName.c_str() == nullptr || entityName.c_str()[0] == '\0')
                    throw EntityException("Engine.addComponentToEntity error: Empty or invalid entity name passed as parameter\n");

                auto scene = this->_scene.find(sceneName);
                if (scene == this->_scene.end())
                    throw EntityException("Engine.addComponentToEntity error: Scene with the name '" + sceneName + "' not found in the engine\n");

                auto entity = scene->second->getEntity().find(entityName);
                if (entity == scene->second->getEntity().end())
                    throw EntityException("Engine.addComponentToEntity error: Entity with the name '" + entityName + "' not found in the scene\n");

                (entity->second->AddComponent(components), ...);
            }

            template<typename... ComponentTypes>
            void removeComponent(std::string sceneName, std::string entityName, ComponentTypes... components) {
                if (sceneName.empty() || sceneName.c_str() == nullptr || sceneName.c_str()[0] == '\0')
                    throw EntityException("Engine.removeComponentToEntity error: Empty or invalid scene name passed as parameter\n");
                if (entityName.empty() || entityName.c_str() == nullptr || entityName.c_str()[0] == '\0')
                    throw EntityException("Engine.removeComponentToEntity error: Empty or invalid entity name passed as parameter\n");

                auto scene = this->_scene.find(sceneName);
                if (scene == this->_scene.end())
                    throw EntityException("Engine.removeComponentToEntity error: Scene with the name '" + sceneName + "' not found in the engine\n");

                auto entity = scene->second->getEntity().find(entityName);
                if (entity == scene->second->getEntity().end())
                    throw EntityException("Engine.removeComponentToEntity error: Entity with the name '" + entityName + "' not found in the scene\n");
                (entity->second->RemoveComponent(components), ...);
            }

            void addTexture(std::string sceneName, std::string entityName, std::string texturePath);
            void addPosition(std::string sceneName, std::string entityName, std::vector<int> position);
            std::vector<int> &getPositionOfEntity(std::string sceneName, std::string entityName);
            std::vector<IComponent *> &getComponent(std::string sceneName, std::string entityName);
            IComponent *getComponent(std::string sceneName, std::string entityName, ComponentType_t comp);

            void setRect(std::string sceneName, std::string entityName, sf::IntRect rect);
            const sf::IntRect &getRect(std::string sceneName, std::string entityName);
            sf::IntRect getDefaultRect(std::string sceneName, std::string entityName);


            void setScale(std::string sceneName, std::string entityName, std::vector<float> scale);
            void setVisibility(std::string sceneName, std::string entityName, bool state);
            bool &isVisible(std::string sceneName, std::string entityName);

            bool isClicked(std::string sceneName, std::string entityName, keyboardInput_t input);
            bool isHover(std::string sceneName, std::string entityName);

            void refreshScene(std::map<std::string, IScene *>);

            void setID(std::string sceneName, std::string entityName, unsigned int id);
            unsigned int &getID(std::string sceneName, std::string entityName);

            void setTag(std::string sceneName, std::string entityName, std::string tag);
            std::string &getTag(std::string sceneName, std::string entityName);

            class EntityException : public std::runtime_error {
                public:
                    EntityException(const std::string& msg) : std::runtime_error(msg) {};
            };

        private:
            Engine *_engine;
            std::map<std::string, IScene *> &_scene;
    };

#endif /* !ENTITYMANAGER_HPP_ */
