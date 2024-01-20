/*
** EPITECH PROJECT, 2023
** B-CPP-500-RUN-5-1-rtype-florian.etheve
** File description:
** Position
*/

#ifndef POSITION_HPP_
    #define POSITION_HPP_
    #include <iostream>
    #include <vector>
    #include "../IComponent.hpp"

    class Position : public IComponent {
        public:
            Position();
            ~Position();
            ComponentType_t &GetType();
            std::vector<int> &getPostion();
            void setPosition(int x, int y);

        private:
            int _x = 0;
            int _y = 0;
            ComponentType_t _type = POSITION;
    };

#endif /* !POSITION_HPP_ */
