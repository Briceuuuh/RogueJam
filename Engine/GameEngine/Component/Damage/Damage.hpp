/*
** EPITECH PROJECT, 2023
** B-CPP-500-RUN-5-1-rtype-florian.etheve
** File description:
** Damage
*/

#ifndef DAMAGE_HPP_
    #define DAMAGE_HPP_
    #include "../IComponent.hpp"

    class Damage : public IComponent {
        public:
            Damage();
            ~Damage();
            ComponentType_t &GetType();
            int &getDamage();
            void setDamage(int damageCount);
            bool &isDisable();
            void disableState(bool state);

        private:
            int _damageCount = 0;
            bool _disabled = false;
            ComponentType_t _type = DAMAGE;
    };

#endif /* !DAMAGE_HPP_ */
