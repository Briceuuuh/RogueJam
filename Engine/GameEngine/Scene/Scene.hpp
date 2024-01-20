/*
** EPITECH PROJECT, 2023
** B-CPP-500-RUN-5-1-rtype-florian.etheve
** File description:
** Scene
*/

#ifndef SCENE_HPP_
    #define SCENE_HPP_
    #include "../Entity/IEntity.hpp"
    #include "../Entity/Entity.hpp"
    #include <iostream>
    #include <map>

    class IScene {
        public:
            virtual ~IScene() = default;
            virtual std::map<std::string, IEntity *> &getEntity() = 0;
            virtual void addEntity(std::string name) = 0;
            virtual void removeEntity(std::string name) = 0;
            virtual void setName(std::string name) = 0;
            virtual std::string &getName() = 0;
    };

    class Scene : public IScene {
        public:
            Scene();
            ~Scene();
            std::map<std::string, IEntity *> &getEntity();
            void addEntity(std::string name);
            void removeEntity(std::string name);
            void removeEntity(IEntity &ent);
            void setName(std::string name);
            std::string &getName();

            class SceneException : public std::runtime_error {
                public:
                    SceneException(const std::string& msg) : std::runtime_error(msg) {};
            };

        private:
            std::string _name;
            std::map<std::string, IEntity *> _entity;
    };

#endif /* !SCENE_HPP_ */
