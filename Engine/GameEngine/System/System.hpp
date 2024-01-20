/*
** EPITECH PROJECT, 2023
** B-CPP-500-RUN-5-1-rtype-florian.etheve
** File description:
** System
*/

#ifndef SYSTEM_HPP_
    #define SYSTEM_HPP_
    #include "../Engine/Engine.hpp"
    #include <tuple>
    #include <string>
    #include <regex>
    #include <sstream>
    #include <vector>
    using MainLoopCallback = std::function<void()>;

    keyboardInput_t getKeyBinded(std::tuple<std::string, std::string, std::vector<keyboardInput_t>> keyOfEntity, int index);

    class System {
        public:
            System(Engine &engine);
            ~System();
            void changeSceneOnClick(std::string entityToClick, std::string actualScene, std::string nextScene, keyboardInput_t keyToPress);
            void changeSceneSystem();

            void changeSpriteRectOnHover(std::string sceneName, std::string entityToHover, sf::IntRect hoverRect);
            void changeSpriteRectSystem();

            void playerKeysInterpretation(keyboardInput_t key, const MainLoopCallback& callback);

            void moveEntitySystem(std::string entityName, std::string room, std::vector<bool> movement, float speed, bool remove);
            void moveEntitySpecificSystem(std::string specificTagName, std::string room, std::vector<bool> movement, float speed);

            bool collisionSystem(std::string entity_name1, std::string entity_name2, std::string room, bool dammage, int nb_dammage, bool removeEnt1, bool removeEnt2);

            void shootSystem(std::string entityName, std::string room, float speed);
            void shootSpecificSystem(std::string specificTagName, std::string room);

            bool checkCollision(Position *pos1, std::vector<float> rocketSize, Position *pos2, std::vector<float> enemySize);

            class SystemException : public std::runtime_error {
                public:
                    SystemException(const std::string& msg) : std::runtime_error(msg) {};
            };

        private:
            Engine *_engine;
            bool checksystem(std::string room, Position *poscomp, std::map<std::string, IEntity *> ent, std::string entity_name1, Visual *visualComp1, bool removeEnt2);
            std::vector<std::tuple<std::string, std::string, std::string, keyboardInput_t>> _actionButton;
            std::vector<std::tuple<std::string, std::string, sf::IntRect>> _hoverAction;
    };

#endif /* !SYSTEM_HPP_ */