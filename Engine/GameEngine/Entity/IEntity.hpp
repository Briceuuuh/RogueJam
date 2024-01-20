/*
** EPITECH PROJECT, 2023
** B-CPP-500-RUN-5-1-rtype-florian.etheve
** File description:
** IEntity
*/

#ifndef IENTITY_HPP_
    #define IENTITY_HPP_
    #include <iostream>
    #include <vector>
    #include "../Component/IComponent.hpp"

    class IEntity {
        public:
            virtual ~IEntity() = default;
            virtual void AddComponent(ComponentType_t type) = 0;
            virtual void RemoveComponent(ComponentType_t type) = 0;
            virtual std::vector<IComponent *> &GetCurrentComponent() = 0;
            virtual IComponent *getComponent(ComponentType_t comp) = 0;
            virtual IComponent &getComponentRef(ComponentType_t comp) = 0;
            virtual std::string &getName() = 0;
            virtual void setName(std::string name) = 0;
    };

#endif /* !IENTITY_HPP_ */
