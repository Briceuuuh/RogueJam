/*
** EPITECH PROJECT, 2023
** B-CPP-500-RUN-5-1-rtype-florian.etheve
** File description:
** Invalid
*/

#ifndef INVALID_HPP_
    #define INVALID_HPP_
    #include "../IComponent.hpp"

    class Invalid : public IComponent {
        public:
            Invalid();
            ~Invalid();
            ComponentType_t &GetType();

        private:
            ComponentType_t _type = __INVALID__;
    };

#endif /* !INVALID_HPP_ */
