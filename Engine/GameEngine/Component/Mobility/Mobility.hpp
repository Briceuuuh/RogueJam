/*
** EPITECH PROJECT, 2023
** B-CPP-500-RUN-5-1-rtype-florian.etheve
** File description:
** Mobility
*/

#ifndef MOBILITY_HPP_
    #define MOBILITY_HPP_
    #include "../IComponent.hpp"

    class Mobility : public IComponent{
        public:
            Mobility();
            ~Mobility();
            ComponentType_t &GetType();
            float &getSpeed();
            void setSpeed(float speed);

        private:
            float _speed = 1;
            ComponentType_t _type = MOBILITY;
    };

#endif /* !MOBILITY_HPP_ */
