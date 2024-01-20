/*
** EPITECH PROJECT, 2023
** B-CPP-500-RUN-5-1-rtype-florian.etheve
** File description:
** Health
*/

#ifndef HEALTH_HPP_
    #define HEALTH_HPP_
    #include "../IComponent.hpp"

    class Health : public IComponent {
        public:
            Health();
            ~Health();
            ComponentType_t &GetType();
            int &getHealth();
            void setHealth(int health);

        private:
            int _health = 100;
            ComponentType_t _type = HEALTH;
    };

#endif /* !HEALTH_HPP_ */
