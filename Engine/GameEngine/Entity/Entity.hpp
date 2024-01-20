/*
** EPITECH PROJECT, 2023
** B-CPP-500-RUN-5-1-rtype-florian.etheve
** File description:
** Entity
*/

#ifndef ENTITY_HPP_
    #define ENTITY_HPP_
    #include <vector>
    #include "./IEntity.hpp"
    #include "../Component/Invalid/Invalid.hpp"

    class Entity : public IEntity {
        public:
            Entity();
            ~Entity();
            void AddComponent(ComponentType_t type);
            void RemoveComponent(ComponentType_t type);
            std::vector<IComponent *> &GetCurrentComponent();
            IComponent *getComponent(ComponentType_t comp);
            IComponent &getComponentRef(ComponentType_t comp);

            std::string &getName();
            void setName(std::string name);
            class EntityException : public std::runtime_error {
                public:
                    EntityException(const std::string& msg) : std::runtime_error(msg) {};
            };

        private:
            std::vector<IComponent *> _components;
            std::string _name;
    };

#endif /* !ENTITY_HPP_ */
