/*
** EPITECH PROJECT, 2023
** B-CPP-500-RUN-5-1-rtype-florian.etheve
** File description:
** IComponent
*/

#ifndef ICOMPONENT_HPP_
    #define ICOMPONENT_HPP_
    #include "./type.hpp"
    #include <iomanip>
    #include <iostream>

    class IComponent {
        public:
            virtual ~IComponent() = default;
            virtual ComponentType_t &GetType() = 0;

        private:
    };

#endif /* !ICOMPONENT_HPP_ */
