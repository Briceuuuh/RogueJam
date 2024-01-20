/*
** EPITECH PROJECT, 2023
** B-CPP-500-RUN-5-1-rtype-florian.etheve
** File description:
** SystemManager
*/

#ifndef SYSTEMMANAGER_HPP_
    #define SYSTEMMANAGER_HPP_
    #include "../../System/System.hpp"
    #include "../../Engine/Engine.hpp"
    using MainLoopCallback = std::function<void()>;

    class System;

    class SystemManager {
        public:
            SystemManager(Engine &engine);
            ~SystemManager();
            void changeSceneOnClick(std::string entityToClick, std::string actualScene, std::string nextScene, keyboardInput_t keyToPress);
            void changeSceneSystem();

            void changeSpriteRectOnHover(std::string sceneName, std::string entityToHover, sf::IntRect hoverRect);
            void changeSpriteRectSystem();

            void playerKeysInterpretation(keyboardInput_t key, const MainLoopCallback& callback);

            void moveEntitySystem(std::string entityName, std::string room, std::vector<bool> movement, float speed, bool remove);
            void moveEntitySpecificSystem(std::string specificTagName, std::string room, std::vector<bool> movement, float speed);

            bool checkCollision(Position *pos1, std::vector<float> rocketSize, Position *pos2, std::vector<float> enemySize);

            bool collisionSystem(std::string entity_name1, std::string entity_name2, std::string room, bool dammage, int nb_dammage, bool removeEnt1, bool removeEnt2);

            void shootSystem(std::string entityName, std::string room, float speed);
            void shootSpecificSystem(std::string specificTagName, std::string room);

        private:
            System *_system;
    };

#endif /* !SYSTEMMANAGER_HPP_ */
