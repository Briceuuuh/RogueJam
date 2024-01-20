/*
** EPITECH PROJECT, 2023
** B-CPP-500-RUN-5-1-rtype-florian.etheve
** File description:
** Hitbox
*/

#ifndef HITBOX_HPP_
    #define HITBOX_HPP_
    #include <iostream>
    #include <vector>
    #include "../IComponent.hpp"
    #include "../Position/Position.hpp"
    #include "../Visual/Visual.hpp"
    #include "../../Entity/IEntity.hpp"

    class Hitbox : public IComponent {
        public:
            Hitbox();
            ~Hitbox();
            ComponentType_t &GetType();
            std::vector<int> &getHitbox();
            void setHitbox(int height, int width);
            bool getCollision(IEntity &entity1, IEntity &entity2);

        private:
            int _height = 0;
            int _width = 0;
            ComponentType_t _type = HITBOX;
    };

#endif /* !HITBOX_HPP_ */
